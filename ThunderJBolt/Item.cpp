#include "Item.h"
USING_NS_CC;

Item* Item::create(const std::string& src, int type)
{
	auto i = new Item();
	if (i && i->init(src, type))
	{
		i->autorelease();
		return i;
	}
	CC_SAFE_DELETE(i);
	return nullptr;
}

bool Item::init(const std::string& src, int type)
{
	if (!this->initWithFile(src))
	{
		return false;
	}

	m_type = type;

	this->runAction(RepeatForever::create(MoveBy::create(1.0f, Vec2(CCRANDOM_0_1() * 10,- CCRANDOM_0_1() * 100))));

	return true;
}