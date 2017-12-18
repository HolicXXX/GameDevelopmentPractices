#pragma once
#include "stack.h"
class maze
{
private:
	char * map[10];
	stack footprint;
	stack path;
	int m_step;
	coord pos;
	coord start;
	coord end;
	void setRoad();
	bool ifpass(coord &);
	void turnback();
	void UP();
	void DOWN();
	void LEFT();
	void RIGHT();
public:
	maze();
	~maze();
	void move();
	void showMaze();
	bool ifdest() { return pos.x == end.x && pos.y == end.y; }
	void showRoad() { path.showStack(); }
};