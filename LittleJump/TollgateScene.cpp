#include "TollgateScene.h"
#include "MonsterManager.h"
Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();

	auto layer = TollgateScene::create();

	scene->addChild(layer);
	return scene;
}

bool TollgateScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* titleSprite = Sprite::create("cocos2dbanner.png");
	titleSprite->setPosition(visibleSize.width / 2,visibleSize.height / 4 * 3);
	this->addChild(titleSprite, 2);

	m_player = Player::create();
	m_player->bindSprite(Sprite::create("CloseNormal.png"));
	m_player->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 4));
	this->addChild(m_player, 3);

	initBG();
	
	MonsterManager* mstManager = MonsterManager::create();
	mstManager->bindPlayer(m_player);
	mstManager->setTag(1);
	this->addChild(mstManager, 4);
	
	addScore();
	addButton();
	this->scheduleUpdate();

	return true;
}

void TollgateScene::initBG()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	m_bgSprite1 = Sprite::create("background3.jpg");
	m_bgSprite1->setPosition(visibleSize / 2);
	this->addChild(m_bgSprite1, 0);

	m_bgSprite2 = Sprite::create("background3.jpg");
	m_bgSprite2->setPosition(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2);
	m_bgSprite2->setFlippedX(true);
	this->addChild(m_bgSprite2, 0);

}

void TollgateScene::addButton()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto button = MenuItemFont::create("Jump", CC_CALLBACK_1(TollgateScene::lableCallBack, this));
	auto menu = Menu::createWithItem(button);
	menu->setPosition(size.width / 6 * 5, size.height / 6);
	this->addChild(menu);
}

void TollgateScene::addScore()
{
	m_Score = 0;
	m_scoreLabel = LabelTTF::create(__String::createWithFormat("Scores: %d",m_Score)->getCString(), "fonts/Marker Felt.ttf", 24);
	m_scoreLabel->setColor(Color3B(255, 255, 0));
	m_scoreLabel->setAnchorPoint(Vec2::ZERO);
	m_scoreLabel->setPosition(Vec2(5, m_scoreLabel->getContentSize().height + 10));
	this->addChild(m_scoreLabel);
	m_HPLabel = LabelTTF::create(__String::createWithFormat("HP: %d", m_player->getHP())->getCString(), "fonts/Marker Felt.ttf", 24);
	m_HPLabel->setColor(Color3B(255, 100, 100));
	m_HPLabel->setAnchorPoint(Vec2::ZERO);
	m_HPLabel->setPosition(Vec2(5, 5));
	this->addChild(m_HPLabel);
}

void TollgateScene::lableCallBack(Ref* ref)
{
	m_player->jump();
}

void TollgateScene::update(float dt)
{
	if (m_player->getHP() <= 0)
	{
		restartGame();
	}

	auto posX1 = m_bgSprite1->getPositionX();
	auto posX2 = m_bgSprite2->getPositionX();

	int iSpeed = 1;

	posX1 -= iSpeed;
	posX2 -= iSpeed;

	auto size = m_bgSprite1->getContentSize();

	if (posX1 <= -size.width / 2)
	{
		log("BG1 reset");
		posX1 = size.width / 2 * 3;
	}
	if (posX2 <= -size.width / 2)
	{
		log("BG2 reset");
		posX2 = size.width / 2 * 3;
	}

	m_bgSprite1->setPositionX(posX1);
	m_bgSprite2->setPositionX(posX2);

	
	m_Score += 1;
	m_scoreLabel->setString(__String::createWithFormat("Scores: %d", m_Score)->getCString());
	m_HPLabel->setString(__String::createWithFormat("HP: %d", m_player->getHP())->getCString());
}

void TollgateScene::restartGame()
{
	this->getChildByTag(1)->unscheduleUpdate();
	this->unscheduleUpdate();
	_eventDispatcher->removeAllEventListeners();

	auto size = Director::getInstance()->getVisibleSize();
	auto layer = LayerColor::create(Color4B(255, 255, 255, 150), size.width, size.height);
	layer->ignoreAnchorPointForPosition(false); 
	layer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	layer->setPosition(Vec2(size.width / 2, size.height / 2));
	
	auto layersize = layer->getContentSize();

	auto over = LabelTTF::create("Game Over!", "fonts/Marker Felt.ttf", 24);
	layer->addChild(over);
	over->setColor(Color3B::BLACK);
	over->setPosition(Vec2(layersize.width / 2, layersize.height - over->getContentSize().height));
	
	auto score = LabelTTF::create(__String::createWithFormat("Scores: %d", m_Score)->getCString(), "", 48);
	layer->addChild(score);
	score->setColor(Color3B::YELLOW);
	score->setPosition(Vec2(layersize.width / 2, layersize.height / 2));
	
	auto menuitem1 = MenuItemFont::create("Restart?", CC_CALLBACK_1(TollgateScene::restartCallBack, this));
	menuitem1->setFontSize(24);
	menuitem1->setColor(Color3B::ORANGE);
	auto menuitem2 = MenuItemFont::create("Quit?", CC_CALLBACK_1(TollgateScene::quitCallBack, this));
	menuitem2->setColor(Color3B::GRAY);
	menuitem2->setFontSize(24);

	auto menu = Menu::create(menuitem1, menuitem2, nullptr);
	layer->addChild(menu);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(layersize.width / 2, menuitem1->getContentSize().height));
	
	this->getParent()->addChild(layer);
}

void TollgateScene::restartCallBack(Ref* ref)
{
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f, TollgateScene::createScene(), false));
}

void TollgateScene::quitCallBack(Ref* ref)
{
	Director::getInstance()->end();
}