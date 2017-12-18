#include "GameOver.h"
#include "HelloWorldScene.h"

bool GameOver::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
		return false;
	auto size = Director::getInstance()->getVisibleSize();

	auto label = LabelTTF::create("Game Over!", "", 36);
	label->setPosition(size / 2);
	label->setColor(Color3B::RED);
	addChild(label);

	auto retItem = MenuItemFont::create("Try Again",CC_CALLBACK_1(GameOver::onClickCallBack,this));
	retItem->setFontSize(24);
	retItem->setColor(Color3B::BLACK);
	
	auto menu = Menu::createWithItem(retItem);
	menu->setPosition(Vec2(size.width / 2, label->getPosition().y / 2));
	addChild(menu);

	return true;
}

Scene* GameOver::createWithScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);

	return scene;
}

void GameOver::onClickCallBack(Ref* ref)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene()));
}
