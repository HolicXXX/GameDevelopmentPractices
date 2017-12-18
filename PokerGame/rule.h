#pragma once
#include "player.h"

class rule
{
protected:
	string game_name;
	vector<card> CardLib;
	vector<card> pubCards;
	vector<player*> player_list;
	int pool;

	rule(string & name,player *);
	virtual ~rule();//todo
	virtual void sendCards() = 0;
	void resetCards();
	void showPubCards();
	virtual void judge() = 0;
};