#pragma once
#include "rule.h"
#include <valarray>

class texas : public rule
{
private:
	const int m_Max_num;
	vector<int> lastbet;
	vector<card> temp;
	int m_bet_max;
	int m_round;
	int m_winner_index;
	int turn(Color);
	bool line(int);
	bool flower(int);
	bool four(int);
	bool fullhouse(int);
	bool three(int);
	bool twopairs(int);
	bool onepair(int);
	void highcard(int);
	void showType(unsigned long);
public:
	texas(string & name, player * real, int pnum = 8);
	virtual ~texas() {};
	void setBegin();
	void round();
	void sort(vector<card> &);
	void playerCardType(int index);
	void settlement();//
	virtual void sendCards();
	virtual void judge();
};
