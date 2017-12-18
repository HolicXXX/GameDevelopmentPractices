#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
#include "Launcher.h"

enum moveDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Hero : public cocos2d::Sprite
{
public:
	static Hero* create(const std::string& str);
	virtual bool init(const std::string& str);
	virtual void update(float dt);

	void initListener();

	void hpDown();
	void getHit(int d);

	void pauseAll();

	void setBulletType(int b){ m_bulletType = b; m_Launcher->setType(b); }
	int getBulletType(){ return m_bulletType; }

	bool isShout(){ return m_isshout; }

	void getBuff(int type);
	void initLauncher(int type);
private:
	int m_hp;
	bool m_isshout;
	cocos2d::Vec2 m_moveStep;
	int m_bulletType;

	Launcher* m_Launcher;

	cocos2d::EventListenerKeyboard* m_klistener;

	cocos2d::Animation* m_upAni;
	cocos2d::Animation* m_backAni;
	void addDir(moveDirection,bool);
};


#endif