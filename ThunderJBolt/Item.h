#ifndef _ITEM_H_
#define _ITEM_H_

#include "cocos2d.h"

class Item :public cocos2d::Sprite
{
public:
	static Item* create(const std::string& src,int type);
	virtual bool init(const std::string& src,int type);

	int getType(){ return m_type; }
	void setType(int t){ m_type = t; }
private:
	int m_type;
};


#endif