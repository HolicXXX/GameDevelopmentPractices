#include "HelloWorldScene.h"
#include "ui\UIButton.h"

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
    
	score = 0;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = LayerColor::create(Color4B(180, 170, 160, 255));
	addChild(backGround);

	scoreLabel = LabelTTF::create(__String::createWithFormat("Scores:%5d",0)->getCString(), "", 80);
	scoreLabel->setPosition(visibleSize.width / 2, visibleSize.height - 80);
	addChild(scoreLabel);

	startX = startY = endX = endY = 0;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&, this](Touch* t, Event* e){
		startX = t->getLocation().x;
		startY = t->getLocation().y;
		return true;
	};

	listener->onTouchEnded = [&, this](Touch* t, Event* e){
		endX = t->getLocation().x - startX;
		endY = t->getLocation().y - startY;

		if (abs(endX) >= abs(endY))
		{
			if (endX > 0)
			{
				if(this->doRight())
					this->addRandomCard();
				this->doCheckGameOver();
			}
			else
			{
				if (this->doLeft())
					this->addRandomCard();
				this->doCheckGameOver();
			}
		}
		else
		{
			if (endY > 0)
			{
				if (this->doUp())
					this->addRandomCard();
				this->doCheckGameOver();
			}
			else
			{
				if (this->doDown())
					this->addRandomCard();
				this->doCheckGameOver();
			}
		}

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	for (int i = 0; i < 4; i++)
	{
		std::vector<Card*> r(4);
		cardVec.push_back(r);
	}

	createCard(visibleSize);
	addRandomCard();
	addRandomCard();

    return true;
}

void HelloWorld::doCheckGameOver()
{
	bool isover = true;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cardVec[i][j]->getNumber() == 0) 
			{
				isover = false;
				break;
			}
			else
			{
				if (j == 0)
				{
					if (i == 0)
					{
						if (cardVec[i][j]->getNumber() == cardVec[i][j + 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i + 1][j]->getNumber()
							)
						{
							isover = false;
							break;
						}
					}
					else if (i == 3)
					{
						if (cardVec[i][j]->getNumber() == cardVec[i][j + 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i - 1][j]->getNumber()
							)
						{
							isover = false;
							break;
						}
					}
					else
					{
						if (cardVec[i][j]->getNumber() == cardVec[i][j + 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i - 1][j]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i + 1][j]->getNumber()
							)
						{
							isover = false;
							break;
						}
					}
				}
				else if (j == 3)
				{
					if (i == 0)
					{
						if (cardVec[i][j]->getNumber() == cardVec[i][j - 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i + 1][j]->getNumber()
							)
						{
							isover = false;
							break;
						}
					}
					else if (i == 3)
					{
						if (cardVec[i][j]->getNumber() == cardVec[i][j - 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i - 1][j]->getNumber()
							)
						{
							isover = false;
							break;
						}
					}
					else
					{
						if (cardVec[i][j]->getNumber() == cardVec[i][j - 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i - 1][j]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i + 1][j]->getNumber()
							)
						{
							isover = false;
							break;
						}
					}
				}
				else
				{
					if (i == 0)
					{
						if (cardVec[i][j]->getNumber() == cardVec[i][j + 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i][j - 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i + 1][j]->getNumber()
							)
						{
							isover = false;
							break;
						}
					}
					else if (i == 3)
					{
						if (cardVec[i][j]->getNumber() == cardVec[i][j + 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i][j - 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i - 1][j]->getNumber()
							)
						{
							isover = false;
							break;
						}
					}
					else
					{
						if (cardVec[i][j]->getNumber() == cardVec[i][j + 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i][j - 1]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i + 1][j]->getNumber() ||
							cardVec[i][j]->getNumber() == cardVec[i - 1][j]->getNumber()
							)
						{
							isover = false;
							break;
						}
					}
				}
			}
		}
		if (!isover)
			break;
	}
	if (isover)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->removeChild(cardVec[i][j]);

		auto size = Director::getInstance()->getVisibleSize();
		auto endlabel = LabelTTF::create("Game Over!", "", 100);
		endlabel->setPosition(size / 2);
		this->addChild(endlabel);

		auto menulabel = MenuItemFont::create("Try Again!", CC_CALLBACK_1(HelloWorld::retCallBack, this));
		menulabel->setFontSize(100);
		auto menu = Menu::createWithItem(menulabel);
		menu->setPosition(size.width / 2, size.height / 2 - endlabel->getContentSize().height);
		addChild(menu);

	}
}

void HelloWorld::addRandomCard()
{
	int x = CCRANDOM_0_1() * 4;
	int y = CCRANDOM_0_1() * 4;
	if (cardVec[x][y]->getNumber() > 0)
		addRandomCard();
	else
		cardVec[x][y]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
}

void HelloWorld::createCard(cocos2d::Size size)
{
	int w = (size.width - 40) / 4;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			auto card = Card::create(0, w, w, w*j + 20, w*(3 - i) + 20 + size.height / 6);
			addChild(card);

			cardVec[i][j] = card;
		}

}
bool HelloWorld::doLeft()
{
	bool isdo = false;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			for (int y = j + 1; y < 4; y++)
			{
				if (cardVec[i][y]->getNumber() > 0)
				{
					if (cardVec[i][j]->getNumber() <= 0)
					{
						cardVec[i][j]->setNumber(cardVec[i][y]->getNumber());
						cardVec[i][y]->setNumber(0);

						j--;
						isdo = true;
					}
					else if (cardVec[i][j]->getNumber() == cardVec[i][y]->getNumber())
					{
						cardVec[i][j]->setNumber(cardVec[i][j]->getNumber() * 2);
						cardVec[i][y]->setNumber(0);

						cardVec[i][j]->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f), ScaleTo::create(0.1f, 1.0f), nullptr));

						score += cardVec[i][j]->getNumber();
						scoreLabel->setString(__String::createWithFormat("Scores:%5d", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	return isdo;
}
bool HelloWorld::doRight()
{
	bool isdo = false;

	for (int i = 0; i < 4; i++)
		for (int j = 3; j >= 0; j--)
		{
			for (int y = j - 1; y >= 0; y--)
			{
				if (cardVec[i][y]->getNumber() > 0)
				{
					if (cardVec[i][j]->getNumber() <= 0)
					{
						cardVec[i][j]->setNumber(cardVec[i][y]->getNumber());
						cardVec[i][y]->setNumber(0);

						j++;
						isdo = true;
					}
					else if (cardVec[i][j]->getNumber() == cardVec[i][y]->getNumber())
					{
						cardVec[i][j]->setNumber(cardVec[i][j]->getNumber() * 2);
						cardVec[i][y]->setNumber(0);

						cardVec[i][j]->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f), ScaleTo::create(0.1f, 1.0f), nullptr));

						score += cardVec[i][j]->getNumber();
						scoreLabel->setString(__String::createWithFormat("Scores:%5d", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	return isdo;
}
bool HelloWorld::doUp()
{
	bool isdo = false;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			for (int y = j + 1; y < 4; y++)
			{
				if (cardVec[y][i]->getNumber() > 0)
				{
					if (cardVec[j][i]->getNumber() <= 0)
					{
						cardVec[j][i]->setNumber(cardVec[y][i]->getNumber());
						cardVec[y][i]->setNumber(0);

						j--;
						isdo = true;
					}
					else if (cardVec[j][i]->getNumber() == cardVec[y][i]->getNumber())
					{
						cardVec[j][i]->setNumber(cardVec[j][i]->getNumber() * 2);
						cardVec[y][i]->setNumber(0);

						cardVec[j][i]->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f), ScaleTo::create(0.1f, 1.0f), nullptr));

						score += cardVec[j][i]->getNumber();
						scoreLabel->setString(__String::createWithFormat("Scores:%5d", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	return isdo;
}
bool HelloWorld::doDown()
{
	bool isdo = false;

	for (int i = 0; i < 4; i++)
		for (int j = 3; j >= 0; j--)
		{
			for (int y = j - 1; y >= 0; y--)
			{
				if (cardVec[y][i]->getNumber() > 0)
				{
					if (cardVec[j][i]->getNumber() <= 0)
					{
						cardVec[j][i]->setNumber(cardVec[y][i]->getNumber());
						cardVec[y][i]->setNumber(0);

						j++;
						isdo = true;
					}
					else if (cardVec[j][i]->getNumber() == cardVec[y][i]->getNumber())
					{
						cardVec[j][i]->setNumber(cardVec[j][i]->getNumber() * 2);
						cardVec[y][i]->setNumber(0);

						cardVec[j][i]->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f), ScaleTo::create(0.1f, 1.0f), nullptr));

						score += cardVec[j][i]->getNumber();
						scoreLabel->setString(__String::createWithFormat("Scores:%5d", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	return isdo;
}

void HelloWorld::retCallBack(Ref* ref)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene()));
}
