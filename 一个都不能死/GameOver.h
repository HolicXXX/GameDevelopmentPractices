#pragma once

#include "cocos2d.h"
USING_NS_CC;

class GameOver : public LayerColor
{
	void onClickCallBack(Ref* ref);
public:
	virtual bool init();
	CREATE_FUNC(GameOver);
	static Scene* createWithScene();
};