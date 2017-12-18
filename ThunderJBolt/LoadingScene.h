#ifndef _LOADINGSCENE_H_
#define _LOADINGSCENE_H_

#include "cocos2d.h"

class LoadingScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(const std::function<cocos2d::Scene*()>& func);
	static LoadingScene* create(const std::function<cocos2d::Scene*()>& func);
	virtual bool init(const std::function<cocos2d::Scene*()>& func);
};

#endif