#pragma once
#include "block.h"
#include <iostream>
#include <Windows.h>

class gamezone
{
private:
	block * m_zone[10];
	void setALLCount(COORD);
	int boomnum(COORD);
	void showBoom();
	bool checkWin();
public:
	gamezone();
	~gamezone();
	void showZone();
	void gameOn();
	void gameOver();
};