#include "Card.h"

Card::Card() : number(0)
{

}

Card::~Card()
{
	this->removeAllChildren();
}


Card* Card::create(int numbers, int wight, int height, float posX, float posY)
{
	auto card = new Card();
	if (card&&card->init())
	{
		card->autorelease();
		card->cardInit(numbers, wight, height, posX, posY);
		return card;
	}

	CC_SAFE_DELETE(card);
	return nullptr;

}

bool Card::init()
{
	if (!Sprite::init())
		return false;
	return true;
}

int Card::getNumber()
{
	return number;
}

void Card::setNumber(int num)
{
	number = num;

	if (number >= 0)
	{
		cardNumberLabel->setFontSize(100);
		this->cardNumberLabel->setColor(Color3B::BLACK);
	}
	if (number >= 16)
	{
		cardNumberLabel->setFontSize(90);
		this->cardNumberLabel->setColor(Color3B::MAGENTA);
	}
	if (number >= 128)
	{
		cardNumberLabel->setFontSize(60);
		this->cardNumberLabel->setColor(Color3B::RED);
	}
	if (number >= 1024)
	{
		cardNumberLabel->setFontSize(40);
		this->cardNumberLabel->setColor(Color3B::BLUE);
	}

	if (number == 0)
	{
		backLayer->setColor(Color3B(200,190,180));
	}
	if (number == 2)
	{
		backLayer->setColor(Color3B(240, 230, 220));
	}
	if (number == 4)
	{
		backLayer->setColor(Color3B(240, 220, 200));
	}
	if (number == 8)
	{
		backLayer->setColor(Color3B(240, 180, 120));
	}
	if (number == 16)
	{
		backLayer->setColor(Color3B(240, 140, 90));
	}
	if (number == 32)
	{
		backLayer->setColor(Color3B(240, 120, 90));
	}
	if (number == 64)
	{
		backLayer->setColor(Color3B(240, 90, 60));
	}
	if (number == 128)
	{
		backLayer->setColor(Color3B(240, 90, 60));
	}
	if (number == 256)
	{
		backLayer->setColor(Color3B(240, 200, 70));
	}
	if (number == 512)
	{
		backLayer->setColor(Color3B(0, 130, 0));
	}
	if (number == 1024)
	{
		backLayer->setColor(Color3B(0, 130, 0));
	}
	if (number >= 2048)
	{
		backLayer->setColor(Color3B(0, 130, 0));
	}

	if (number > 0)
	{
		this->cardNumberLabel->setString(__String::createWithFormat("%d", number)->getCString());
	}
	else
	{
		this->cardNumberLabel->setString("");
	}
}

void Card::cardInit(int numbers, int wight, int height, float posX, float posY)
{
	number = numbers;

	backLayer = LayerColor::create(Color4B(200, 190, 180, 255), wight - 15, height - 15);
	/*this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	backLayer->ignoreAnchorPointForPosition(false);*/
	backLayer->setPosition(posX, posY);
	
	if (number > 0)
	{
		cardNumberLabel = LabelTTF::create(__String::createWithFormat("%d", number)->getCString(), "", 100);
		cardNumberLabel->setPosition(backLayer->getContentSize().width / 2, backLayer->getContentSize().height / 2);
		backLayer->addChild(cardNumberLabel);
	}
	else
	{
		cardNumberLabel = LabelTTF::create("", "", 100);
		cardNumberLabel->setPosition(backLayer->getContentSize().width / 2, backLayer->getContentSize().height / 2);
		backLayer->addChild(cardNumberLabel);
	}
	this->addChild(backLayer);
}



