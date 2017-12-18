#include "stdafx.h"
#include "SNAKE.h"

SNAKE::SNAKE(RECT window)
{
	bodies.push_back(new BODY(RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
	bodies.push_back(new BODY(RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
	bodies.push_back(new BODY(RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)));
	bodies[2]->x = 15;
	bodies[2]->y = 120;
	bodies[1]->x = 15;
	bodies[1]->y = 130;
	bodies[0]->x = 15;
	bodies[0]->y = 140;
	wndRect = window;
	width = 0;
	speed = 8;
}

SNAKE::~SNAKE()
{
	for (int i = 0;i < bodies.size() - 1;++i)
	{
		delete bodies[i];
	}
	bodies.clear();
}

void SNAKE::showSnake(HDC& dstDC)
{
	HDC snakeDC = CreateCompatibleDC(dstDC);
	HBITMAP hSnakeBmp = CreateCompatibleBitmap(dstDC, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top);
	SelectObject(snakeDC, hSnakeBmp);
	BITMAP snakeBmp;
	GetObject(hSnakeBmp, sizeof(BITMAP), &snakeBmp);
	for (int i = bodies.size() - 1;i >= 0;--i)
	{
		HBRUSH b_body = CreateSolidBrush(bodies[i]->color);
		SelectObject(snakeDC, b_body);
		Ellipse(snakeDC, bodies[i]->x - 7 - width, bodies[i]->y - 7 - width, bodies[i]->x + 7 + width, bodies[i]->y + 7 + width);
		DeleteObject(b_body);
	}
	TransparentBlt(dstDC, 0, 0, wndRect.right, wndRect.bottom, snakeDC, 0, 0, snakeBmp.bmWidth, snakeBmp.bmHeight, RGB(0, 0, 0));

	DeleteObject(hSnakeBmp);
	DeleteObject(snakeDC);
}

double SNAKE::xhead()
{
	return bodies[0]->x;
}

double SNAKE::yhead()
{
	return bodies[0]->y;
}

bool SNAKE::isCrush()
{
	bool ret = 0;
	if ((bodies[0]->x) < wndRect.left + 7 || (bodies[0]->x) > wndRect.right - 7 || (bodies[0]->y) < wndRect.top + 7 || (bodies[0]->y) > wndRect.bottom - 7)
	{
		ret = 1;
	}
	return ret;
}

void SNAKE::move(TOWARD t)
{
	//ÓÀÔ¶¾àÀë¼ä¸ô10  speedÖ»¿ØÖÆÉßÍ·
	for (int i = bodies.size() - 1;i > 0;--i)
	{
		bodies[i]->x = bodies[i - 1]->x;
		bodies[i]->y = bodies[i - 1]->y;
	}
	switch (t)
	{
	case LEFT:
		{
			bodies[0]->x -= speed;
		}
		break;
	case RIGHT:
		{
			bodies[0]->x += speed;
		}
		break;
	case UP:
		{
			bodies[0]->y -= speed;
		}
		break;
	case DOWN:
		{
			bodies[0]->y += speed;
		}
		break;
	}
}

void SNAKE::eatFood(COLORREF color)
{
	bodies.push_back(new BODY(color));
	speed += 0.1;
}