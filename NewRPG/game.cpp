#include "game.h"
#include <ctime>
using namespace std;


game::game(player * player)
	: m_player(player)
{
	settlement_Exp = 0;
	player_escape = false;
	if_boss = false;
}

game::~game()
{
	m_enemy.clear();
}

void game::town()
{
	srand(time(0));
	int ran;
	int choice;
	while (true)
	{
		cout << "Place: Town\n\n";
		((player*)m_player)->recover();
		m_player->showData();
		cout << "\nChoose your movement:\n";
		cout << "#1: Defeat some minions\n";
		cout << "#2: Chanllenge a Boss\n";
		cout << "#3: Check Items\n";
		cout << "#4: Quit game\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			char c[2];
			ran = rand() % 3 + 3;
			m_enemy.clear();
			for (int i = 0; i < ran; i++)
			{
				sprintf(c, "%d", i + 1);
				m_enemy.push_back(new minion(string("minion ") + c, m_player->retLevel()));
				m_enemy_movement.push_back(0);
			}
			battlezone();
			battleover();
		}
		break;
		case 2:
			m_enemy.clear();
			m_enemy.push_back(new boss(string("Boss"), m_player->retLevel()));
			m_enemy_movement.push_back(0);
			if_boss = true;
			battlezone();
			battleover();
			break;
		case 3:
			showBag();
			break;
		case 4:
			cout << "Game over.\nBye.\n";
			return;
		default:
			cout << "Wrong input , please try again." << endl;
			break;
		}
	}
}

void game::showBag()
{
	int choice;
	system("cls");
	while (true)
	{
		cout << "Place: Bag\n";
		((player*)m_player)->showEquipment();
		((player*)m_player)->showBag();
		cout << "Choose your movement: \n";
		cout << "#1: Put on equipment.\n";
		cout << "#2: Take off equipment.\n";
		cout << "#3: Sell items.\n";
		cout << "#4: Leave the bag.\n";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
		{
			((player*)m_player)->showBag();
			cout << "Input a index: ";
			cin >> choice;
			((player*)m_player)->putOn(choice);
		}
		break;
		case 2:
		{
			((player*)m_player)->showEquipment();
			cout << "Input a index: ";
			cin >> choice;
			((player*)m_player)->takeOff(choice);
		}
		break;
		case 3:
		{
			((player*)m_player)->showBag();
			cout << "Input a index: ";
			cin >> choice;
			((player*)m_player)->sellItem(choice);
		}
		break;
		case 4:
			return;
		default:
			cout << "Wrong input,try again.\n";
			break;
		}
	}
	
}

void game::battlezone()
{
	/*srand(time(0));
	m_player->setSpd(rand() % 10);
	for (int i = 0; i < m_enemy.size(); i++)
		m_enemy[i]->setSpd(rand() % 10);*/
	while (true)
	{
		system("pause");
		system("cls");
		if (m_enemy.size() == 0 || !m_player->isAlive())
			return;
		rounds();
		if (player_escape)
			return;
		settlement();
	}
}

void game::showRoundsOptions()
{
	cout << "Please choose your movement: " << endl;
	cout << "#1: Attack\n";
	cout << "#2: UseSkill\n";
	cout << "#3: Defense\n";
	cout << "#4: UseItem\n";
	cout << "#5: Escape\n";
}

void game::showEnemy()
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		cout << "#" << i + 1 << ": " << endl;
		m_enemy[i]->showData();
	}
}

int game::chooseTarget()
{
	int ret;
	cout << "Choose your target: \n";
	for (int i = 0; i < m_enemy.size(); i++)
	{
		cout << "#" << i + 1 << endl;
	}
	cin >> ret;
	return ret;
}

void game::enemyAct()
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		switch (m_enemy_movement[i])
		{
		case 1:
			m_player->beattack(m_enemy[i]->attack());
			if (!m_player->isAlive())
				return;
			break;
		case 2:
			m_enemy[i]->useDemageSkill(*m_player);
			break;
		case 3:
			m_enemy[i]->useHealSkill();
			break;
		case 0:
			m_enemy[i]->tryEscape();
			break;
		default:
			break;
		}
	}
}

void game::rounds()
{
	int choice;
	int target = 0;
	showEnemy();
	showRoundsOptions();
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy_movement[i] = m_enemy[i]->movement();
	}
	cin >> choice;
	switch (choice)
	{
	case 1:
		target = chooseTarget() - 1;
		m_enemy[target]->beattack(m_player->attack());
		if (!m_enemy[target]->isAlive())
		{
			settlement_Exp += m_enemy[target]->retExp();
			m_enemy.erase(m_enemy.begin() + target);
		}
		enemyAct();
		break;
	case 2:
	{
		int skill_choose;
		cout << "Choose your skill: " << endl;
		((player*)m_player)->showSkill();
		cin >> skill_choose;
		switch (skill_choose)
		{
		case 1:
			target = chooseTarget() - 1;
			m_player->useDemageSkill(*m_enemy[target], 1);
			if (!m_enemy[target]->isAlive())
			{
				settlement_Exp += m_enemy[target]->retExp();
				m_enemy.erase(m_enemy.begin() + target);
			}
			enemyAct();
			break;
		case 2:
			target = chooseTarget() - 1;
			m_player->useDemageSkill(*m_enemy[target], 2);
			if (!m_enemy[target]->isAlive())
			{
				settlement_Exp += m_enemy[target]->retExp();
				m_enemy.erase(m_enemy.begin() + target);
			}
			enemyAct();
			break;
		case 3:
			m_player->useHealSkill(1);
			enemyAct();
			break;
		case 4:
			m_player->useHealSkill(2);
			enemyAct();
			break;
		case 5:
			((player*)m_player)->useBuffSkill(1);
			enemyAct();
			break;
		case 6:
			((player*)m_player)->useBuffSkill(2);
			enemyAct();
			break;
		case 7:
			((player*)m_player)->useBuffSkill(3);
			enemyAct();
			break;
		case 8:
			((player*)m_player)->useBuffSkill(4);
			enemyAct();
			break;
		default:
			break;
		}
	}
	break;
	case 3:
		((player*)m_player)->setDef();
		enemyAct();
		((player*)m_player)->setDef();
		break;
	case 4:
		cout << "No items now.\n";
		break;
	case 5:
		if (m_player->tryEscape())
		{
			player_escape = true;
			break;
		}
		else
		{
			enemyAct();
			break;
		}
	}
}

void game::settlement()
{
	m_player->beattack(m_player->sumDot());
	m_player->getHealed(m_player->sumHot());
	m_player->removeExtra();
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->beattack(m_enemy[i]->sumDot());
	}
	for (int i = 0; i < m_enemy.size(); i++)
	{
		if (!m_enemy[i]->isAlive())
		{
			settlement_Exp += m_enemy[i]->retExp();
			m_enemy.erase(m_enemy.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->getHealed(m_enemy[i]->sumHot());
	}
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->removeExtra();
	}
}

void game::battleover()
{

	if (m_player->isAlive() && m_enemy.size() <= 0)
	{
		cout << m_player->retName() << " win the battle.\n";
		((player*)m_player)->getExp(settlement_Exp);
		if (if_boss)
		{
			if (rand() % 2 == 0)
			{
				int ran = rand() & 4 + 3;
				((player*)m_player)->getItem(item(ran,m_player->retLevel()));
			}
			else
			{
				((player*)m_player)->getMoney(10 * m_player->retLevel());
			}
		}
		settlement_Exp = 0;
		m_player->showData();
	}
	else
	{
		cout << m_player->retName() << " lose the battle.\n";
		settlement_Exp = 0;
		((player*)m_player)->getExp(settlement_Exp);
		m_player->showData();
	}
}

