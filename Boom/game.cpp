#include "game.h"
using namespace std;

gamezone::gamezone()
{
	for (int i = 0; i < 10; i++)
	{
		m_zone[i] = new block[10];
	}
	int boomcount = 10;
	int ran;
	while (boomcount > 0)
	{
		ran = rand() % 100;
		if (m_zone[ran / 10][ran % 10].retCount() >= 0)
			m_zone[ran / 10][ran % 10].setCount(-1);
		else
			continue;
		boomcount--;
	}
}

gamezone::~gamezone()
{
	for (int i = 0; i < 10; i++)
	{
		delete [] m_zone[i];
	}
	delete [] m_zone;
}

void gamezone::showZone()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_zone[i][j].showBlock();
		}
		cout << endl;
	}
}

bool gamezone::checkWin()
{
	int bnum = 0;
	int mnum = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_zone[i][j].retCount() < 0)
			{
				bnum++;
				if (m_zone[i][j].retState() == Mark)
					mnum++;
			}
		}
	}
	if (bnum == mnum)
		return true;
	else
		return false;
}

void gamezone::gameOn()
{
	HANDLE hOut, hIn;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD keyRec;
	DWORD res;
	COORD pos = { 0, 0 };
	while (true)
	{
		system("cls");
		SetConsoleCursorPosition(hOut, { 0, 0 });
		if (checkWin())
		{
			gameOver();
			return;
		}
		showZone();
		SetConsoleCursorPosition(hOut, pos);
		int now = GetTickCount();
		while (true)
		{
			if (GetTickCount() - now < 500)
				continue;
			ReadConsoleInput(hIn, &keyRec, 1, &res);
			if (keyRec.Event.KeyEvent.uChar.AsciiChar == 'W')
			{
				if (pos.Y != 0)
					pos.Y--;
				break;
			}
			if (keyRec.Event.KeyEvent.uChar.AsciiChar == 'A')
			{
				if (pos.X != 0)
					pos.X--;
				break;
			}
			if (keyRec.Event.KeyEvent.uChar.AsciiChar == 'S')
			{
				if (pos.Y != 9)
					pos.Y++;
				break;
			}
			if (keyRec.Event.KeyEvent.uChar.AsciiChar == 'D')
			{
				if (pos.X != 9)
					pos.X++;
				break;
			}
			if (keyRec.Event.KeyEvent.uChar.AsciiChar == 'Q')
			{
				if (m_zone[pos.Y][pos.X].leftClick())
				{
					setALLCount(pos);
					break;
				}
				else
				{
					showBoom();
					gameOver();
					return;
				}
			}
			if (keyRec.Event.KeyEvent.uChar.AsciiChar == 'E')
			{
				m_zone[pos.Y][pos.X].rightClick();
				break;
			}
		}
		
	}
}

int gamezone::boomnum(COORD pos)
{
	int ret = 0;
	if (pos.X == 0)
	{
		if (pos.Y == 0)
		{
			if (m_zone[pos.Y + 1][pos.X].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X + 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y][pos.X + 1].retCount() < 0)
				ret++;
		}
		else if (pos.Y == 9)
		{
			if (m_zone[pos.Y - 1][pos.X].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X + 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y][pos.X + 1].retCount() < 0)
				ret++;
		}
		else
		{
			if (m_zone[pos.Y - 1][pos.X].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X + 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y][pos.X + 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X + 1].retCount() < 0)
				ret++;
		}
	}
	else if (pos.X == 9)
	{
		if (pos.Y == 0)
		{
			if (m_zone[pos.Y][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X].retCount() < 0)
				ret++;
		}
		else if (pos.Y == 9)
		{
			if (m_zone[pos.Y][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X].retCount() < 0)
				ret++;
		}
		else
		{
			if (m_zone[pos.Y][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X].retCount() < 0)
				ret++;
		}
	}
	else
	{
		if (pos.Y == 0)
		{
			if (m_zone[pos.Y][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y][pos.X + 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X + 1].retCount() < 0)
				ret++;
		}
		else if (pos.Y == 9)
		{
			if (m_zone[pos.Y][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y][pos.X + 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X + 1].retCount() < 0)
				ret++;
		}
		else
		{
			if (m_zone[pos.Y][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X - 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X].retCount() < 0)
				ret++;
			if (m_zone[pos.Y + 1][pos.X + 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y][pos.X + 1].retCount() < 0)
				ret++;
			if (m_zone[pos.Y - 1][pos.X + 1].retCount() < 0)
				ret++;

		}
	}
	return ret;
}

void gamezone::showBoom()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_zone[i][j].retCount() < 0)
				m_zone[i][j].setBoom();
		}
		cout << endl;
	}
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, { 0, 10 });
	showZone();
}

void gamezone::setALLCount(COORD pos)
{
	COORD nowpos = pos;
	int num = 0;
	for (; nowpos.X < 10; nowpos.X++)
	{
		nowpos.Y = pos.Y;
		for (; nowpos.Y < 10; nowpos.Y++)
		{
			num = boomnum(nowpos);
			m_zone[nowpos.Y][nowpos.X].setBlank();
			if (num > 0)
			{
				m_zone[nowpos.Y][nowpos.X].setCount(num);
				break;
			}
		}
		nowpos.Y = pos.Y;
		for (; nowpos.Y >= 0; nowpos.Y--)
		{
			num = boomnum(nowpos);
			m_zone[nowpos.Y][nowpos.X].setBlank();
			if (num > 0)
			{
				m_zone[nowpos.Y][nowpos.X].setCount(num);
				break;
			}
		}
	}
	nowpos = pos;
	for (; nowpos.X >= 0; nowpos.X--)
	{
		nowpos.Y = pos.Y;
		for (; nowpos.Y < 10; nowpos.Y++)
		{
			num = boomnum(nowpos);
			m_zone[nowpos.Y][nowpos.X].setBlank();
			if (num > 0)
			{
				m_zone[nowpos.Y][nowpos.X].setCount(num);
				break;
			}
		}
		nowpos.Y = pos.Y;
		for (; nowpos.Y >= 0; nowpos.Y--)
		{
			num = boomnum(nowpos);
			m_zone[nowpos.Y][nowpos.X].setBlank();
			if (num > 0)
			{
				m_zone[nowpos.Y][nowpos.X].setCount(num);
				break;
			}
		}
	}
}

void gamezone::gameOver()
{
	if (checkWin())
		cout << "WIN" << endl;
	else
		cout << "LOSE" << endl;
	cout << "Game Over!" << endl;
}



