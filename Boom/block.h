#pragma once

enum state{Block,Blank,Mark,Boom};

class block
{
private:
	state m_state;
	char m_count;
public:
	block(char count = 0);
	void showBlock();
	bool leftClick();
	void rightClick();
	void setBoom() { m_state = Boom; }
	void setBlank() { m_state = Blank; }
	void setCount(char c) { m_count = c; }
	char retCount() { return m_count; }
	state retState() { return m_state; }
};