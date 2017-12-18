#include "Block.h"

USING_NS_CC;

bool Block::init()
{
	Sprite::init();

	Size size = Director::getInstance()->getVisibleSize();
	Size s = Size(CCRANDOM_0_1() * 20 + 5, CCRANDOM_0_1() * 50 + 10);


	setTextureRect(Rect(0, 0, s.width, s.height));
	setPhysicsBody(PhysicsBody::createBox(s));
	setColor(Color3B::BLACK);
	setPositionX(size.width);
	setContentSize(s);
	
	
	scheduleUpdate();

	getPhysicsBody()->setDynamic(false);
	return true;
}

void Block::update(float dt)
{
	this->setPositionX(getPositionX() - 3);
	if (getPositionX() < 0)
	{
		log("removed");
		unscheduleUpdate();
		removeFromParent();
	}
}

