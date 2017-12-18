#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Hero.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void startInit();
	void initUI();
	void loadAnimation();
	void initBackGround();

	virtual void update(float dt);

	void setUIString();
	void gameEnd();
    
    CREATE_FUNC(HelloWorld);
private:
	Hero* m_hero;

	cocos2d::Sprite* m_background1;
	cocos2d::Sprite* m_background2;

	cocos2d::Sprite* m_scoreImage;
	cocos2d::Sprite* m_hpImage;
	cocos2d::Sprite* m_hpBar;
	cocos2d::Sprite* m_hpBG;
	cocos2d::Label* m_score;
};

#endif // __HELLOWORLD_SCENE_H__
