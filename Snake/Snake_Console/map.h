#include "snake.h"

class map
{
private:
	enum{ WIGHT = 79, HEIGHT = 24 };
	vector<basicNODE*> m_map;
	vector<basicNODE*> m_food;
	snake m_snake;
	void setFood();
	void clrFood();
	void showMap();
	void showFood();
	bool isCrash();
	bool isEat();
public:
	map();
	~map();
	void gameOn();
	void gameOver();
};