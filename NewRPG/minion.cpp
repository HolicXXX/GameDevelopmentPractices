#include "minion.h"
#include <ctime>
using std::cout;
using std::endl;

minion::minion(string & name, int level)
	:charactor(name,level)
{
	m_ret_Exp = 40 * level;
	initData();
	m_basic_data.m_Speed = 0;
	m_basic_data.m_escape_perc = 20;
}

void minion::initData()
{
	m_basic_data.m_HP = m_basic_data.m_HP_Max = 25 + 25 * m_basic_data.m_level;
	m_basic_data.m_MP = m_basic_data.m_MP_Max = 0;
	m_basic_data.m_AtkP = 10 + 10 * m_basic_data.m_level;
	m_basic_data.m_DefP = 10 + 5 * m_basic_data.m_level;
	m_basic_data.m_DdgP = 5;
	m_basic_data.m_CriP = 5;
}

int minion::movement()
{
	if (m_basic_data.m_HP > 0.3 * m_basic_data.m_HP_Max)
		return 1;
	else
		return 0;
}
