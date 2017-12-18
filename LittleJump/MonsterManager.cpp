#include "MonsterManager.h"

bool MonsterManager::init()
{
	craeteMonster();
	scheduleUpdate();
	return true;
}

void MonsterManager::craeteMonster()
{
	for (int i = 0; i < MAX_MONSTER_NUM; i++)
	{
		auto m = Monster::create();
		m->bindSprite(Sprite::create("CloseSelected.png"));
		m->reset();

		this->addChild(m);
		m_monsters.pushBack(m);
	}
}

void MonsterManager::bindPlayer(Player* player)
{
	m_player = player;
}

void MonsterManager::update(float dt)
{
	for (auto m : m_monsters)
	{
		if (m->isAlive())
		{
			m->setPositionX(m->getPositionX() - 2);
			if (m->getPositionX() < 0)
			{
				m->hide();
			}
			else if (m->isHitPlayer(m_player))
			{
				m_player->hit();
				m->hide();
			}
		}
		else
		{
			m->show();
		}
	}
}
