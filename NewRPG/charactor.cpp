#include "charactor.h"
#include <ctime>
using std::cout;
using std::endl;

charactor::charactor(string & name, int level)
{
	m_basic_data.m_name = name;
	m_basic_data.m_level = level;
}

void charactor::showData()
{
	cout << "Name: " << m_basic_data.m_name << endl;
	cout << "Level: " << m_basic_data.m_level << endl;
	cout << "HP: " << m_basic_data.m_HP << "/" << m_basic_data.m_HP_Max << endl;
	cout << "MP: " << m_basic_data.m_MP << "/" << m_basic_data.m_MP_Max << endl;
	cout << "AtkP: " << m_basic_data.m_AtkP + sumExtra(atk_extra_list) + sumProp(1) << endl;
	cout << "DefP: " << m_basic_data.m_DefP + sumExtra(def_extra_list) + sumProp(2) << endl;
	cout << "DdgP: " << m_basic_data.m_DdgP + sumExtra(dgd_extra_list) + sumProp(3) << endl;
	cout << "CriP: " << m_basic_data.m_CriP + sumExtra(cri_extra_list) + sumProp(4) << endl;
}

bool charactor::tryEscape()
{
	srand(time(0));
	double random_per = rand() % 100;
	if (random_per < m_basic_data.m_escape_perc)
	{
		m_basic_data.m_HP = 0;
		cout << m_basic_data.m_name << " escaped.\n";
		return true;
	}
	else
	{
		cout << m_basic_data.m_name << " escape failed.\n";
		return false;
	}
}

double charactor::sumExtra(vector<Extra_Data> list)
{
	double ret = 0;
	for (int i = 0; i < list.size(); i++)
	{
		ret += list[i].m_Extra_Value;
	}
	return ret;
}

void charactor::beattack(double demage)
{
	if (demage == 0)
		return;
	srand(time(0));
	double random_per = rand() % 100;
	if (random_per < m_basic_data.m_DdgP + sumExtra(dgd_extra_list))
	{
		demage = 0;
		cout << m_basic_data.m_name << " Dodged.\n";
	}
	else
	{
		demage -= m_basic_data.m_DefP + sumExtra(def_extra_list);
		if (demage <= 1)
			demage = 1;
	}
	m_basic_data.m_HP -= demage;
	cout << m_basic_data.m_name << " get " << demage << " points demage.\n";
}

void charactor::getHealed(double healp)
{
	if (healp == 0)
		return;
	m_basic_data.m_HP += healp;
	cout << m_basic_data.m_name << " get " << healp << " healed points.\n";
	if (m_basic_data.m_HP >= m_basic_data.m_HP_Max)
		m_basic_data.m_HP = m_basic_data.m_HP_Max;
}

double charactor::attack()
{
	int ran = rand() % 100;
	double demage = 0;
	if (ran < m_basic_data.m_CriP + sumExtra(cri_extra_list) + sumProp(4))
	{
		demage = 2 * (m_basic_data.m_AtkP + sumExtra(atk_extra_list) + sumProp(1));
		cout << m_basic_data.m_name << " Critical makes " << demage << " points demage.\n";
	}
	else
	{
		demage = m_basic_data.m_AtkP + sumExtra(atk_extra_list) + sumProp(1);
		cout << m_basic_data.m_name << " makes " << demage << " points demage.\n";
	}
	return demage;
}

void charactor::addExtra(Extra_Data extra, int type)
{
	switch (type)
	{
	case 1:
		atk_extra_list.push_back(extra);
		cout << m_basic_data.m_name << " Atk buff.\n";
		break;
	case 2:
		def_extra_list.push_back(extra);
		cout << m_basic_data.m_name << " Def buff.\n";
		break;
	case 3:
		dgd_extra_list.push_back(extra);
		cout << m_basic_data.m_name << " Dgd buff.\n";
		break;
	case 4:
		cri_extra_list.push_back(extra);
		cout << m_basic_data.m_name << " Cri buff.\n";
		break;
	case 5:
		dot_list.push_back(extra);
		cout << m_basic_data.m_name << " get Dot\n";
		break;
	case 6:
		hot_list.push_back(extra);
		cout << m_basic_data.m_name << " get Hot.\n";
		break;
	}
}

double charactor::sumDot()
{
	if (dot_list.size() != 0)
	{
		cout << "Dot: " << sumExtra(dot_list) << endl;
		return sumExtra(dot_list);
	}
	return 0;
}

double charactor::sumHot()
{
	if (hot_list.size() != 0)
	{
		cout << "Hot: " << sumExtra(hot_list) << endl;
		return sumExtra(hot_list);
	}
	return 0;
}

void charactor::remove(vector<Extra_Data> & list)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].m_Extra_Rounds <= 0)
		{
			list.erase(list.begin() + i);
			i--;
		}
		else
		{
			list[i].m_Extra_Rounds--;
		}
	}
}

void charactor::removeExtra()
{
	remove(dot_list);
	remove(hot_list);
	remove(atk_extra_list);
	remove(def_extra_list);
	remove(dgd_extra_list);
	remove(cri_extra_list);
}
