#ifndef _STARTSCENE_H_
#define _STARTSCENE_H_

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static StartScene* create();
	virtual bool init();

	void startCallBack(cocos2d::Ref*);
	void scoreCallBack(cocos2d::Ref*);
	void endCallBack(cocos2d::Ref*);
};


#endif