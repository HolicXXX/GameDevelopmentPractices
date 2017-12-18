#include "EndScene.h"
#include "SceneManager.h"
#include "DataManager.h"
USING_NS_CC;

EndScene* EndScene::create()
{
	auto endscene = new EndScene();
	if (endscene && endscene->init())
	{
		endscene->autorelease();
		return endscene;
	}
	CC_SAFE_DELETE(endscene);
	return nullptr;
}

Scene* EndScene::createScene()
{
	auto l = EndScene::create();

	auto s = Scene::create();

	s->addChild(l);

	return s;
}

bool EndScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("background/end.jpg");
	background->setPosition(size / 2);
	this->addChild(background);

	auto sumBackGround = Sprite::create("ui/pause_bg.png");
	sumBackGround->setPosition(size.width / 2,size.height / 3 * 2);
	this->addChild(sumBackGround);

	auto scoreLabel = MenuItemImage::create("ui/achievescore.png", "ui/achievescore.png", [](Ref*){});

	auto planeNumLabel = MenuItemImage::create("ui/defeatplane.png","ui/achievescore.png" ,[](Ref*){});

	auto sc = StringUtils::format("%05d", DataManager::getDataManager()->getScore());
	auto scnode = Node::create();
	for (int i = 0; i < sc.length(); i++)
	{
		char c[2] = {};
		c[0] = sc.at(i);
		auto num = Sprite::create(StringUtils::format("ui/achieve%s.png", c));
		num->setPosition(i * num->getContentSize().width, 0);
		scnode->addChild(num);
	}
	scnode->setPosition(scoreLabel->getContentSize().width / 2 * 3, scoreLabel->getContentSize().height / 2);
	scoreLabel->addChild(scnode);

	auto plnum = StringUtils::format("%03d", DataManager::getDataManager()->getDefeatEnemyNum());
	auto numnode = Node::create();
	for (int i = 0; i < plnum.length(); i++)
	{
		char c[2] = {};
		c[0] = plnum.at(i);
		auto num = Sprite::create(StringUtils::format("ui/achieve%s.png", c));
		num->setPosition(i * num->getContentSize().width, 0);
		numnode->addChild(num);
	}
	numnode->setPosition(planeNumLabel->getContentSize().width / 2 * 3, planeNumLabel->getContentSize().height / 2);
	planeNumLabel->addChild(numnode);

	auto menu = Menu::create(scoreLabel, planeNumLabel, nullptr);
	menu->alignItemsVerticallyWithPadding(50);
	menu->setPosition(sumBackGround->getContentSize().width / 3, sumBackGround->getContentSize().height / 2);
	sumBackGround->addChild(menu);

	auto restart = MenuItemImage::create("ui/button_bg_normal.png", "ui/button_bg_selected.png", [](Ref*)->void{
		auto scene = SceneManager::load(SceneManager::game);
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
	});
	auto restartLabel = Label::createWithTTF("Restart", "fonts/arial.ttf", 48);
	restartLabel->setPosition(restart->getContentSize() / 2);
	restartLabel->setTextColor(Color4B::BLACK);
	restart->addChild(restartLabel);

	auto end = MenuItemImage::create("ui/button_bg_normal.png", "ui/button_bg_selected.png", [](Ref*)->void{
		Director::getInstance()->end();
	});
	auto endLable = Label::createWithTTF("End", "fonts/arial.ttf", 48);
	endLable->setPosition(end->getContentSize() / 2);
	endLable->setTextColor(Color4B::BLACK);
	end->addChild(endLable);

	auto button = Menu::create(restart, end, nullptr);
	button->alignItemsHorizontallyWithPadding(50);
	button->setPosition(size.width / 2, size.height / 4);
	this->addChild(button);


	return true;
}