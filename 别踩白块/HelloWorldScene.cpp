#include "HelloWorldScene.h"

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
    if ( !Layer::init() )
    {
        return false;
    }
	auto bs = Block::getBlocks();
	bs->clear();
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	gameLayer = Node::create();
	addChild(gameLayer);

	timerLabel = Label::create();
	timerLabel->setTextColor(Color4B::RED);
	timerLabel->setSystemFontSize(36);
	timerLabel->setPosition(visibleSize.width / 2, visibleSize.height - 100);
	timerLabel->setString("0.000");
	addChild(timerLabel);

	startGame();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* t, Event* e)
	{
		auto bs = Block::getBlocks();
		Block* b;
		for (auto it = bs->begin(); it != bs->end(); it++)
		{
			b = *it;
			if (b->getLineIndex() == 1 && b->getBoundingBox().containsPoint(t->getLocation())){
				if (b->getColor() == Color3B::BLACK)
				{
					if (!isRunning)
					{
						this->startTimer();
					}
					b->setColor(Color3B::GRAY);
					this->moveDown();
				}
				else if (b->getColor() == Color3B::GREEN)
				{
					this->stopTimer();
					this->moveDown();
					this->reStart();
				}
				else
				{
					MessageBox("Wrong Block!", "Wrong");
				}
				break;
			}
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelloWorld::reStart()
{
	auto mil = MenuItemFont::create("Again!",CC_CALLBACK_1(HelloWorld::clickCallBack,this));
	mil->setFontSize(48);
	mil->setColor(Color3B::RED);

	auto menu = Menu::createWithItem(mil);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	addChild(menu);
}

void HelloWorld::update(float dt)
{
	long minus = clock() - startTime;

	timerLabel->setString(__String::createWithFormat("%.3f", ((double)minus) / 1000)->getCString());

}

void HelloWorld::startTimer()
{
	if (!isRunning)
	{
		scheduleUpdate();
		startTime = clock();
		isRunning = true;
	}
}

void HelloWorld::stopTimer()
{
	if (isRunning)
	{
		unscheduleUpdate();
		isRunning = false;
	}
}

void HelloWorld::startGame()
{
	isRunning = false;
	lineCount = 0;
	showEnd = false;
	addStartLine();
	addNormalLine(1);
	addNormalLine(2);
	addNormalLine(3);
}

void HelloWorld::addStartLine()
{
	auto b = Block::createWithArgs(Color3B::YELLOW, Size(visibleSize.width, visibleSize.height / 4),"Start!");
	gameLayer->addChild(b);
	b->setLineIndex(0);
}

void HelloWorld::addEndLine()
{
	auto b = Block::createWithArgs(Color3B::GREEN, visibleSize, "Game Over!", 32, Color4B::BLACK);
	b->setLineIndex(4);
	gameLayer->addChild(b);
}

void HelloWorld::addNormalLine(int index)
{
	Block* b;
	int blackIndex = CCRANDOM_0_1() * 4;
	for (int i = 0; i < 4; i++)
	{
		b = Block::createWithArgs(i == blackIndex? Color3B::BLACK : Color3B::WHITE,Size(visibleSize.width / 4 - 1,visibleSize.height / 4 - 1));
		gameLayer->addChild(b);
		b->setPosition(Vec2(visibleSize.width / 4 * i, index * visibleSize.height / 4));
		b->setLineIndex(index);
	}
	lineCount++;
}

void HelloWorld::moveDown()
{
	if (lineCount < 50)
		addNormalLine(4);
	else if (!showEnd)
	{
		showEnd = true;
		addEndLine();
	}

	auto bs = Block::getBlocks();

	for (auto it = bs->begin(); it != bs->end(); it++)
	{
		(*it)->moveDown();
	}

}

void HelloWorld::clickCallBack(Ref* ref)
{
	/*auto bs = Block::getBlocks();

	for (auto it = bs->begin(); it != bs->end(); it++)
	{
		(*it)->removeBlock();
	}*/

	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.5f, HelloWorld::createScene()));
}


