#include "item.h"
#include <iostream>
using std::cout;
using std::endl;

item::item(int type, int level)
{
	m_type = type;
	m_itemID = m_type;
	initItem(level);
}

void item::initItem(int level)
{
	switch (m_type)
	{
	case 1:
		name = "HP Drug";
		m_val = 200 * level;
		m_money = 10 * level;
		break;
	case 2:
		name = "MP Drug";
		m_val = 50 * level;
		m_money = 10 * level;
		break;
	case 3:
		name = "Attack Equipment";
		m_val = 20 * level;
		m_money = 20 * level;
		break;
	case 4:
		name = "Defense Equipment";
		m_val = 10 * level;
		m_money = 10 * level;
		break;
	case 5:
		name = "Dodge Equipmen";
		m_val = 20;
		m_money = 500;
		break;
	case 6:
		name = "Critical Equipment";
		m_val = 30;
		m_money = 500;
		break;
	default:
		break;
	}
}

void item::showItem()
{
	cout << "Item: " << name << endl;
	switch (m_type)
	{
	case 1:
		cout << "Add HP: " << m_val << endl;
		break;
	case 2:
		cout << "Add MP: " << m_val << endl;
		break;
	case 3:
		cout << "Increase Attack Points: " << m_val << endl;
		break;
	case 4:
		cout << "Increase Defense Points: " << m_val << endl;
		break;
	case 5:
		cout << "Increase Dodge Points: " << m_val << endl;
		break;
	case 6:
		cout << "Increase Critical Points: " << m_val << endl;
		break;
	default:
		cout << "No such item.\n";
		break;
	}
	cout << "Selling Price: " << m_money << endl;
}

void item::resetItem(int level)
{
	initItem(level);
}
