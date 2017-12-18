#include "LevelSelectScene.h"
#include "SceneManager.h"
#include "DataManager.h"
USING_NS_CC;


Scene* LevelSelectScene::createScene()
{
	auto select = LevelSelectScene::create();

	auto scene = Scene::create();

	scene->addChild(select);

	return scene;
}

LevelSelectScene* LevelSelectScene::create()
{
	auto l = new LevelSelectScene();
	if (l && l->init())
	{
		l->autorelease();
		return l;
	}
	CC_SAFE_DELETE(l);
	return nullptr;
}

bool LevelSelectScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("background/start.jpg");
	background->setPosition(size / 2);
	this->addChild(background);

	auto selectBG = Sprite::create("ui/selectlevel_bg.png");
	selectBG->setPosition(size.width / 2, size.height / 2);
	this->addChild(selectBG);

	auto easy = MenuItemImage::create("ui/easy_normal.png", "ui/easy_selected.png", [](Ref*)->void{
		DataManager::getDataManager()->setLevel(1);
		auto scene = SceneManager::load(SceneManager::game);
		Director::getInstance()->replaceScene(TransitionZoomFlipY::create(0.5f, scene));
	});

	auto usual = MenuItemImage::create("ui/uaual_normal.png", "ui/uaual_selected.png", [](Ref*)->void{
		DataManager::getDataManager()->setLevel(2);
		auto scene = SceneManager::load(SceneManager::game);
		Director::getInstance()->replaceScene(TransitionZoomFlipY::create(0.5f, scene));
	});

	auto defficult = MenuItemImage::create("ui/difficulty_normal.png", "ui/difficulty_selected.png", [](Ref*)->void{
		DataManager::getDataManager()->setLevel(3);
		auto scene = SceneManager::load(SceneManager::game);
		Director::getInstance()->replaceScene(TransitionZoomFlipY::create(0.5f, scene));
	});

	auto menu = Menu::create(easy, usual, defficult, nullptr);
	menu->alignItemsVerticallyWithPadding(50);
	menu->setPosition(selectBG->getContentSize() / 2);
	selectBG->addChild(menu);

	return true;
}