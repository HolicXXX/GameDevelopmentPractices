#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));
    
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
    if ( !LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int num = 3;
	float h = visibleSize.height / num;
	for (int i = 0; i < num; i++)
	{
		gcs.insert(0, GameController::create(this, i * h, h));
	}
	
	auto touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = [&](Touch* t, Event* e){

		for (auto gcit = gcs.begin(); gcit != gcs.end(); gcit++)
		{
			if ((*gcit)->hitTestPoint(t->getLocation()))
			{
				if (!(*gcit)->isJump())
					(*gcit)->onUserTouch();

				break;
			}
		}


		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [&](PhysicsContact& contact){
		this->unscheduleUpdate();
		Director::getInstance()->replaceScene(TransitionMoveInR::create(0.5f,GameOver::createWithScene()));

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();
    return true;
}

void HelloWorld::update(float dt)
{
	for (auto gcit = gcs.begin(); gcit != gcs.end(); gcit++)
	{
		(*gcit)->doUpdate(dt);
	}
}
