#include "block.h"
#include <iostream>

block::block(char count)
	:m_state(Block)
{
	m_count = count;
}

void block::showBlock()
{
	switch (m_state)
	{
	case Block:
		std::cout << '#';
		break;
	case Blank:
		if (m_count == 0)
			std::cout << ' ';
		if (m_count > 0)
			std::cout << int(m_count);
		break;
	case Mark:
		std::cout << '$';
		break;
	case Boom:
		std::cout << '@';
		break;
	}
}

bool block::leftClick()
{
	if (m_count >= 0)
	{
		m_state = Blank;
		return true;
	}
	else
	{
		m_state = Boom;
		return false;
	}
}

void block::rightClick()
{
	if (m_state == Block)
	{
		m_state = Mark;
	}
	else if (m_state == Mark)
	{
		m_state = Block;
	}
}