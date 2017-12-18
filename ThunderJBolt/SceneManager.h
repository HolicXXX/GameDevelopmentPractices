#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "cocos2d.h"

class SceneManager
{
public:
	static cocos2d::Scene* start();
	static cocos2d::Scene* levelSelected();
	static cocos2d::Scene* load(const std::function<cocos2d::Scene*()>& func);
	static cocos2d::Scene* game();
	static cocos2d::Scene* end();

};


#endif