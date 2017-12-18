#pragma once 

struct coord
{
	int x;
	int y;
};
class stack
{
private:
	struct NODE
	{
		coord Data;
		NODE * next;
	};
	NODE * Botton;
	NODE * Top;
	int m_count;
public:
	stack();
	~stack();
	int Size() { return m_count; }
	void push(const coord &);
	bool pop(coord &);
	coord * operator[](int);
	void showStack();
};