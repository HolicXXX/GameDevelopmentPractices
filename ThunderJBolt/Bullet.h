#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"

class Bullet : public cocos2d::Sprite
{
public:
	static Bullet* create(const std::string& str);
	virtual bool init(const std::string& str);

	void initBullet(int type,const cocos2d::Vec2& dir,float speed = 0, unsigned int demage = 0);
	void endCall();

	unsigned int getDemage() { return m_demage; }
	void setType(int t){ m_type = t; }
	int getType(){ return m_type; }

	void setSpeed(float s){ m_speed = s; };
	void setDemage(unsigned int d){ m_demage = d; }
	void setDir(const cocos2d::Vec2& dir){ m_dir = dir; }
	virtual void update(float dt);
private:
	float m_speed;
	unsigned int m_demage;
	cocos2d::Vec2 m_dir;
	int m_type;
};


#endif