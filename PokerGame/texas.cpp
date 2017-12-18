#include "texas.h"
#include <cmath>

texas::texas(string & name, player * real,int pnum)
	:rule(name,real), m_Max_num(pnum)
{
	m_winner_index = -1;
	lastbet.push_back(0);
	m_round = 0;
	cout << real->retname() << " welcome to Texas Hold'em Poker.\n";
}

void texas::setBegin()
{
	while (true)
	{
		if (player_list.size() < m_Max_num)
		{
			player_list.push_back(new player(string("comp"), rand() % 500 + 501));
			lastbet.push_back(0);
			cout << "New player enter.\n";
			player_list[player_list.size() - 1]->showPlayer();
		}
		else
			break;
	}
	for (int i = 0; i < player_list.size(); i++)
	{
		player_list[i]->bet(10);
		lastbet[i] = 10;
		pool += 10;
	}
	m_bet_max = 10;
	cout << "Pool: " << pool << endl;
}

void texas::round()
{
	int choice;
	int ran;
	for (m_round = 1; m_round <= 4; m_round++)
	{
		switch (m_round)
		{
		case 2:
			ran = rand() % CardLib.size();
			pubCards.push_back(CardLib[ran]);
			CardLib.erase(CardLib.begin() + ran);
			ran = rand() % CardLib.size();
			pubCards.push_back(CardLib[ran]);
			CardLib.erase(CardLib.begin() + ran);
			ran = rand() % CardLib.size();
			pubCards.push_back(CardLib[ran]);
			CardLib.erase(CardLib.begin() + ran);
			cout << "Public Cards: ";
			showPubCards();
			break;
		case 3:
			ran = rand() % CardLib.size();
			pubCards.push_back(CardLib[ran]);
			CardLib.erase(CardLib.begin() + ran);
			cout << "Public Cards: ";
			showPubCards();
			break;
		case 4:
			ran = rand() % CardLib.size();
			pubCards.push_back(CardLib[ran]);
			CardLib.erase(CardLib.begin() + ran);
			cout << "Public Cards: ";
			showPubCards();
			break;
		default:
			break;
		}
		if (!player_list[0]->ifdiscard())
		{
			cout << "Your HandCards: ";
			player_list[0]->showHandCards();
			cout << "Choose your movement: #1: Bet #2: Discard #3: Quit\n";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				int bet_num;
				while (true)
				{
					cout << "Minimum bet: " << m_bet_max << endl;
					cout << "Your chips: " << player_list[0]->retchips() << endl;
					if (player_list[0]->retchips() < m_bet_max)
					{
						cout << "You can't call the bet.\n";
						cout << "#1: " << player_list[0]->retname() << " disards.\n";
						player_list[0]->showHandCards();
						player_list[0]->discards();
						break;
					}
					cout << "Your bet: ";
					cin >> bet_num;
					if (bet_num < m_bet_max)
					{
						cout << "Your bet is too small,input again.\n";
						continue;
					}
					if (player_list[0]->bet(bet_num))
					{
						m_bet_max = bet_num;
						pool += bet_num;
						lastbet[0] = bet_num;
						break;
					}
				}
			}
			break;
			case 2:
				player_list[0]->discards();
				break;
			case 3:
				cout << "Quit Texas.\n";
				system("pause");
				exit(0);//
			default:
				break;
			}
		}
		//might need AI
		for (int i = 1; i < player_list.size(); i++)
		{
			if (!player_list[i]->ifdiscard())
			{
				if (!player_list[i]->bet(m_bet_max))
				{
					cout << "#" << i + 1 << ": " << player_list[i]->retname() << " disards.\n";
					player_list[i]->showHandCards();
					player_list[i]->discards();
				}
				pool += m_bet_max;
				player_list[i]->showHandCards();
			}
		}
	}
}

void texas::settlement()
{
	for (int i = 0; i < player_list.size(); i++)
		lastbet[i] = 0;
	pool = 0;
	m_winner_index = -1;
	resetCards();
	for (int i = 0; i < player_list.size(); i++)
	{
		if (player_list[i]->ifleave())
			player_list.erase(player_list.begin() + i);
	}
}

void texas::sendCards()
{
	int ran = 0;
	for (int i = 0; i < player_list.size(); i++)
	{
		ran = rand() % CardLib.size();
		player_list[i]->getCard(CardLib[ran]);
		CardLib.erase(CardLib.begin() + ran);
		ran = rand() % CardLib.size();
		player_list[i]->getCard(CardLib[ran]);
		CardLib.erase(CardLib.begin() + ran);
	}
}

void texas::sort(vector<card>& allcards)
{
	for (int i = 0; i < pubCards.size(); i++)
	{
		allcards.push_back(pubCards[i]);
	}
	card temp(0);
	for (int i = 0; i < 6; i++)
	{
		for (int j = i + 1; j < 7; j++)
		{
			if (allcards[i] < allcards[j])
			{
				temp = allcards[i];
				allcards[i] = allcards[j];
				allcards[j] = temp;
			}
			else if (allcards[i].retNum() == allcards[j].retNum())
			{
				if (turn(allcards[i].retColor()) < turn(allcards[j].retColor()))
				{
					temp = allcards[i];
					allcards[i] = allcards[j];
					allcards[j] = temp;
				}
			}
		}
	}
}

int texas::turn(Color c)
{
	switch (c)
	{
	case Spade:
		return 4;
	case Heart:
		return 3;
	case Club:
		return 2;
	case Diamond:
		return 1;
	default:
		return 0;
	}
}

bool texas::line(int index)
{
	bool ifline = false;
	int linestart = 0;
	for (int i = 0; i < 3; i++)
	{
		if (temp[i].retNum() - temp[i + 1].retNum() == 1
			&& temp[i + 1].retNum() - temp[i + 2].retNum() == 1
			&& temp[i + 2].retNum() - temp[i + 3].retNum() == 1
			&& temp[i + 3].retNum() - temp[i + 4].retNum() == 1)
		{
			linestart = i;
			ifline = true;
			break;
		}
	}
	if (ifline)
	{
		player_list[index]->settlecards();
		for (int i = linestart; i < linestart + 5; i++)
		{
			player_list[index]->addCard(temp[i]);
		}
	}
	return ifline;
}

bool texas::flower(int index)
{
	bool ifflower = false;
	vector<int> flowerindex;
	for (int i = 0; i < 3 ; i++)
	{
		flowerindex.push_back(i);
		for (int j = i + 1; j < 7; j++)
		{
			if (temp[i].retColor() == temp[j].retColor())
				flowerindex.push_back(j);
		}
		if (flowerindex.size() >= 5)
		{
			ifflower = true;
			break;
		}
		flowerindex.clear();
	}
	if (ifflower)
	{
		player_list[index]->settlecards();
		for (int i = 0; i < 5; i++)
			player_list[index]->addCard(temp[flowerindex[i]]);
	}
	return ifflower;
}

bool texas::four(int index)
{
	bool iffour = false;
	int start = 0;
	for (int i = 0; i < 4; i++)
	{
		if (temp[i].retNum() == temp[i + 1].retNum() && temp[i + 1].retNum() == temp[i + 2].retNum() && temp[i + 2].retNum() == temp[i + 3].retNum())
		{
			iffour = true;
			start = i;
			break;
		}
	}
	if (iffour)
	{
		player_list[index]->settlecards();
		if (start == 0)
		{
			for (int i = 0; i < 5; i++)
				player_list[index]->addCard(temp[i]);
		}
		else 
		{
			for (int i = start; i < 4; i++)
				player_list[index]->addCard(temp[i]);
			player_list[index]->addCard(temp[0]);
		}
	}
	return iffour;
}

bool texas::fullhouse(int index)
{
	bool iffull = false;
	int threestart = 0;
	int twostart = 0;
	for (int i = 0; i < 5; i++)
	{
		if (temp[i].retNum() == temp[i + 1].retNum() && temp[i + 1].retNum() == temp[i + 2].retNum())
		{
			threestart = i;
			if (i <= 1)
			{
				for (int j = i + 3; j < temp.size(); j++)
				{
					if (temp[j].retNum() == temp[j].retNum())
					{
						twostart = j;
						iffull = true;
						break;
					}
				}
				if (iffull)
					break;
			}
			else if (i + 2 >= temp.size() - 2)
			{
				for (int j = 0; j < i; j++)
				{
					if (temp[j].retNum() == temp[j].retNum())
					{
						twostart = j;
						iffull = true;
						break;
					}
				}
				if (iffull)
					break;
			}
			else
			{
				if (temp[0].retNum() == temp[1].retNum())
				{
					twostart = 0;
					iffull = true;
					break;
				}
				else if (temp[temp.size() - 2].retNum() == temp[temp.size() - 1].retNum())
				{
					twostart = temp.size() - 2;
					iffull = true;
					break;
				}
			}
		}
	}
	if (iffull)
	{
		player_list[index]->settlecards();
		player_list[index]->addCard(temp[threestart]);
		player_list[index]->addCard(temp[threestart + 1]);
		player_list[index]->addCard(temp[threestart + 2]);
		player_list[index]->addCard(temp[twostart]);
		player_list[index]->addCard(temp[twostart + 1]);
	}
	return iffull;
}

bool texas::three(int index)
{
	bool ifthree = false;
	int threestart = 0;
	for (int i = 0; i < 5; i++)
	{
		if (temp[i].retNum() == temp[i + 1].retNum() && temp[i + 1].retNum() == temp[i + 2].retNum())
		{
			threestart = i;
			ifthree = true;
			break;
		}
	}
	if (ifthree)
	{
		player_list[index]->settlecards();
		if (threestart == 0)
		{
			for (int i = 0; i < 5; i++)
				player_list[index]->addCard(temp[i]);
		}
		else if (threestart == 1)
		{
			for (int i = threestart; i < 4; i++)
				player_list[index]->addCard(temp[i]);
			player_list[index]->addCard(temp[0]);
			player_list[index]->addCard(temp[4]);
		}
		else
		{
			for (int i = threestart; i < threestart + 3;i++)
				player_list[index]->addCard(temp[i]);
			player_list[index]->addCard(temp[0]);
			player_list[index]->addCard(temp[1]);
		}
	}
	return ifthree;
}

bool texas::twopairs(int index)
{
	bool iftwopairs = false;
	int onepairstart = 0;
	int twopairstart = 0;
	for (int i = 0; i < 6; i++)
	{
		if (temp[i].retNum() == temp[i + 1].retNum())
		{
			onepairstart = i;
			for (int j = i + 2; j < 6; j++)
			{
				if (temp[j].retNum() == temp[j + 1].retNum())
				{
					twopairstart = j;
					iftwopairs = true;
					break;
				}
			}
			if (iftwopairs)
				break;
		}
	}
	if (iftwopairs)
	{
		player_list[index]->settlecards();
		if (onepairstart == 0)
		{
			if (twopairstart == 2)
			{
				for (int i = 0; i < 5; i++)
					player_list[index]->addCard(temp[i]);
			}
			else
			{
				player_list[index]->addCard(temp[onepairstart]);
				player_list[index]->addCard(temp[onepairstart + 1]);
				player_list[index]->addCard(temp[twopairstart]);
				player_list[index]->addCard(temp[twopairstart + 1]);
				player_list[index]->addCard(temp[2]);
			}
		}
		else
		{
			player_list[index]->addCard(temp[onepairstart]);
			player_list[index]->addCard(temp[onepairstart + 1]);
			player_list[index]->addCard(temp[twopairstart]);
			player_list[index]->addCard(temp[twopairstart + 1]);
			player_list[index]->addCard(temp[0]);
		}
	}
	return iftwopairs;
}

bool texas::onepair(int index)
{
	bool ifonepair = false;
	int onestart = 0;
	for (int i = 0; i < 6; i++)
	{
		if (temp[i].retNum() == temp[i + 1].retNum())
		{
			ifonepair = true;
			onestart = i;
			break;
		}
	}
	if (ifonepair)
	{
		player_list[index]->settlecards();
		if (onestart >= 3)
		{
			player_list[index]->addCard(temp[onestart]);
			player_list[index]->addCard(temp[onestart + 1]);
			player_list[index]->addCard(temp[0]);
			player_list[index]->addCard(temp[1]);
			player_list[index]->addCard(temp[2]);
		}
		else if (onestart == 0)
		{
			for (int i = 0; i < 5;i++)
				player_list[index]->addCard(temp[i]);
		}
		else
		{
			if (onestart == 1)
			{
				player_list[index]->addCard(temp[onestart]);
				player_list[index]->addCard(temp[onestart + 1]);
				player_list[index]->addCard(temp[0]);
				player_list[index]->addCard(temp[3]);
				player_list[index]->addCard(temp[4]);
			}
			if (onestart == 2)
			{
				player_list[index]->addCard(temp[onestart]);
				player_list[index]->addCard(temp[onestart + 1]);
				player_list[index]->addCard(temp[0]);
				player_list[index]->addCard(temp[1]);
				player_list[index]->addCard(temp[4]);
			}
		}
	}
	return ifonepair;
}

void texas::highcard(int index)
{
	player_list[index]->settlecards();
	for (int i = 0; i < 5;i++)
		player_list[index]->addCard(temp[i]);
}

void texas::playerCardType(int index)
{
	temp.push_back(player_list[index]->retHandCard(0));
	temp.push_back(player_list[index]->retHandCard(1));
	sort(temp);
	int i;
	unsigned long type1 = 0;
	unsigned long type2 = 0;
	if (line(index))
	{
		if (flower(index))
		{
			type1 = 9 * _Pow_int<unsigned long>(10, 6);
			for (i = 0; i < 2; i++)
			{
				type1 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (2 - i) * 3 - 2);
				type1 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (2 - i) * 3 - 3);

			}
			for (i = 2; i < 5; i++)
			{
				type2 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (5 - i) * 3 - 2);
				type2 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (5 - i) * 3 - 3);
			}
		}
		else
		{
			type1 = 5 * _Pow_int<unsigned long>(10, 6);
			for (i = 0; i < 2; i++)
			{
				type1 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (2 - i) * 3 - 2);
				type1 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (2 - i) * 3 - 3);

			}
			for (i = 2; i < 5; i++)
			{
				type2 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (5 - i) * 3 - 2);
				type2 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (5 - i) * 3 - 3);
			}
		}
	}
	else if (four(index))
	{
		type1 = 8 * _Pow_int<unsigned long>(10, 6);
		for (i = 0; i < 2; i++)
		{
			type1 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (2 - i) * 3 - 2);
			type1 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (2 - i) * 3 - 3);

		}
		for (i = 2; i < 5; i++)
		{
			type2 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (5 - i) * 3 - 2);
			type2 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (5 - i) * 3 - 3);
		}
	}
	else if (fullhouse(index))
	{
		type1 = 7 * _Pow_int<unsigned long>(10, 6);
		for (i = 0; i < 2; i++)
		{
			type1 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (2 - i) * 3 - 2);
			type1 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (2 - i) * 3 - 3);

		}
		for (i = 2; i < 5; i++)
		{
			type2 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (5 - i) * 3 - 2);
			type2 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (5 - i) * 3 - 3);
		}
	}
	else if (flower(index))
	{
		type1 = 6 * _Pow_int<unsigned long>(10, 6);
		for (i = 0; i < 2; i++)
		{
			type1 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (2 - i) * 3 - 2);
			type1 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (2 - i) * 3 - 3);

		}
		for (i = 2; i < 5; i++)
		{
			type2 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (5 - i) * 3 - 2);
			type2 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (5 - i) * 3 - 3);
		}
	}
	else if (three(index))
	{
		type1 = 4 * _Pow_int<unsigned long>(10, 6);
		for (i = 0; i < 2; i++)
		{
			type1 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (2 - i) * 3 - 2);
			type1 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (2 - i) * 3 - 3);

		}
		for (i = 2; i < 5; i++)
		{
			type2 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (5 - i) * 3 - 2);
			type2 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (5 - i) * 3 - 3);
		}
	}
	else if (twopairs(index))
	{
		type1 = 3 * _Pow_int<unsigned long>(10, 6);
		for (i = 0; i < 2; i++)
		{
			type1 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (2 - i) * 3 - 2);
			type1 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (2 - i) * 3 - 3);

		}
		for (i = 2; i < 5; i++)
		{
			type2 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (5 - i) * 3 - 2);
			type2 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (5 - i) * 3 - 3);
		}
	}
	else if (onepair(index))
	{
		type1 = 2 * _Pow_int<unsigned long>(10, 6);
		for (i = 0; i < 2; i++)
		{
			type1 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (2 - i) * 3 - 2);
			type1 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (2 - i) * 3 - 3);

		}
		for (i = 2; i < 5; i++)
		{
			type2 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (5 - i) * 3 - 2);
			type2 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (5 - i) * 3 - 3);
		}
	}
	else{
		highcard(index);
		type1 = 1 * _Pow_int<unsigned long>(10, 6);
		for (i = 0; i < 2; i++)
		{
			type1 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (2 - i) * 3 - 2);
			type1 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (2 - i) * 3 - 3);

		}
		for (i = 2; i < 5; i++)
		{
			type2 += player_list[index]->retHandCard(i).retNum() * _Pow_int<unsigned long>(10, (5 - i) * 3 - 2);
			type2 += turn(player_list[index]->retHandCard(i).retColor()) * _Pow_int<unsigned long>(10, (5 - i) * 3 - 3);
		}
	}
	temp.clear();
	player_list[index]->setcardsum1(type1);
	player_list[index]->setcardsum2(type2);
}

void texas::showType(unsigned long type)
{
	unsigned int cases = type / _Pow_int<unsigned long>(10, 6);
	switch (cases)
	{
	case 9:
		cout << "Straight Flush: ";
		break;
	case 8:
		cout << "Four of a Kind: ";
		break;
	case 7:
		cout << "FullHouse: ";
		break;
	case 6:
		cout << "Flush: ";
		break;
	case 5:
		cout << "Straight: ";
		break;
	case 4:
		cout << "Three of a Kind: ";
		break;
	case 3:
		cout << "Two Pairs: ";
		break;
	case 2:
		cout << "One Pair: ";
		break;
	case 1:
		cout << "High card: "; 
		break;
	default:
		break;
	}
}

void texas::judge()
{
	for (int i = 0; i < player_list.size(); i++)
	{
		if (!player_list[i]->ifdiscard())
			playerCardType(i);
	}
	for (int i = 0; i < player_list.size(); i++)
	{
		if (!player_list[i]->ifdiscard())
		{
			cout << "#" << i + 1 << ": " << player_list[i]->retname() << " show cards: \n";
			showType(player_list[i]->retcardsum1());
			player_list[i]->showHandCards();
		}
	}
	m_winner_index = 0;
	for (int i = 0; i < player_list.size(); i++)
	{
		if (!player_list[i]->ifdiscard())
		{
			if (player_list[m_winner_index]->retcardsum1() < player_list[i]->retcardsum1())
				m_winner_index = i;
			else if (player_list[m_winner_index]->retcardsum1() == player_list[i]->retcardsum1())
			{
				if (player_list[m_winner_index]->retcardsum2() < player_list[i]->retcardsum2())
					m_winner_index = i;
			}
		}
	}
	cout << "#" << m_winner_index + 1 << ": " << player_list.at(m_winner_index)->retname() << " win the game.\n";
	player_list[m_winner_index]->showHandCards();
	cout << "Get chips: " << pool << endl;
	player_list[m_winner_index]->getChips(pool);
}



