#pragma once

#include <string>
using std::string;

struct Extra_Data
{
	double m_Extra_Value;
	int m_Extra_Rounds;
};

class skill
{
private:
	string name;
	int MP_cost;
	int m_type;//demage or heal
	int m_ins_OR_del;
	int m_skillID;//instance demage or dot//instance heal or hot
	Extra_Data m_ret_struct;
	double m_ret_val;
public:
	skill(int type,int insORdel,int level,int bufftype = 0);
	//might need copy
	~skill() {};
	int retMP() { return MP_cost; }
	void showSkill();
	void resetSkillVal(int level);
	Extra_Data retStruct() { return m_ret_struct; }
	double retVal() { return m_ret_val; }
	int retID() { return m_skillID; }
};