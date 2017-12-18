#include "SceneManager.h"
#include "StartScene.h"
#include "HelloWorldScene.h"
#include "EndScene.h"
#include "LoadingScene.h"
#include "LevelSelectScene.h"
USING_NS_CC;

Scene* SceneManager::start()
{
	return StartScene::createScene();
}

Scene* SceneManager::levelSelected()
{
	return LevelSelectScene::createScene();
}

Scene* SceneManager::load(const std::function<cocos2d::Scene*()>& func)
{
	return LoadingScene::createScene(func);
}

Scene* SceneManager::game()
{
	return HelloWorld::createScene();
}

Scene* SceneManager::end()
{
	return EndScene::createScene();
}