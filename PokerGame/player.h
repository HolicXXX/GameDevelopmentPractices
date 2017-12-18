#pragma once
#include "card.h"

class player
{
private:
	string m_name;
	vector<card> m_handcards;
	bool if_discard;
	unsigned long card_sum_num1;
	unsigned long card_sum_num2;
	int m_chips;
public:
	player(string & name,int money = 0);
	string & retname() { return m_name; }
	void getChips(int c) { m_chips += c; }
	void getCard(card c);
	void addCard(card c);
	void showPlayer();
	void showHandCards();
	bool bet(int chips);
	const card & retHandCard(int);
	bool ifdiscard() { return if_discard; }
	int retchips() { return m_chips; }
	bool ifleave() { return m_chips <= 10; }
	void discards();
	void settlecards() { m_handcards.clear(); }
	void setcardsum1(unsigned long num) { card_sum_num1 = num; }
	void setcardsum2(unsigned long num) { card_sum_num2 = num; }
	unsigned long retcardsum1() { return card_sum_num1; }
	unsigned long retcardsum2() { return card_sum_num2; }
	//might need discard
};