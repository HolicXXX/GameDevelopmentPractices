#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum Color {Spade,Heart,Club,Diamond/*,Joker*/};

class card
{
private:
	Color m_Color;
	int m_Num;
public:
	card(int index);
	void showCard();
	bool operator<(const card &);
	Color retColor() const { return m_Color; }
	int retNum() const { return m_Num; }
};