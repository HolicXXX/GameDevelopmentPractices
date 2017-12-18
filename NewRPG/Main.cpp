
#include "game.h"
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));
	player p1(string("p1"),10);
	game game1(&p1);
	game1.town();

	system("pause");
	return 0;
}