#include "map.h"
#include <ctime>

int main()
{
	srand(time(0));
	char c;
	do
	{
		map map1;
		system("cls");
		map1.gameOn();
		map1.gameOver();
		std::cin >> c;
		std::cin.get();
	} while (c == 'Y' || c == 'y');
	return 0;
}