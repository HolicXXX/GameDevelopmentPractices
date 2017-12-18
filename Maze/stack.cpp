#include "stack.h"
#include <iostream>
using namespace std;

stack::stack()
{
	Top = Botton = nullptr;
	m_count = 0;
}

stack::~stack()
{
	for (int i = 0; i < m_count; i++)
	{

	}
}

void stack::push(const coord & data)
{
	NODE * temp = new NODE{ data, nullptr };
	if (m_count == 0)
	{
		Top = Botton = temp;
		m_count++;
	}
	else
	{
		Top->next = temp;
		Top = temp;
		m_count++;
	}
}

bool stack::pop(coord & target)
{
	if (m_count == 0)
		return false;
	target = Top->Data;
	NODE * temp = Botton;
	while (true)
	{
		if (temp == Top)
		{
			Top = Botton = nullptr;
			delete temp;
			m_count--;
			break;
		}
		else 
		{
			if (temp->next == Top)
				break;
			temp = temp->next;
		}
	}
	Top = temp;
	delete Top->next;
	m_count--;
	return true;
}

coord * stack::operator[](int index)
{
	if (index >= m_count || index < 0)
	{
		return new coord{ 0, 0 };
	}
	else
	{
		NODE * temp = Botton;
		if (index == m_count - 1)
		{
			temp = Top;
			return &(temp->Data);
		}
		for (int i = 0; i < index ; i++)
		{
			temp = temp->next;
		}
		return &(temp->Data);
	}
}

void stack::showStack()
{
	if (m_count == 0)
		return;
	for (int i = 0; i < m_count; i++)
	{
		cout << "#" << i + 1 << ": (" << this->operator[](i)->x << "," << this->operator[](i)->y << ")\n";
	}
}







