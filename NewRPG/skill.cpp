#include "skill.h"
#include <iostream>
using std::cout;
using std::endl;

skill::skill(int type, int insORdel, int level,int bufftype)
{
	m_type = type;
	m_ins_OR_del = insORdel;
	m_skillID = m_type * 10 + insORdel;
	MP_cost = 10 + level * 10;
	if (type == 1)
	{
		if (insORdel == 1)
		{
			name = "Instance Demage Skill";
		}
		else if (insORdel == 2)
		{
			name = "Dot Skill";
		}
	}
	else if (type == 2)
	{
		if (insORdel == 1)
		{
			name = "Instance Heal Skill";
		}
		else if (insORdel == 2)
		{
			name = "Hot Skill";
		}
	}
	else//3
	{
		m_skillID = m_type * 10 + bufftype;
	}
	resetSkillVal(level);
}

void skill::showSkill()
{
	cout << "Skill type: " << (m_type == 1 ? " Demage " : (m_type == 2 ? " Heal " : " Buff ")) << endl;
	cout << "Skill name: " << name << endl;
	cout << "Skill ID: " << m_skillID << endl;
	switch (m_ins_OR_del)
	{
	case 1:
		cout << "Skill value: " << m_ret_val << endl;
		break;
	case 2:
		cout << "Skill value: " << m_ret_struct.m_Extra_Value << endl;
		cout << "Skill stay rounds: " << m_ret_struct.m_Extra_Rounds << endl;
	default:
		break;
	}
}

void skill::resetSkillVal(int level)
{
	MP_cost = 10 + level * 10;
	if (m_type != 3)
	{
		if (m_ins_OR_del == 1)
		{
			m_ret_struct = { 0, 0 };
			m_ret_val = 100 * level;
		}
		else if (m_ins_OR_del == 2)
		{
			m_ret_struct = { double(10 * level), 5 };
			m_ret_val = 0;
		}
	}
	else
	{
		m_ret_struct = { double(5 * level), 5 };
		m_ret_val = 0;
	}
	
}

