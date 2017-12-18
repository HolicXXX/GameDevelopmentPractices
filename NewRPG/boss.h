#pragma once

#include "charactor.h"

class boss : public charactor
{
protected:
	int ret_Equipment_ID;
	int ret_Exp;
	int ret_Money;
	vector<skill> demage_skill_list;
	vector<skill> heal_skill_list;
	virtual void initData();
public:
	boss(string & name, int level);
	//might need copy
	virtual ~boss() {};
	virtual void useDemageSkill(charactor & target,int index = 0);
	virtual void useHealSkill(int index = 0);
	virtual int movement();
	int retEquipmentID() { return ret_Equipment_ID; }
	virtual int retExp() { return ret_Exp; }
	int retMoney() { return ret_Money; }
};