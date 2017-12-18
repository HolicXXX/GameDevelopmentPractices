#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "Player.h"

class Monster : public Entity
{
public:
	Monster();
	~Monster();
	CREATE_FUNC(Monster);
	virtual bool init();
	bool isHitPlayer(Player* player);
public:
	void show();
	void hide();
	void reset();
	bool isAlive();
private:
	bool m_isAlive;
};


#endif