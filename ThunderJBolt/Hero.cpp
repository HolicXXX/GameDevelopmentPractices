#include "Hero.h"
#include "DataManager.h"
#include "Manager.h"
USING_NS_CC;

Hero* Hero::create(const std::string& str)
{
	auto h = new Hero();
	if (h && h->init(str))
	{
		h->autorelease();
		return h;
	}
	CC_SAFE_DELETE(h);
	return nullptr;
}

bool Hero::init(const std::string& str)
{
	m_hp = 1000;
	m_isshout = false;
	m_moveStep = Vec2::ZERO;
	m_bulletType = 1;

	return this->initWithFile(str);
}

void Hero::initListener()
{
	m_upAni = AnimationCache::getInstance()->getAnimation("forward");
	m_backAni = AnimationCache::getInstance()->getAnimation("back");

	m_klistener = EventListenerKeyboard::create();
	m_klistener->onKeyPressed = [this](EventKeyboard::KeyCode kc, Event*){
		if (kc == EventKeyboard::KeyCode::KEY_W)
		{
			this->addDir(moveDirection::UP, true);
			this->stopAllActions();
			this->runAction(Animate::create(m_upAni));
		}
		if (kc == EventKeyboard::KeyCode::KEY_S)
		{
			this->addDir(moveDirection::DOWN, true);
			this->stopAllActions();
			this->runAction(Animate::create(m_backAni));
		}
		if (kc == EventKeyboard::KeyCode::KEY_A)
		{
			this->addDir(moveDirection::LEFT, true);
		}
		if (kc == EventKeyboard::KeyCode::KEY_D)
		{
			this->addDir(moveDirection::RIGHT, true);
		}
		if (kc == EventKeyboard::KeyCode::KEY_J)
		{
			this->m_isshout = true;
			m_bulletType = 1;
		}
		if (kc == EventKeyboard::KeyCode::KEY_K)
		{
			this->m_isshout = true;
			m_bulletType = 2;
		}
		if (kc == EventKeyboard::KeyCode::KEY_L)
		{
			this->m_isshout = true;
			m_bulletType = 3;
		}
	};
	m_klistener->onKeyReleased = [this](EventKeyboard::KeyCode kc, Event*){
		if (kc == EventKeyboard::KeyCode::KEY_W)
		{
			this->addDir(moveDirection::UP, false);
			this->stopAllActions();
			this->setTexture("PlayerPlane/normal_01.png");
		}
		if (kc == EventKeyboard::KeyCode::KEY_S)
		{
			this->addDir(moveDirection::DOWN, false);
			this->stopAllActions();
			this->setTexture("PlayerPlane/normal_01.png");
		}
		if (kc == EventKeyboard::KeyCode::KEY_A)
		{
			this->addDir(moveDirection::LEFT, false);
		}
		if (kc == EventKeyboard::KeyCode::KEY_D)
		{
			this->addDir(moveDirection::RIGHT, false);
		}
		if (kc == EventKeyboard::KeyCode::KEY_J ||
			kc == EventKeyboard::KeyCode::KEY_K ||
			kc == EventKeyboard::KeyCode::KEY_L)
		{
			this->m_isshout = false;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_klistener, this);
}

void Hero::getBuff(int type)
{
	if (type == m_Launcher->getType())
	{
		m_Launcher->setLevel(m_Launcher->getLevel() + 1);
	}
	else
	{
		m_Launcher->setType(type);
		m_Launcher->setLevel(1);
	}
}

void Hero::initLauncher(int type)
{
	if (m_Launcher)
		this->removeChild(m_Launcher, true);
	auto launcher = Launcher::create();
	launcher->setLauncherType(LauncherType::PLAYER_LAUNCHER);
	launcher->setPosition(Vec2(0, 20) + this->getContentSize() / 2);
	launcher->setType(type);
	launcher->setLevel(1);
	m_Launcher = launcher;
	m_Launcher->scheduleUpdate();
	this->addChild(launcher);
}

void Hero::addDir(moveDirection d,bool b)
{
	const float step = 300;
	switch (d)
	{
	case moveDirection::UP:
	{
		if (b)
			m_moveStep = m_moveStep + Vec2(0, step);
		else
			m_moveStep = m_moveStep - Vec2(0, step);
	}
	break;
	case moveDirection::DOWN:
	{
		if (b)
			m_moveStep = m_moveStep + Vec2(0, -step);
		else
			m_moveStep = m_moveStep - Vec2(0, -step);
	}
	break;
	case moveDirection::LEFT:
	{
		if (b)
			m_moveStep = m_moveStep + Vec2(-step, 0);
		else
			m_moveStep = m_moveStep - Vec2(-step, 0);
	}
	break;
	case moveDirection::RIGHT:
	{
		if (b)
			m_moveStep = m_moveStep + Vec2(step, 0);
		else
			m_moveStep = m_moveStep - Vec2(step, 0);
	}
	break;
	}
}

void Hero::getHit(int d)
{
	DataManager::getDataManager()->setPlayerHP(DataManager::getDataManager()->getPlayerHP() - d);
	
	hpDown();
}

void Hero::hpDown()
{
	if (DataManager::getDataManager()->getPlayerHP() <= 0)
	{
		this->pauseAll();
		this->stopAllActions();
		_eventDispatcher->removeEventListenersForTarget(this);
		auto ani = Animate::create(AnimationCache::getInstance()->getAnimation("planeexplode"));
		this->runAction(Sequence::create(ani, CallFunc::create([this]()->void{
			this->setVisible(false);
		}), nullptr));
	}
}

void Hero::update(float dt)
{
	auto size = Director::getInstance()->getVisibleSize();
	auto next = this->getPosition() + m_moveStep * dt;
	if (next.x <= 0 || next.x >= size.width || next.y <= 0 || next.y >= size.height)
		return;
	this->setPosition(next);
}

void Hero::pauseAll()
{
	this->pauseSchedulerAndActions();
	m_Launcher->unscheduleUpdate();
}