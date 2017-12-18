#pragma once

#include "cocos2d.h"

class Edge : public cocos2d::Node
{
public:
	virtual bool init();
	static Edge* create();
};