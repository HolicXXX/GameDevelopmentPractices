
#include "card.h"

card::card(int index)//0-51
{
	switch (index / 13)
	{
	case 0:
		m_Color = Spade;
		break;
	case 1:
		m_Color = Heart;
		break;
	case 2:
		m_Color = Club;
		break;
	case 3:
		m_Color = Diamond;
		break;
	//case 4:
	//	m_Color = Joker;
	//	break;
	default:
		break;
	}
	m_Num = index % 13;
}

void card::showCard()
{
	string s[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	switch (m_Color)
	{
	case Spade:
		cout << char(6) << s[m_Num] << " ";
		break;
	case Heart:
		cout << char(3) << s[m_Num] << " ";
		break;
	case Club:
		cout << char(5) << s[m_Num] << " ";
		break;
	case Diamond:
		cout << char(4) << s[m_Num] << " ";
	//case Joker:
	//	cout << char(2) << (m_Num == 0 ? "1" : "2") << " ";
	//	break;
	default:
		break;
	}
}

bool card::operator<(const card & c2)
{
	if (m_Num < c2.m_Num)
		return true;
	return false;
}



