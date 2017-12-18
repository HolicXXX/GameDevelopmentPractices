#ifndef _ENDSCENE_H_
#define _ENDSCENE_H_

#include "cocos2d.h"

class EndScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static EndScene* create();
	virtual bool init();
};



#endif