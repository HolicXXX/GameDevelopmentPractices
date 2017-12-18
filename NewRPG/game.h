#pragma once

#include "player.h"
#include "minion.h"
#include "boss.h"

class game
{
private:
	int settlement_Exp;
	bool player_escape;
	bool if_boss;
	charactor * m_player;
	vector<charactor *> m_enemy;
	vector<int> m_enemy_movement;
	void showRoundsOptions();
	void showEnemy();
	int chooseTarget();
	void enemyAct();
public:
	game(player *);
	void town();
	void battlezone();
	void rounds();
	void settlement();
	void battleover();
	//store
	void showBag();
	~game();
};

