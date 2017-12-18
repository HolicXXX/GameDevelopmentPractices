#include "Hero.h"
#include "FlashTool.h"
USING_NS_CC;

Hero* Hero::create(int i)
{
	auto hero = new Hero();
	if (hero && hero->init(i))
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

bool Hero::init(int i)
{
	Sprite::init();

	Size s = Size(44, 52);

	this->setSpriteFrame(SpriteFrame::create("Hero.png", Rect(0, 0, 44, 52)));

	runAction(RepeatForever::create(FlashTool::readJsonSpriteSheet("Hero.json",0.2f)));

	setPhysicsBody(PhysicsBody::createBox(s));
	setContentSize(s);

	getPhysicsBody()->setRotationEnable(false);
	getPhysicsBody()->setContactTestBitmask(i);
	return true;
}