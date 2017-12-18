#include "Manager.h"
#include "DataManager.h"
#include "HelloWorldScene.h"
USING_NS_CC;

static Manager* _manager = nullptr;

Manager* Manager::getManager()
{
	if (_manager == nullptr)
	{
		_manager = new Manager();
	}
	return _manager;
}

Manager::Manager()
	:m_hero(nullptr),
	m_layer(nullptr),
	m_boss(nullptr)
{
}

Manager::~Manager()
{
	if (m_hero)
		m_hero->removeFromParent();
	for (auto t : m_targets)
	{
		t->removeFromParent();
	}
	m_targets.clear();
	for (auto b : m_playerbullets)
	{
		b->removeFromParent();
	}
	m_playerbullets.clear();
	for (auto b : m_enemybullets)
	{
		b->removeFromParent();
	}
	m_enemybullets.clear();
	for (auto i : m_items)
	{
		i->removeFromParent();
	}
	m_items.clear();
}

void Manager::pauseAll()
{
	if (m_hero)
		m_hero->pauseAll();
	if (m_boss)
		m_boss->pauseAll();
	for (auto t : m_targets)
	{
		t->pauseAll();
	}
	for (auto b : m_playerbullets)
	{
		b->pauseSchedulerAndActions();
	}
	for (auto b : m_enemybullets)
	{
		b->pauseSchedulerAndActions();
	}
	for (auto i : m_items)
	{
		i->pauseSchedulerAndActions();
	}
}

void Manager::init()
{
	auto size = Director::getInstance()->getVisibleSize();
	m_boss = nullptr;
	m_targets.clear();
	m_playerbullets.clear();
	m_enemybullets.clear();
	m_items.clear();
}

void Manager::update(float dt)
{
	produceEnemy();
	detectBullet();
	detectPlayer();
	detectEnemy();
}

void Manager::produceEnemy()
{
	auto level = DataManager::getDataManager()->getLevel();
	auto size = Director::getInstance()->getVisibleSize();
	auto plane = DataManager::getDataManager()->getDefeatEnemyNum();
	if (m_boss == nullptr)
	{
		if (plane <= level * 100)
		{
			if (m_targets.size() <= 3 * level)
			{
				int type = CCRANDOM_0_1() * 2 + 1;
				auto tar = Target::create(StringUtils::format("EnemyPlane/enemyplane_%02d.png", type));
				tar->initTarget(Vec2(0, -1), 50 * level, CCRANDOM_0_1() * 10 + 10, CCRANDOM_0_1() * 50 + 10);
				tar->initLauncher(10 + type);
				tar->setBulletType(10 + type);
				tar->setPosition(Vec2(CCRANDOM_0_1() * (size.width - tar->getContentSize().width * 2) + tar->getContentSize().width, CCRANDOM_0_1() * tar->getContentSize().height * 3 + size.height));

				m_targets.pushBack(tar);
				m_layer->addChild(tar);
			}
		}
		else
		{
			m_boss = Target::create("EnemyPlane/bossplane_01.png");
			m_boss->initTarget(Vec2(0, 0), 0, 30 * level, MAX_HP * level);
			m_boss->initLauncher(20 + 1);
			m_boss->setBulletType(20 + 1);
			m_boss->setPosition(size.width / 2, size.height + m_boss->getContentSize().height * 2);
			m_layer->addChild(m_boss);
			m_boss->runAction(MoveBy::create(2.0f, Vec2(0, -m_boss->getContentSize().height * 3)));
		}
	}
	
}

void Manager::detectEnemy()
{
	auto size = Director::getInstance()->getVisibleSize();
	if (m_boss)
	{
		for (size_t j = 0; j < m_playerbullets.size(); j++)
		{
			auto bul = m_playerbullets.at(j);
			if (m_boss->getBoundingBox().containsPoint(bul->getPosition()))
			{
				m_boss->getHit(bul->getDemage());
				if (bul->getType() != 3)
				{
					bul->stopAllActions();
					bul->endCall();
					m_playerbullets.eraseObject(bul);
				}
				break;
			}
		}
		if (m_boss->getHp() <= 0)
		{
			auto sc = m_boss->getDemage();
			DataManager::getDataManager()->setScore(DataManager::getDataManager()->getScore() + sc);
			m_boss->endCall();
			DataManager::getDataManager()->setDefeatEnemyNum(DataManager::getDataManager()->getDefeatEnemyNum() + 1);
			static_cast<HelloWorld*>(m_layer)->setUIString();
			//TODO:many things
			static_cast<HelloWorld*>(m_layer)->gameEnd();
			return;
		}
	}
	
	for (size_t i = 0; i < m_targets.size(); i++)
	{
		auto tar = m_targets.at(i);
		Rect rc = { 0, 0, size.width, size.height };
		if (tar->getPositionY() <= -tar->getContentSize().height)
		{
			tar->removeFromParent();
			m_targets.eraseObject(tar);
			i--;
			continue;
		}
		for (size_t j = 0; j < m_playerbullets.size(); j++)
		{
			auto bul = m_playerbullets.at(j);
			if (tar->getBoundingBox().containsPoint(bul->getPosition()))
			{
				tar->getHit(bul->getDemage());
				if (bul->getType() != 3)
				{
					bul->stopAllActions();
					bul->endCall();
					m_playerbullets.eraseObject(bul);
				}
				break;
			}
		}
		if (tar->getHp() <= 0)
		{
			auto sc = tar->getDemage();
			DataManager::getDataManager()->setScore(DataManager::getDataManager()->getScore() + sc);
			produceItem(tar->getPosition());
			tar->endCall();
			m_targets.eraseObject(tar);
			DataManager::getDataManager()->setDefeatEnemyNum(DataManager::getDataManager()->getDefeatEnemyNum() + 1);
			i--;
			static_cast<HelloWorld*>(m_layer)->setUIString();
			continue;
		}
		if (m_hero->getBoundingBox().intersectsRect(tar->getBoundingBox()))
		{
			m_hero->getHit(tar->getDemage());
			static_cast<HelloWorld*>(m_layer)->setUIString();
			tar->endCall();
			m_targets.eraseObject(tar);
			i--;
			return;
		}
	}
}

void Manager::detectBullet()//out
{
	auto size = Director::getInstance()->getVisibleSize();
	for (size_t j = 0; j < m_playerbullets.size(); j++)
	{
		auto bul = m_playerbullets.at(j);
		Rect rc = { 0, 0, size.width, size.height };
		if (!rc.intersectsRect(bul->getBoundingBox()))
		{
			bul->stopAllActions();
			bul->removeFromParent();
			m_playerbullets.eraseObject(bul);
			j--;
		}
	}
	for (size_t j = 0; j < m_enemybullets.size(); j++)
	{
		auto bul = m_enemybullets.at(j);
		Rect rc = { 0, 0, size.width, size.height };
		if (!rc.intersectsRect(bul->getBoundingBox()))
		{
			bul->stopAllActions();
			bul->removeFromParent();
			m_enemybullets.eraseObject(bul);
			j--;
		}
	}
}

void Manager::detectPlayer()//hit
{
	auto size = Director::getInstance()->getVisibleSize();
	auto rc = Rect{ 0, 0, m_hero->getContentSize().width, m_hero->getContentSize().height };
	for (size_t i = 0; i < m_enemybullets.size(); i++)
	{
		auto bul = m_enemybullets.at(i);
		auto pos = m_hero->convertToNodeSpace(bul->convertToWorldSpace(Vec2::ZERO));
		if (rc.containsPoint(pos))
		{
			m_hero->getHit(bul->getDemage());
			static_cast<HelloWorld*>(m_layer)->setUIString();
			bul->endCall();
			m_enemybullets.eraseObject(bul);
			return;
		}
	}

	for (size_t i = 0; i < m_items.size(); i++)
	{
		auto item = m_items.at(i);
		Rect rc = { 0, 0, size.width, size.height };
		if (!rc.intersectsRect(item->getBoundingBox()))
		{
			item->removeFromParent();
			m_items.eraseObject(item);
			i--;
			continue;
		}
		if (m_hero->getBoundingBox().containsPoint(item->getPosition()))
		{
			m_hero->getBuff(item->getType());
			item->removeFromParent();
			m_items.eraseObject(item);
			i--;
		}
	}
}

void Manager::produceItem(Vec2 pos)
{
	int r = CCRANDOM_0_1() * 1000;
	if (r > 0 && r < 100)
	{
		auto item = Item::create(StringUtils::format("ui/buff%d.png",1), 1);
		item->setPosition(pos);
		m_items.pushBack(item);
		m_layer->addChild(item);
	}
	else if (r > 100 && r < 150)
	{
		auto item = Item::create(StringUtils::format("ui/buff%d.png", 2), 2);
		item->setPosition(pos);
		m_items.pushBack(item);
		m_layer->addChild(item);
	}
	else if (r > 150 && r < 180)
	{
		auto item = Item::create(StringUtils::format("ui/buff%d.png", 3), 3);
		item->setPosition(pos);
		m_items.pushBack(item);
		m_layer->addChild(item);
	}
	else
		return;
}

void Manager::playerAddBullet(Bullet* bul)
{
	m_layer->addChild(bul);
	m_playerbullets.pushBack(bul);
}

void Manager::enemyAddBullet(Bullet* bul)
{
	m_layer->addChild(bul);
	m_enemybullets.pushBack(bul);
}