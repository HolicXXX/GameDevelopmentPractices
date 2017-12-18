#include "boss.h"
#include <ctime>
using std::cout;
using std::endl;

boss::boss(string & name, int level)
	:charactor(name,level)
{
	ret_Equipment_ID = rand() % 4 + 1;
	ret_Exp = 60 * level;
	ret_Money = 10 * level;
	initData();
	demage_skill_list.push_back(skill(1, 1, level));
	demage_skill_list.push_back(skill(1, 2, level));
	heal_skill_list.push_back(skill(2, 1, level));
	heal_skill_list.push_back(skill(2, 2, level));
}

void boss::initData()
{
	m_basic_data.m_HP = m_basic_data.m_HP_Max = 100 + 100 * m_basic_data.m_level;
	m_basic_data.m_MP = m_basic_data.m_MP_Max = 40 + 30 * m_basic_data.m_level;
	m_basic_data.m_AtkP = 30 + 20 * m_basic_data.m_level;
	m_basic_data.m_DefP = 20 + 20 * m_basic_data.m_level;
	m_basic_data.m_DdgP = 10;
	m_basic_data.m_CriP = 10;
}

void boss::useDemageSkill(charactor & target,int index)
{
	int i = rand() % 2 + 1;
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

void boss::useHealSkill(int i)
{
	int index = rand() % 2 + 1;
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

int boss::movement()
{
	int ran;
	if (m_basic_data.m_HP > 0.6 * m_basic_data.m_HP_Max)
	{
		ran = rand() % 2;
		if (ran == 0)
			return 1;
		else
		{
			if (m_basic_data.m_MP > 0.3 * m_basic_data.m_MP_Max)
				return 2;
			else
				return 1;
		}
	}
	else if (m_basic_data.m_HP < 0.1 * m_basic_data.m_HP_Max)
	{
		return 0;
	}

	else
	{
		ran = rand() % 2;
		if (ran == 0)
			return 1;
		else
		{
			if (m_basic_data.m_MP > 0.3 * m_basic_data.m_MP_Max)
				return 3;
			else
				return 1;
		}
	}
}
