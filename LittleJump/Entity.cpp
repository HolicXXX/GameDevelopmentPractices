#include "Entity.h"

Entity::Entity()
	:m_sprite(nullptr)
{
}

Entity::~Entity()
{
}

Sprite* Entity::getSprite()
{
	return this->m_sprite;
}

void Entity::bindSprite(Sprite* sp)
{
	this->m_sprite = sp;
	this->addChild(m_sprite);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	auto size = m_sprite->getContentSize();
	this->setContentSize(size);
	m_sprite->setPosition(Vec2::ZERO);
	

}

