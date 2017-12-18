#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Block : public Sprite
{
private:
	static Vector<Block*>* blocks;
	int lineIndex;
public:
	static Vector<Block*>* getBlocks();
	static Block* createWithArgs(Color3B color,Size size,std::string label = "",float fontSize = 20,Color4B textColor = Color4B::BLACK);
	virtual bool initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor);
	void removeBlock();
	int getLineIndex();
	void setLineIndex(int value);

	void moveDown();

};
