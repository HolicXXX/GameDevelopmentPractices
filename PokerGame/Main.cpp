#include <ctime>
#include "texas.h"

int main()
{
	time_t t;
	time(&t);
	srand(t);
	cout << "Please input your Name: ";
	string name;
	getline(cin, name);
	cout << "Plaese input your Chips Num(1000 ~ 1500): ";
	int money;
	cin >> money;
	player p1(name, money);
	cout << "Inut the Number of Computer Player: ";
	int num;
	cin >> num;
	texas game(string("Texas Hold'em Poker"), &p1, num);
	while (true)
	{
		game.setBegin();
		game.sendCards();
		game.round();
		game.judge();
		game.settlement();
		system("pause");
		system("cls");
	}

	return 0;
}