
#ifndef _MONSTERMANAGER_H_
#define _MONSTERMANAGER_H_

#include "Monster.h"

#define MAX_MONSTER_NUM 10
class MonsterManager : public Node
{
public:
	CREATE_FUNC(MonsterManager);
	virtual bool init();

	virtual void update(float dt);

	void bindPlayer(Player* player);
private:
	void craeteMonster();
	Player* m_player;
	Vector<Monster*> m_monsters;

};


#endif