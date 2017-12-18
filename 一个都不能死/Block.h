#pragma once 
#include "cocos2d.h"

class Block : public cocos2d::Sprite
{
public:
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(Block);
};