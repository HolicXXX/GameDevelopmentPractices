#include "HelloWorldScene.h"
#include "DataManager.h"
#include "SceneManager.h"
#include "Manager.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	auto size = Director::getInstance()->getVisibleSize();
	
	auto dm = DataManager::getDataManager();
	dm->setScore();
	dm->setDefeatEnemyNum();
	dm->setPlayerHP();

	Manager::getManager()->init();

	loadAnimation();
	initBackGround();
	initUI();
	startInit();

    return true;
}

void HelloWorld::initBackGround()
{
	auto level = DataManager::getDataManager()->getLevel();
	m_background1 = Sprite::create(StringUtils::format("background/background_%02d.jpg",level));
	m_background1->setPosition(m_background1->getContentSize().width / 2, m_background1->getContentSize().height / 2);
	this->addChild(m_background1);
	m_background2 = Sprite::create(StringUtils::format("background/background_%02d.jpg", level));
	m_background2->setPosition(m_background2->getContentSize().width / 2, m_background1->getContentSize().height + m_background2->getContentSize().height / 2);
	m_background2->setFlippedY(true);
	this->addChild(m_background2);
}

void HelloWorld::startInit()
{
	auto size = Director::getInstance()->getVisibleSize();

	m_hero = Hero::create("PlayerPlane/normal_01.png");
	m_hero->setTag(1);
	m_hero->initListener();
	m_hero->setPosition(size.width / 2, 0 - 2 * m_hero->getContentSize().height);
	this->addChild(m_hero);
	m_hero->runAction(Sequence::create(MoveTo::create(1.0f, Vec2(size.width / 2, m_hero->getContentSize().height * 2)),
		CallFunc::create([this]()->void{
		this->m_hero->scheduleUpdate();
		m_hero->initLauncher(m_hero->getBulletType());
	})
		, nullptr));

	Manager::getManager()->bindLayer(this);
	Manager::getManager()->bindPlayer(m_hero);

	scheduleUpdate();
}

void HelloWorld::initUI()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto dm = DataManager::getDataManager();
	auto score = dm->getScore();
	auto hp = dm->getPlayerHP();

	m_scoreImage = Sprite::create("ui/score.png");
	m_scoreImage->setPosition(m_scoreImage->getContentSize().width / 2, size.height - m_scoreImage->getContentSize().height / 2);
	this->addChild(m_scoreImage,10);

	m_score = Label::createWithTTF(StringUtils::format("%05d", score), "fonts/arial.ttf", 24);
	m_score->setPosition(m_scoreImage->getContentSize().width + m_score->getContentSize().width / 2, m_score->getContentSize().height / 2);
	m_score->setTextColor(Color4B::WHITE);
	m_scoreImage->addChild(m_score);

	m_hpImage = Sprite::create("ui/playHP.png");
	m_hpImage->setPosition(m_hpImage->getContentSize().width / 2, size.height - m_scoreImage->getContentSize().height - m_hpImage->getContentSize().height / 2);
	this->addChild(m_hpImage,10);

	m_hpBG = Sprite::create("ui/plane_lifebg.png");
	m_hpBG->setPosition(m_hpImage->getContentSize().width, m_hpImage->getContentSize().height / 2);
	m_hpBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	m_hpImage->addChild(m_hpBG);
	
	m_hpBar = Sprite::create("ui/plane_lifebar.png");
	auto width = m_hpBar->getTextureRect().size.width * DataManager::getDataManager()->getPlayerHP() / MAX_HP;
	m_hpBar->setTextureRect(Rect{ 0, 0, width, m_hpBar->getTextureRect().size.height });
	m_hpBar->setPosition(m_hpImage->getContentSize().width, m_hpImage->getContentSize().height / 2);
	m_hpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	m_hpImage->addChild(m_hpBar);
}

void HelloWorld::loadAnimation()
{
	auto anicache = AnimationCache::getInstance();
	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("PlayerPlane/forward_01.png", Rect(0, 0, 83, 117)));
		ani->addSpriteFrame(SpriteFrame::create("PlayerPlane/forward_02.png", Rect(0, 0, 83, 117)));
		anicache->addAnimation(ani, "forward");
	}
	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("PlayerPlane/back_01.png", Rect(0, 0, 83, 84)));
		ani->addSpriteFrame(SpriteFrame::create("PlayerPlane/back_02.png", Rect(0, 0, 83, 84)));
		anicache->addAnimation(ani, "back");
	}
	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("PlayerPlane/planeex_01.png", Rect(0, 0, 113, 112)));
		ani->addSpriteFrame(SpriteFrame::create("PlayerPlane/planeex_02.png", Rect(0, 0, 107, 109)));
		ani->addSpriteFrame(SpriteFrame::create("PlayerPlane/planeex_03.png", Rect(0, 0, 124, 131)));
		anicache->addAnimation(ani, "planeexplode");
	}
	
	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("EnemyPlane/enemy_explode_01.png", Rect(0, 0, 64, 64)));
		ani->addSpriteFrame(SpriteFrame::create("EnemyPlane/enemy_explode_02.png", Rect(0, 0, 32, 32)));
		anicache->addAnimation(ani, "enemyexplode");
	}
	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("EnemyPlane/boss_explode_01.png", Rect(0, 0, 128, 128)));
		ani->addSpriteFrame(SpriteFrame::create("EnemyPlane/boss_explode_02.png", Rect(0, 0, 194, 194)));
		anicache->addAnimation(ani, "bossexplode");
	}

	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("bullet/bullet_01(1).png", Rect(0, 0, 23, 45)));
		ani->addSpriteFrame(SpriteFrame::create("bullet/bullet_01(2).png", Rect(0, 0, 26, 59)));
		anicache->addAnimation(ani, "bullet01");
	}
	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("bullet/bulletex_01(1).png", Rect(0, 0, 39, 37)));
		ani->addSpriteFrame(SpriteFrame::create("bullet/bulletex_01(2).png", Rect(0, 0, 59, 53)));
		anicache->addAnimation(ani, "bulletex01");
	}
	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("bullet/bullet_02(1).png", Rect(0, 0, 24, 59)));
		ani->addSpriteFrame(SpriteFrame::create("bullet/bullet_02(2).png", Rect(0, 0, 29, 76)));
		anicache->addAnimation(ani, "bullet02");
	}
	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("bullet/bulletex_02(1).png", Rect(0, 0, 38, 62)));
		ani->addSpriteFrame(SpriteFrame::create("bullet/bulletex_02(2).png", Rect(0, 0, 47, 60)));
		anicache->addAnimation(ani, "bulletex02");
	}
	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("bullet/bullet_03(1).png", Rect(0, 0, 30, 109)));
		ani->addSpriteFrame(SpriteFrame::create("bullet/bullet_03(2).png", Rect(0, 0, 42, 126)));
		anicache->addAnimation(ani, "bullet03");
	}
	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("bullet/bulletex_03(1).png", Rect(0, 0, 75, 70)));
		ani->addSpriteFrame(SpriteFrame::create("bullet/bulletex_03(2).png", Rect(0, 0, 109, 109)));
		ani->addSpriteFrame(SpriteFrame::create("bullet/bulletex_03(3).png", Rect(0, 0, 45, 42)));
		anicache->addAnimation(ani, "bulletex03");
	}

	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("bullet/bossbullet_01(1).png", Rect(0, 0, 18, 99)));
		ani->addSpriteFrame(SpriteFrame::create("bullet/bossbullet_01(2).png", Rect(0, 0, 24, 99)));
		anicache->addAnimation(ani, "bossbullet01");
	}
	{
		auto ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->addSpriteFrame(SpriteFrame::create("bullet/bossbulletex_01(1).png", Rect(0, 0, 49, 46)));
		ani->addSpriteFrame(SpriteFrame::create("bullet/bossbulletex_01(2).png", Rect(0, 0, 72, 71)));
		anicache->addAnimation(ani, "bossbulletex01");
	}

}

void HelloWorld::update(float dt)
{
	m_background1->setPositionY(m_background1->getPositionY() - 1);
	m_background2->setPositionY(m_background2->getPositionY() - 1);
	if (m_background1->getPositionY() <= 0 - m_background1->getContentSize().height / 2)
	{
		m_background1->setPositionY(m_background2->getPositionY() + m_background1->getContentSize().height);
	}
	if (m_background2->getPositionY() <= 0 - m_background2->getContentSize().height / 2)
	{
		m_background2->setPositionY(m_background1->getPositionY() + m_background2->getContentSize().height);
	}

	Manager::getManager()->update(dt);
	if (!this->getChildByTag(1)->isVisible())
	{
		gameEnd();
	}
}

void HelloWorld::setUIString()
{
	auto dm = DataManager::getDataManager();
	auto score = dm->getScore();
	auto hp = dm->getPlayerHP();
	m_score->setString(StringUtils::format("%05d", score)); 
	auto width = (298.0f * hp) / MAX_HP;
	m_hpBar->setTextureRect(Rect{ 0, 0, width, m_hpBar->getTextureRect().size.height });
}

void HelloWorld::gameEnd()
{
	this->unscheduleUpdate();
	Manager::getManager()->pauseAll();
	Manager::getManager()->releasePlayer();
	Manager::getManager()->releaseLayer();

	auto scene = SceneManager::end();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
}
