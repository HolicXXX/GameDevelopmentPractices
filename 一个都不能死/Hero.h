#pragma once

#include "cocos2d.h"

class Hero : public cocos2d::Sprite
{
public:
	virtual bool init(int i);
	static Hero* create(int i);

};