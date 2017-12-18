#pragma once
#include"FOOD.h"
#include<vector>
#include<iostream>
using namespace std;

enum TOWARD { UP, LEFT, DOWN, RIGHT };

struct BODY
{
	BODY(COLORREF clr) :color(clr) { x = 0;y = 0; }
	COLORREF color;
	double x;
	double y;
};

class SNAKE
{
public:
	SNAKE(RECT window);
	~SNAKE();
	void showSnake(HDC& dstDC);
	bool isCrush();
	double xhead();
	double yhead();
	void move(TOWARD t);
	void eatFood(COLORREF color);
private:
	vector<BODY*>bodies;
	RECT wndRect;
	double width;
	double speed;
};

