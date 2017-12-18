#include "charactor.h"

class minion : public charactor
{
protected:
	int m_ret_Exp;
	virtual void initData();
public:
	minion(string & name, int level);
	//might need copy
	virtual ~minion() {};
	virtual int movement();
	virtual int retExp() { return m_ret_Exp; }
};