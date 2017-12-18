#include "basics.h"

void basics::setPosition(basicNODE * pos)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ pos->x, pos->y });
}

void basics::printVector(vector<basicNODE*> * v)
{
	for (int i = 0; i < v->size(); i++)
	{
		setPosition((*v)[i]);
		switch ((*v)[i]->type)
		{
		case SNAKE:
			if (i == 0)
				cout << '@';
			else
				cout << '*';
			break;
		case MAPEdge:
			cout << '#';
			break;
		case FOOD:
			cout << '$';
			break;
		default:
			break;
		}
	}
}

void basics::clearPosition(basicNODE * pos)
{
	setPosition(pos);
	cout << ' ';
}
