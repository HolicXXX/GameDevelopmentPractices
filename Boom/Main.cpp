#include <ctime>
#include "game.h"
using namespace std;

int main()
{
	srand(std::time(0));
	gamezone g;
	g.gameOn();
	system("pause");
	return 0;
}


