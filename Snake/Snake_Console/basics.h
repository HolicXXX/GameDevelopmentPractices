#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
using std::vector;
using std::cout;

enum NODEtype
{
	SNAKE,
	MAPEdge,
	FOOD
};

struct basicNODE
{
	int x;
	int y;
	NODEtype type;
};

class basics
{
public:
	static void setPosition(basicNODE * pos);
	static void printVector(vector<basicNODE*> * v);
	static void clearPosition(basicNODE * pos);
};




