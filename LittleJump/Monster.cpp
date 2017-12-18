#include "Monster.h"

Monster::Monster()
	:m_isAlive(false)
{
}

Monster::~Monster()
{
}

bool Monster::init()
{
	return true;
}

bool Monster::isHitPlayer(Player* player)
{
	auto rect = player->getBoundingBox();
	auto pos = this->getPosition();

	return rect.containsPoint(pos);
}

void Monster::show()
{
	if (getSprite() != nullptr)
	{
		setVisible(true);
		m_isAlive = true;
	}
}

void Monster::hide()
{
	if (getSprite() != nullptr)
	{
		setVisible(false);
		reset();
		m_isAlive = false;
	}
}

void Monster::reset()
{
	if (getSprite() != nullptr)
	{
		setPosition(Vec2(480 + CCRANDOM_0_1() * 1000, 128 - CCRANDOM_0_1() * 64));
	}
}

bool Monster::isAlive()
{
	return m_isAlive;
}




