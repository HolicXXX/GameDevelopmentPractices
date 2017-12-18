#pragma once
#include "basics.h"
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class snake
{
private:
	vector<basicNODE*> body;
	basicNODE* head;
	Direction head_dire;
public:
	snake(basicNODE*);
	~snake();
	vector<basicNODE*>* retBodyVect() { return &body; }
	basicNODE* retHeadNode() { return head; }
	Direction retDir() { return head_dire; }
	void headTrun(Direction);
	void showSnake();
	void grow();
	void move();
};