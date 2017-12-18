#include "rule.h"

rule::rule(string & name,player * real)
{
	game_name = name;
	pool = 0;
	player_list.push_back(real);
	resetCards();
}

rule::~rule()
{
	for (int i = 0; i < player_list.size(); i++)
	{
		delete player_list[i];
		player_list[i] = nullptr;
	}
	player_list.clear();
}

void rule::resetCards()
{
	CardLib.clear();
	pubCards.clear();
	for (int i = 0; i < 52;i++)
		CardLib.push_back(card(i));
	for (int i = 0; i < player_list.size(); i++)
		player_list[i]->discards();
}

void rule::showPubCards()
{
	for (int i = 0; i < pubCards.size(); i++)
	{
		pubCards[i].showCard();
	}
	cout << endl;
}



