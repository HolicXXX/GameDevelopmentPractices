#ifndef _TARGET_H_
#define _TARGET_H_

#include "cocos2d.h"
#include "Launcher.h"

class Target : public cocos2d::Sprite
{
public:
	static Target* create(const std::string& str);
	virtual bool init(const std::string& str);

	void initTarget(const cocos2d::Vec2& dir, float speed = 0, unsigned int demage = 0, unsigned int hp = 0);
	void endCall();

	void getHit(unsigned int d){ m_hp -= d; }
	int getHp(){ return m_hp; }
	unsigned int getDemage(){ return m_demage; }
	void setSpeed(float s){ m_speed = s; };
	void setDemage(unsigned int d){ m_demage = d; }
	void setDir(const cocos2d::Vec2& dir){ m_dir = dir; }
	void setBulletType(int b){ m_bulletType = b; m_Launcher->setType(b); }
	int getBulletType(){ return m_bulletType; }
	void pauseAll();

	void initLauncher(int type);
	virtual void update(float dt);
private:
	int m_hp;
	float m_speed;
	unsigned int m_demage;
	cocos2d::Vec2 m_dir;
	int m_bulletType;

	Launcher* m_Launcher;
};


#endif