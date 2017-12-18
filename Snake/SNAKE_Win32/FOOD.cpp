#include "stdafx.h"
#include "FOOD.h"

FOOD::FOOD(RECT wndSize)
{
	m_color = RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	m_x = rand() % (wndSize.right - wndSize.left - 40) + wndSize.left + 20;
	m_y = rand() % (wndSize.bottom - wndSize.top - 40) + wndSize.top + 20;
	wndRect = wndSize;
}

FOOD::FOOD(COLORREF color)
{
	m_color = color;
}

FOOD::~FOOD()
{
}

double FOOD::xFood()
{
	return m_x;
}

double FOOD::yFood()
{
	return m_y;
}

COLORREF FOOD::color()
{
	return m_color;
}

void FOOD::showFood(HDC& dstDC)
{
	HDC foodDC = CreateCompatibleDC(dstDC);
	HBITMAP foodBmp = CreateCompatibleBitmap(dstDC, 10, 10);
	SelectObject(foodDC, foodBmp);
	HBRUSH b_food = CreateSolidBrush(m_color);
	SelectObject(foodDC, b_food);
	Ellipse(foodDC, 0, 0, 10, 10);
	DeleteObject(b_food);
	DeleteObject(foodBmp);

	TransparentBlt(dstDC, m_x - 5, m_y - 5, 10, 10, foodDC, 0, 0, 10, 10, RGB(0, 0, 0));

	DeleteObject(foodDC);
}