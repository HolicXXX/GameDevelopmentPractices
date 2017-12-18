#pragma once

#include <string>
using std::string;

class item
{
private:
	string name;
	int m_type;//6
	int m_itemID;
	int m_money;
	double m_val;
	void initItem(int);
public:
	item(int type, int level);
	//might need copy
	~item() {};
	void showItem();
	void resetItem(int);
	int retType() { return m_type; }
	int ret_itemID() { return m_itemID; }
	double retValue() { return m_val; }
	int retPrice() { return m_money; }
};
