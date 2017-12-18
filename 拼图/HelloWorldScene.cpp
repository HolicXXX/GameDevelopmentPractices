#include "HelloWorldScene.h"
#include "CuttingPhotos.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label1 = LabelTTF::create("3 X 3", "", 36);
	label1->setColor(Color3B::BLACK);
	label1->setPosition(visibleSize / 2);
	addChild(label1);

	SimpleAudioEngine::getInstance()->preloadEffect("FX085.mp3");

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [&](Touch* t, Event* e){
		auto tar = e->getCurrentTarget();
		Point localposition = tar->convertToNodeSpace(t->getLocation());
		Rect rect{ 0, 0, tar->getContentSize().width, tar->getContentSize().height };
		if (rect.containsPoint(localposition))
		{
			SimpleAudioEngine::getInstance()->playEffect("FX085.mp3");
			auto scene = CuttingPhotos::createScene("turtle.jpg", 3, 3);
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, label1);


	auto label2 = LabelTTF::create("5 X 5", "", 36);
	label2->setColor(Color3B::BLACK);
	label2->setPosition(visibleSize.width / 2,visibleSize.height / 2 - label2->getContentSize().height);
	addChild(label2);

	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [&](Touch* t, Event* e){
		auto tar = e->getCurrentTarget();
		Point localposition = tar->convertToNodeSpace(t->getLocation());
		Rect rect{ 0, 0, tar->getContentSize().width, tar->getContentSize().height };
		if (rect.containsPoint(localposition))
		{
			SimpleAudioEngine::getInstance()->playEffect("FX085.mp3");
			auto scene = CuttingPhotos::createScene("turtle.jpg", 5, 5);
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, label2);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);



	/*
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    */
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
