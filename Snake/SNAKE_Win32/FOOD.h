#pragma once
class FOOD
{
public:
	FOOD(RECT wndSize);
	FOOD(COLORREF color);
	~FOOD();
	double xFood();
	double yFood();
	COLORREF color();
	void showFood(HDC& dstDC);
private:
	double m_x;
	double m_y;
	COLORREF m_color;
	RECT wndRect;
};

