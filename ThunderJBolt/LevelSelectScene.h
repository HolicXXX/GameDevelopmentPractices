#ifndef _LEVELSELECTSCENE_H_
#define _LEVELSELECTSCENE_H_

#include "cocos2d.h"

class LevelSelectScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static LevelSelectScene* create();
	virtual bool init();
};


#endif