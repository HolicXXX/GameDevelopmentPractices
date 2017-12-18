#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

#define JUMP_ACTION_TAG 1;
class Player : public Entity
{
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();

	void resetData();
	void jump();
	void hit();
	int getHP();
private:
	bool m_isJumping;
	int m_HP;


};

#endif