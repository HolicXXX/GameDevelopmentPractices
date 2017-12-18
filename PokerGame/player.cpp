#include "player.h"

player::player(string & name, int money)
{
	m_name = name;
	m_chips = money;
	card_sum_num1 = 0;
	card_sum_num2 = 0;
	if_discard = false;
}

void player::getCard(card c)
{
	if_discard = false;
	m_handcards.push_back(c);
}

void player::addCard(card c)
{
	m_handcards.push_back(c);
}

void player::showPlayer()
{
	cout << m_name << " :" << m_chips << endl;
}

void player::showHandCards()
{
	for (int i = 0; i < m_handcards.size(); i++)
	{
		m_handcards[i].showCard();
	}
	cout << endl;
}

bool player::bet(int chips)
{
	if (m_chips < chips)
	{
		cout << m_name << " don't have enough chips." << endl;
		return false;
	}
	else
	{
		cout << m_name << " bet " << chips << " chips.\n";
		m_chips -= chips;
		return true;
	}
}

const card & player::retHandCard(int index)
{
	return m_handcards[index];
}

void player::discards()
{
	m_handcards.clear();
	card_sum_num1 = 0;
	card_sum_num2 = 0;
	if_discard = true;
}
