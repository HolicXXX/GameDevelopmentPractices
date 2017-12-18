#include "StartScene.h"
#include "SceneManager.h"
USING_NS_CC;

StartScene* StartScene::create()
{
	auto startscene = new StartScene();
	if (startscene && startscene->init())
	{
		startscene->autorelease();
		return startscene;
	}
	CC_SAFE_DELETE(startscene);
	return nullptr;
}

Scene* StartScene::createScene()
{
	auto l = StartScene::create();

	auto s = Scene::create();

	s->addChild(l);

	return s;
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto size = Director::getInstance()->getVisibleSize();

	auto backGround = Sprite::create("background/start.jpg");
	backGround->setPosition(size / 2);
	this->addChild(backGround);

	auto logo = Sprite::create("ui/gamename.png");
	logo->setPosition(size.width / 2,size.height / 3 * 2);
	this->addChild(logo);

	auto anicache = AnimationCache::getInstance();
	auto ani = Animation::create();
	ani->setDelayPerUnit(0.2f);
	for (size_t i = 1; i < 6; i++)
	{
		ani->addSpriteFrame(SpriteFrame::create(StringUtils::format("ui/lighting%d.png",i), Rect(0, 0, 113, 92)));
	}
	anicache->addAnimation(ani, "lighting");

	auto lighting = Sprite::create();
	lighting->setScale(2.0f);
	lighting->setPosition(logo->getContentSize() / 2);
	logo->addChild(lighting);
	lighting->runAction(RepeatForever::create(Animate::create(ani)));

	auto start = MenuItemImage::create("ui/button_bg_normal.png", "ui/button_bg_selected.png", CC_CALLBACK_1(StartScene::startCallBack, this));
	auto label1 = Label::createWithTTF("Start", "fonts/arial.ttf", 48);
	label1->setTextColor(Color4B::BLACK);
	label1->setPosition(start->getContentSize() / 2);
	start->addChild(label1);

	auto score = MenuItemImage::create("ui/button_bg_normal.png", "ui/button_bg_selected.png", CC_CALLBACK_1(StartScene::scoreCallBack, this));
	auto label2 = Label::createWithTTF("Score", "fonts/arial.ttf", 48);
	label2->setTextColor(Color4B::BLACK);
	label2->setPosition(score->getContentSize() / 2);
	score->addChild(label2);

	auto end = MenuItemImage::create("ui/button_bg_normal.png", "ui/button_bg_selected.png", CC_CALLBACK_1(StartScene::endCallBack, this));
	auto label3 = Label::createWithTTF("End", "fonts/arial.ttf", 48);
	label3->setTextColor(Color4B::BLACK);
	label3->setPosition(end->getContentSize() / 2);
	end->addChild(label3);

	auto menu = Menu::create(start, score,end,nullptr);
	menu->alignItemsVerticallyWithPadding(50);
	menu->setPosition(size.width / 2,size.height / 3);
	this->addChild(menu); 

	

	return true;
}

void StartScene::startCallBack(Ref* pSender)
{
	auto scene = SceneManager::levelSelected();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

void StartScene::scoreCallBack(cocos2d::Ref*)
{
	//
}

void StartScene::endCallBack(cocos2d::Ref*)
{
	//
	Director::getInstance()->end();
}