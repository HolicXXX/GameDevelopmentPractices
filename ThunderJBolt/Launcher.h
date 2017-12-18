#ifndef _LAUNCHER_H_
#define _LAUNCHER_H_

#include "Bullet.h"

enum LauncherType
{
	PLAYER_LAUNCHER,
	ENEMY_LAUNCHER,
	BOSS_LAUNCHER
};

class Launcher : public cocos2d::Node
{
public:
	static Launcher* create();
	virtual bool init();
	virtual void update(float dt);

	void setLauncherType(LauncherType l){ m_ltype = l; }
	LauncherType getLauncherType(){ return m_ltype; }
	void setType(int t){ m_type = t; }
	int getType(){ return m_type; }
	void setLevel(int l);
	int getLevel(){ return m_level; }
	void setShoot(bool b){ m_isshoot = b; }
	bool isShoot(){ return m_isshoot; }

	void produceBullet();
private:
	LauncherType m_ltype;
	int m_type;
	int m_level;
	bool m_isshoot;
	int m_count;
};


#endif