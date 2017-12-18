#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Card : public Sprite
{
public:
	Card();
	virtual ~Card();
	static Card* create(int numbers, int wight, int height, float posX, float posY);
	virtual bool init();

	void setNumber(int num);
	int getNumber();

private:
	int number;
	void cardInit(int numbers, int wight, int height, float posX, float posY);

	LabelTTF* cardNumberLabel;

	LayerColor* backLayer;

};
