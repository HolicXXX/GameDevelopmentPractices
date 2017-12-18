#pragma once

#include <iostream>
#include <vector>
#include "skill.h"
#include "item.h"
using std::vector;

struct Property_Data
{
	string m_name;
	int m_level;
	int m_HP_Max;
	int m_HP;
	int m_MP_Max;
	int m_MP;
	int m_Speed;
	int m_escape_perc;
	double m_AtkP;
	double m_DefP;
	double m_DdgP;
	double m_CriP;
};

class charactor
{
protected:
	Property_Data m_basic_data;
	//property_extra_list
	vector<Extra_Data> atk_extra_list;
	vector<Extra_Data> def_extra_list;
	vector<Extra_Data> dgd_extra_list;
	vector<Extra_Data> cri_extra_list;
	//Dot_list or Hot_list
	vector<Extra_Data> dot_list;
	vector<Extra_Data> hot_list;
	double sumExtra(vector<Extra_Data> list);
	virtual void initData() = 0;
	void remove(vector<Extra_Data> &);
public:
	charactor(string & name, int level = 1);
	bool isAlive() { return m_basic_data.m_HP > 0; }
	void setSpd(int spd) { m_basic_data.m_Speed = spd; }
	int retSpd() { return m_basic_data.m_Speed; }
	int retLevel() { return m_basic_data.m_level; }
	const string & retName() { return m_basic_data.m_name; }
	virtual void beattack(double demage);
	virtual void getHealed(double healp);
	virtual double attack();
	virtual void useDemageSkill(charactor & target, int i = 0) {};
	virtual void useHealSkill(int index = 0) {};
	virtual void showData();
	virtual int movement() = 0;
	virtual bool tryEscape();
	void addExtra(Extra_Data extra,int type);
	double sumDot();
	double sumHot();
	void removeExtra();
	virtual double sumProp(int type) { return 0; }
	virtual int retExp() { return 0; }
	virtual ~charactor() {};
};