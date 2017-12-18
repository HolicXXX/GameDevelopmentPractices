#pragma once

#include "charactor.h"

class player : public charactor
{
protected:
	int m_Exp_Max;
	int m_Exp;
	vector<skill> demage_skill_list;
	vector<skill> heal_skill_list;
	vector<skill> buff_skill_list;

	int m_money;
	vector<item> equipment_list;
	vector<item> bag_list;
	const int bag_SIZE;
	const int equipment_SIZE;

	bool isDef;
	virtual void initData();
public:
	player(string & name, int level = 1);
	//might need copy
	virtual ~player() {};
	virtual void showData();
	virtual int movement();
	virtual void beattack(double demage);
	void showSkill();
	virtual void useDemageSkill(charactor & target,int i);
	virtual void useHealSkill(int index);
	void useBuffSkill(int index);
	virtual bool tryEscape();
	void recover() { initData(); }
	void getExp(int exp);
	void levelUp();
	void setDef() { isDef = !isDef; }
	
	void getItem(item);
	void sellItem(int index);
	void putOn(int index);
	void takeOff(int index);
	double sumProp(int type);
	void showBag();
	void showEquipment();
	void getMoney(int money);
};