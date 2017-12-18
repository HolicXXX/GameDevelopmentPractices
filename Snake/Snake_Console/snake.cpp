#include "snake.h"

snake::snake(basicNODE* initpos)
{
	head = initpos;
	body.push_back(initpos);
	head_dire = RIGHT;
	body.push_back(new basicNODE{ initpos->x - 1, initpos->y, SNAKE });
	body.push_back(new basicNODE{ initpos->x - 2, initpos->y, SNAKE });
}

snake::~snake()
{
	for (auto i : body)
	{
		delete i;
	}
	body.clear();
}

void snake::headTrun(Direction dire)
{
	switch (head_dire)
	{
	case UP:
		if (dire == DOWN)
			return;
		break;
	case DOWN:
		if (dire == UP)
			return;
		break;
	case LEFT:
		if (dire == RIGHT)
			return;
		break;
	case RIGHT:
		if (dire == LEFT)
			return;
		break;
	default:
		break;
	}
	head_dire = dire;
}

void snake::showSnake()
{
	basics::printVector(&body);
}

void snake::grow()
{
	if (body[body.size() - 1]->x == body[body.size() - 2]->y)
	{
		if (body[body.size() - 1]->y > body[body.size() - 2]->y)
			body.push_back(new basicNODE{ body[body.size() - 1]->x, body[body.size() - 1]->y + 1, SNAKE });
		else
			body.push_back(new basicNODE{ body[body.size() - 1]->x, body[body.size() - 1]->y - 1, SNAKE });
	}
	else
	{
		if (body[body.size() - 1]->x > body[body.size() - 2]->x)
			body.push_back(new basicNODE{ body[body.size() - 1]->x + 1, body[body.size() - 1]->y, SNAKE });
		else
			body.push_back(new basicNODE{ body[body.size() - 1]->x - 1, body[body.size() - 1]->y, SNAKE });
	}
}

void snake::move()
{
	basics::clearPosition(body.at(body.size() - 1));
	for (int i = body.size() - 1; i > 0; i--)
	{
		body[i]->x = body[i - 1]->x;
		body[i]->y = body[i - 1]->y;
	}
	switch (head_dire)
	{
	case UP:
		head->y--;
		break;
	case DOWN:
		head->y++;
		break;
	case LEFT:
		head->x--;
		break;
	case RIGHT:
		head->x++;
		break;
	default:
		break;
	}
}
