#include "Block.h"

Vector<Block*>* Block::blocks = new Vector<Block*>();

Vector<Block*>* Block::getBlocks()
{
	return Block::blocks;
}

Block* Block::createWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor)
{
	auto block = new Block();
	if (block && block->initWithArgs(color, size, label, fontSize, textColor))
	{
		block->autorelease();
		blocks->pushBack(block);
		return block;
	}

	CC_SAFE_DELETE(block);
	return nullptr;
}

bool Block::initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor)
{
	Sprite::init();
	setContentSize(size);
	setAnchorPoint(Vec2::ZERO);
	setTextureRect(Rect(0, 0, size.width, size.height));
	setColor(color);

	auto l = Label::create();
	l->setString(label);
	l->setSystemFontSize(fontSize);
	l->setTextColor(textColor);
	addChild(l);
	l->setPosition(size.width / 2, size.height / 2);


	return true;
}

void Block::removeBlock()
{
	removeFromParent();
	blocks->eraseObject(this);
}

int Block::getLineIndex()
{
	return this->lineIndex;
}

void Block::setLineIndex(int value)
{
	this->lineIndex = value;
}

void Block::moveDown()
{
	--lineIndex;

	auto size = Director::getInstance()->getVisibleSize();

	runAction(Sequence::create(MoveTo::create(0.1f, Vec2(getPosition().x, lineIndex * size.height / 4)), CallFunc::create([&](){
		if (lineIndex < 0)
			this->removeBlock();
	}), nullptr));

}
