#include "map.h"
#include <Windows.h>

map::map()
	:m_snake(new basicNODE{ rand() % 5 + 5, rand() % 3 + 3,SNAKE })
{
	for (int i = 0; i < WIGHT; i++)
	{
		m_map.push_back(new basicNODE{ i, 0, MAPEdge });
		m_map.push_back(new basicNODE{ i, 23, MAPEdge });
	}
	for (int i = 1; i < HEIGHT - 1; i++)
	{
		m_map.push_back(new basicNODE{ 0, i, MAPEdge });
		m_map.push_back(new basicNODE{ 78, i, MAPEdge });
	}
	for (int i = 8; i < 15; i++)
		m_map.push_back(new basicNODE{ 12, i, MAPEdge });
	for (int i = 40; i < 60; i++)
		m_map.push_back(new basicNODE{ i, 18, MAPEdge });
}

map::~map()
{
	for (auto i : m_map)
		delete i;
	m_map.clear();
	for (auto i : m_food)
		delete i;
	m_food.clear();
}

void map::setFood()
{
	int x;
	int y;
	bool isEdge = true, isBody = true;
	while (isEdge || isBody)
	{
		x = rand() % 77 + 1;
		y = rand() % 22 + 1;
		isEdge = isBody = false;
		for (int i = 0; i < m_snake.retBodyVect()->size(); i++)
		{
			if (m_snake.retBodyVect()->at(i)->x == x && m_snake.retBodyVect()->at(i)->y)
			{
				isBody = true;
				break;
			}
			else
			{
				for (int j = 0; j < m_map.size(); j++)
				{
					if (m_map[j]->x == x && m_map[j]->y == y)
					{
						isEdge == true;
						break;
					}
				}
				if (isEdge)
					break;
			}
		}
	}
	m_food.push_back(new basicNODE{ x, y, FOOD });
}

void map::clrFood()
{
	int i;
	for (i = 0; i < m_food.size(); i++)
		if (m_food[i]->x == m_snake.retHeadNode()->x && m_food[i]->y == m_snake.retHeadNode()->y)
			break;
	delete m_food[i];
	m_food.erase(m_food.begin() + i);
}

void map::showMap()
{
	basics::printVector(&m_map);
}

void map::showFood()
{
	basics::printVector(&m_food);
}

bool map::isCrash()
{
	for (auto i : m_map)
	{
		if (i->x == m_snake.retHeadNode()->x && i->y == m_snake.retHeadNode()->y)
			return true;
	}
	for (int i = 1; i < m_snake.retBodyVect()->size(); i++)
	{
		if (m_snake.retBodyVect()->at(i)->x == m_snake.retHeadNode()->x && m_snake.retBodyVect()->at(i)->y == m_snake.retHeadNode()->y)
			return true;
	}
	return false;
}

bool map::isEat()
{
	for (auto i : m_food)
	{
		if (i->x == m_snake.retHeadNode()->x && i->y == m_snake.retHeadNode()->y)
			return true;
	}
	return false;
}

void map::gameOn()
{
	setFood();
	showMap();
	int t;
	Direction dir = m_snake.retDir();
	do
	{
		showFood();
		m_snake.showSnake();
		if (isEat())
		{
			clrFood();
			m_snake.grow();
			setFood();
		}
		t = GetTickCount();
		while (GetTickCount() - t <= 1000)//speed
		{
			if (GetAsyncKeyState(VK_UP) != 0)
				dir = UP;
			if (GetAsyncKeyState(VK_DOWN) != 0)
				dir = DOWN;
			if (GetAsyncKeyState(VK_LEFT) != 0)
				dir = LEFT;
			if (GetAsyncKeyState(VK_RIGHT) != 0)
				dir = RIGHT;
		}
		m_snake.headTrun(dir);
		m_snake.move();
	} while (!isCrash());
	showFood();
	m_snake.showSnake();
}

void map::gameOver()
{
	basicNODE* temp = new basicNODE{ 32, 11, MAPEdge };
	basics::setPosition(temp);
	delete temp;
	cout << "***Game Over!***\n";
	temp = new basicNODE{ 32, 12, MAPEdge };
	basics::setPosition(temp);
	delete temp;
	cout << " Continue? Y/N: ";
}



