#include "player.h"
#include <ctime>
using std::cout;
using std::cin;
using std::endl;

player::player(string & name, int level)
	:charactor(name, level), bag_SIZE(20), equipment_SIZE(4)
{
	m_Exp_Max = 100 * level;
	demage_skill_list.push_back(skill(1, 1, level));
	demage_skill_list.push_back(skill(1, 2, level));
	heal_skill_list.push_back(skill(2, 1, level));
	heal_skill_list.push_back(skill(2, 2, level));
	buff_skill_list.push_back(skill(3, 2, level, 1));
	buff_skill_list.push_back(skill(3, 2, level, 2));
	buff_skill_list.push_back(skill(3, 2, level, 3));
	buff_skill_list.push_back(skill(3, 2, level, 4));
	initData();
	m_money = 1;
	m_basic_data.m_Speed = 0;
	isDef = false;
	m_basic_data.m_escape_perc = 80;
}

void player::initData()
{
	m_basic_data.m_HP = m_basic_data.m_HP_Max = 100 + 50 * m_basic_data.m_level;
	m_basic_data.m_MP = m_basic_data.m_MP_Max = 40 + 30 * m_basic_data.m_level;
	m_basic_data.m_AtkP = 30 + 15 * m_basic_data.m_level;
	m_basic_data.m_DefP = 20 + 10 * m_basic_data.m_level;
	m_basic_data.m_DdgP = 30;
	m_basic_data.m_CriP = 10;
	demage_skill_list[0].resetSkillVal(m_basic_data.m_level);
	demage_skill_list[1].resetSkillVal(m_basic_data.m_level);
	heal_skill_list[0].resetSkillVal(m_basic_data.m_level);
	heal_skill_list[1].resetSkillVal(m_basic_data.m_level);
	buff_skill_list[0].resetSkillVal(m_basic_data.m_level);
	buff_skill_list[1].resetSkillVal(m_basic_data.m_level);
	buff_skill_list[2].resetSkillVal(m_basic_data.m_level);
	buff_skill_list[3].resetSkillVal(m_basic_data.m_level);
}

void player::showData()
{
	charactor::showData();
	cout << "Money: " << m_money << endl;
	cout << "Exp: " << m_Exp << "/" << m_Exp_Max << endl;
}

int player::movement()
{
	int ret;
	cin >> ret;
	return ret;
}

void player::beattack(double demage)
{
	if (demage == 0)
		return;
	double random_per = rand() % 100;
	if (random_per < m_basic_data.m_DdgP + sumExtra(dgd_extra_list) + sumProp(3))
	{
		demage = 0;
		cout << m_basic_data.m_name << " Dodged.\n";
	}
	else
	{
		demage *= (isDef ? 0.5 : 1);
		demage -= m_basic_data.m_DefP + sumExtra(def_extra_list) + sumProp(2);
		if (demage <= 1)
			demage = 1;
	}
	m_basic_data.m_HP -= demage;
	cout << m_basic_data.m_name << " get " << demage << " points demage.\n";
}

void player::showSkill()
{
	cout << "Skill #1: \n";
	demage_skill_list[0].showSkill();
	cout << "Skill #2: \n";
	demage_skill_list[1].showSkill();
	cout << "Skill #3: \n";
	heal_skill_list[0].showSkill();
	cout << "Skill #4: \n";
	heal_skill_list[1].showSkill();
	for (int i = 0; i < 4; i++)
	{
		cout << "Skill #" << i + 5 << ": \n";
		buff_skill_list[i].showSkill();
	}
}

void player::useDemageSkill(charactor & target, int i)
{
	if (i == 1)
	{
		if (m_basic_data.m_MP > demage_skill_list[i - 1].retMP())
		{
			m_basic_data.m_MP -= demage_skill_list[i - 1].retMP();
			cout << m_basic_data.m_name << " uses instance demage skill  makes " << demage_skill_list[i - 1].retVal() << " points demage.\n";
			target.beattack(demage_skill_list[i - 1].retVal());
		}
		else
			cout << "Not enough MP.\n";
	}
	else
	{
		if (m_basic_data.m_MP > demage_skill_list[i - 1].retMP())
		{
			m_basic_data.m_MP -= demage_skill_list[i - 1].retMP();
			cout << m_basic_data.m_name << " uses Dot skill  makes " << demage_skill_list[i - 1].retStruct().m_Extra_Value << " for per rounds in " << demage_skill_list[i - 1].retStruct().m_Extra_Rounds << " rounds.\n";
			target.addExtra(demage_skill_list[i - 1].retStruct(), 5);
		}
		else
			cout << "Not enough MP.\n";
	}
}

void player::useHealSkill(int index)
{
	if (index == 1)
	{
		if (m_basic_data.m_MP > heal_skill_list[index - 1].retMP())
		{
			m_basic_data.m_MP -= heal_skill_list[index - 1].retMP();
			cout << m_basic_data.m_name << " uses instance heal skill makes " << heal_skill_list[index - 1].retVal() << " points heal.\n";
			getHealed(heal_skill_list[index - 1].retVal());
		}
		else
			cout << "Not enough MP.\n";
	}
	else
	{
		if (m_basic_data.m_MP > heal_skill_list[index - 1].retMP())
		{
			m_basic_data.m_MP -= heal_skill_list[index - 1].retMP();
			cout << m_basic_data.m_name << " uses Hot skill makes " << heal_skill_list[index - 2].retStruct().m_Extra_Value << " points heal for " << heal_skill_list[index - 2].retStruct().m_Extra_Rounds << " rounds.\n";
			addExtra(heal_skill_list[index - 2].retStruct(), 6);
		}
		else
			cout << "Not enough MP.\n";
	}
}

void player::useBuffSkill(int index)
{
	if (m_basic_data.m_MP > buff_skill_list[index - 1].retMP())
	{
		if (index == 1)
		{
			addExtra(buff_skill_list[index - 1].retStruct(), 1);
		}
		if (index == 2)
		{
			addExtra(buff_skill_list[index - 1].retStruct(), 2);
		}
		if (index == 3)
		{
			addExtra(buff_skill_list[index - 1].retStruct(), 3);
		}
		if (index == 4)
		{
			addExtra(buff_skill_list[index - 1].retStruct(), 4);
		}
	}
	else
		cout << "Not enough MP.\n";
}

bool player::tryEscape()
{
	double random_per = rand() % 100;
	if (random_per < m_basic_data.m_escape_perc)
	{
		cout << m_basic_data.m_name << " escaped. Battle is over.\n";
		return true;
	}
	else
	{
		cout << m_basic_data.m_name << " escape failed.\n";
		return false;
	}
}

void player::getExp(int exp)
{
	m_Exp += exp;
	if (m_Exp >= m_Exp_Max)
	{
		m_Exp -= m_Exp_Max;
		levelUp();
	}
	cout << m_basic_data.m_name << " get " << exp << " points Exp.\n";
}

void player::levelUp()
{
	m_basic_data.m_level++;
	cout << m_basic_data.m_name << " level up to " << m_basic_data.m_level << endl;
	initData();
}

void player::getItem(item item)
{
	if (bag_list.size() < bag_SIZE)
	{
		cout << m_basic_data.m_name << " get item : \n";
		item.showItem();
		bag_list.push_back(item);
	}
	else
	{
		cout << m_basic_data.m_name << " get item : \n";
		item.showItem();
		cout << "Bag has no left space.\n\n";
		cout << "Drop item.\n\n";
	}
}

void player::getMoney(int money)
{
	cout << m_basic_data.m_name << " get money: " << money << endl;
	m_money += money;
}

void player::sellItem(int index)
{
	if (index <= bag_list.size())
	{
		cout << "Sell item:";
		bag_list[index - 1].showItem();
		getMoney(bag_list[index - 1].retPrice());
		bag_list.erase(bag_list.begin() + index - 1);
	}
	else
		cout << "Wrong input.\n";
}

void player::putOn(int index)
{
	if (index <= bag_list.size() && bag_list[index - 1].retType() > 2)
	{
		if (equipment_list.size() < equipment_SIZE)
		{
			cout << "Put on equipment:\n";
			bag_list[index - 1].showItem();
			equipment_list.push_back(bag_list[index - 1]);
			bag_list.erase(bag_list.begin() + index - 1);
		}
		else
			cout << "You have no left space in Equipment.\n";
	}
	else
		cout << "Wrong input.\n";
	
}

void player::takeOff(int index)
{
	if (index <= equipment_list.size())
	{
		if (bag_list.size() < bag_SIZE)
		{
			cout << "Take off equipment:";
			equipment_list[index - 1].showItem();
			bag_list.push_back(equipment_list[index - 1]);
			equipment_list.erase(equipment_list.begin() + index - 1);
		}
		else
			cout << "You have no left space in Bag.\n";
	}
	else
		cout << "Wrong input.\n";
}

double player::sumProp(int type)
{
	double ret = 0;
	switch (type)
	{
	case 1:
		for (int i = 0; i < equipment_list.size(); i++)
		{
			if (equipment_list[i].retType() == 3)
				ret += equipment_list[i].retValue();
		}
		break;
	case 2:
		for (int i = 0; i < equipment_list.size(); i++)
		{
			if (equipment_list[i].retType() == 4)
				ret += equipment_list[i].retValue();
		}
		break;
	case 3:
		for (int i = 0; i < equipment_list.size(); i++)
		{
			if (equipment_list[i].retType() == 5)
				ret += equipment_list[i].retValue();
		}
		break;
	case 4:
		for (int i = 0; i < equipment_list.size(); i++)
		{
			if (equipment_list[i].retType() == 6)
				ret += equipment_list[i].retValue();
		}
		break;
	default:
		break;
	}
	return ret;
}

void player::showBag()
{
	if (bag_list.size() == 0)
	{
		cout << "No item in your bag.\n";
		return;
	}
	for (int i = 0; i < bag_list.size(); i++)
	{
		cout << "#1: " << endl;
		bag_list[i].showItem();
	}
}

void player::showEquipment()
{
	if (equipment_list.size() == 0)
	{
		cout << "No equipment.\n";
		return;
	}
	for (int i = 0; i < equipment_list.size(); i++)
	{
		cout << "#1: " << endl;
		equipment_list[i].showItem();
	}
}




