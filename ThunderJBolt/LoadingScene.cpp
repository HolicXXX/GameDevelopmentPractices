#include "LoadingScene.h"
USING_NS_CC;

Scene* LoadingScene::createScene(const std::function<cocos2d::Scene*()>& func)
{
	auto load = LoadingScene::create(func);

	auto scene = Scene::create();

	scene->addChild(load);

	return scene;
}

LoadingScene* LoadingScene::create(const std::function<cocos2d::Scene*()>& func)
{
	auto l = new LoadingScene();
	if (l && l->init(func))
	{
		l->autorelease();
		return l;
	}
	CC_SAFE_DELETE(l);
	return nullptr;
}

bool LoadingScene::init(const std::function<cocos2d::Scene*()>& func)
{
	if (!Layer::init())
	{
		return false;
	}

	auto size = Director::getInstance()->getVisibleSize();

	auto loadimage = Sprite::create("ui/loading.png");
	loadimage->setPosition(size / 2);
	this->addChild(loadimage);
	auto seq = Sequence::create(Repeat::create(RotateBy::create(1.0f, 180), int(CCRANDOM_0_1() * 3) + 1), CallFunc::create([func]()->void{
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, func()));
	}),nullptr);
	loadimage->runAction(seq);

	auto loadfont = Label::createWithTTF("Loading...", "fonts/arial.ttf", 72);
	loadfont->setPosition(loadimage->getPosition() + Vec2(0, loadimage->getContentSize().height));
	loadfont->setTextColor(Color4B::WHITE);
	this->addChild(loadfont);

	return true;
}