#include "Maze.h"
#include <Windows.h>
#include <iostream>
using namespace std;
int main()
{
	/*stack s;
	s.push(coord{ 0, 0 });
	s.push(coord{ 0, 1 });
	s.push(coord{ 1, 0 });
	s.push(coord{ 1, 1 });
	cout << s.Size() << endl;
	for (int i = 0; i < s.Size(); i++)
	{
		cout << (*s[i]).x << "," << (*s[i]).y << endl;
	}*/

	maze maze1;
	while (!maze1.ifdest())
	{
		maze1.showMaze();
		maze1.move();
		//Sleep(1000);
		system("cls");
	}
	maze1.showRoad();
	system("pause");
	return 0;
}

