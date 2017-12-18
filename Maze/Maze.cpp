#include "Maze.h"
#include <iostream>
using namespace std;

maze::maze()
{
	for (int i = 0; i < 10; i++)
	{
		map[i] = new char[10];
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			map[i][j] = '#';
		}
		//map[i][10] = '\0';
	}
	m_step = 0;
	setRoad();
}

maze::~maze()
{
	for (int i = 0; i < 10; i++)
	{
		delete map[i];
	}
}

void maze::setRoad()
{
	pos = start = { 0, 0 };
	path.push(pos);
	end = { 0, 9 };
	for (int i = 0; i < 4; i++)
	{
		map[0][i] = ' ';
	}
	for (int i = 0; i < 4; i++)
	{
		map[i][3] = ' ';
	}
	for (int i = 3; i < 6; i++)
	{
		map[3][i] = ' ';
	}
	for (int i = 3; i < 10; i++)
	{
		map[i][5] = ' ';
	}
	for (int i = 5; i < 8; i++)
	{
		map[6][i] = ' ';
	}
	for (int i = 0; i < 6; i++)
	{
		map[9][i] = ' ';
	}
}

bool maze::ifpass(coord & pos)
{
	for (int i = 0; i < footprint.Size(); i++)
	{
		if (pos.x == footprint[i]->x && pos.y == footprint[i]->y)
			return false;
	}
	return true;
}

void maze::turnback()
{
	path.pop(pos);
	footprint.push(pos);
	pos = *path[path.Size() - 1];
}

void maze::UP()
{
	footprint.push(pos);
	pos.y--;
	path.push(pos);
}

void maze::DOWN()
{
	footprint.push(pos);
	pos.y++;
	path.push(pos);
}

void maze::LEFT()
{
	footprint.push(pos);
	pos.x--;
	path.push(pos);
}

void maze::RIGHT()
{
	footprint.push(pos);
	pos.x++;
	path.push(pos);
}

void maze::move()//R-D-L-U
{
	if (pos.x == 0)
	{
		if (pos.y == 0)
		{
			if (map[pos.y][pos.x + 1] == ' ' && ifpass(coord{ pos.x + 1, pos.y }))//R
			{
			
				RIGHT();
				return;
				
			}
			else if (map[pos.y + 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y + 1 }))//D
			{
				DOWN();
				return;
			}
			else
			{
				turnback();
				return;
			}
		}
		if (pos.y == 9)
		{
			if (map[pos.y][pos.x + 1] == ' ' && ifpass(coord{ pos.x + 1, pos.y }))//R
			{
				RIGHT();
				return;
			}
			else if (map[pos.y - 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y - 1 }))//U
			{
				UP();
				return;
			}
			else
			{
				turnback();
				return;
			}
		}
		else
		{
			if (map[pos.y][pos.x + 1] == ' ' && ifpass(coord{ pos.x + 1, pos.y }))//R
			{
				RIGHT();
				return;
			}
			else if (map[pos.y + 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y + 1 }))//D
			{
				DOWN();
				return;
			}
			else if (map[pos.y - 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y - 1 }))//U
			{
				UP();
				return;
			}
			
			else
			{
				turnback();
				return;
			}
		}
	}
	else if (pos.x == 9)
	{
		if (pos.y == 0)
		{	
			if (map[pos.y + 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y + 1 }))//D
			{
				DOWN();
				return;
			}
			else if (map[pos.y][pos.x - 1] == ' ' && ifpass(coord{ pos.x - 1, pos.y }))//L
			{
				LEFT();
				return;
			}
			else
			{
				turnback();
				return;
			}
		}
		else if (pos.y == 9)
		{
			if (map[pos.y][pos.x - 1] == ' ' && ifpass(coord{ pos.x - 1, pos.y }))//L
			{
				LEFT();
				return;
			}
			else if (map[pos.y - 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y - 1 }))//U
			{
				UP();
				return;
			}
			else
			{
				turnback();
				return;
			}
		}
		else
		{
			if (map[pos.y + 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y + 1 }))//D
			{
				DOWN();
				return;
			}
			else if (map[pos.y][pos.x - 1] == ' ' && ifpass(coord{ pos.x - 1, pos.y }))//L
			{
				LEFT();
				return;
			}
			else if (map[pos.y - 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y - 1 }))//U
			{
				UP();
				return;
			}
			else
			{
				turnback();
				return;
			}
		}
	}
	else
	{
		if (pos.y == 0)
		{
			if (map[pos.y][pos.x + 1] == ' ' && ifpass(coord{ pos.x + 1, pos.y }))//R
			{
				RIGHT();
				return;
			}
			else if (map[pos.y + 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y + 1 }))//D
			{
				DOWN();
				return;
			}
			else if (map[pos.y][pos.x - 1] == ' ' && ifpass(coord{ pos.x - 1, pos.y }))//L
			{
				LEFT();
				return;
			}
			else
			{
				turnback();
				return;
			}
		}
		else if (pos.y == 9)
		{
			if (map[pos.y + 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y + 1 }))//D
			{
				DOWN();
				return;
			}
			else if (map[pos.y][pos.x - 1] == ' ' && ifpass(coord{ pos.x - 1, pos.y }))//L
			{
				LEFT();
				return;
			}
			else if (map[pos.y - 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y - 1 }))//U
			{
				UP();
				return;
			}
			else
			{
				turnback();
				return;
			}
		}
		else
		{
			if (map[pos.y][pos.x + 1] == ' ' && ifpass(coord{ pos.x + 1, pos.y }))//R
			{
				RIGHT();
				return;
			}
			else if (map[pos.y + 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y + 1 }))//D
			{
				DOWN();
				return;
			}
			else if (map[pos.y][pos.x - 1] == ' ' && ifpass(coord{ pos.x - 1, pos.y }))//L
			{
				LEFT();
				return;
			}
			else if (map[pos.y - 1][pos.x] == ' ' && ifpass(coord{ pos.x, pos.y - 1 }))//U
			{
				UP();
				return;
			}
			else
			{
				turnback();
				return;
			}
		}
	}
}

void maze::showMaze()
{
	map[pos.y][pos.x] = '$';
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << map[i][j];
		cout << endl;
	}
	map[pos.y][pos.x] = ' ';
}


