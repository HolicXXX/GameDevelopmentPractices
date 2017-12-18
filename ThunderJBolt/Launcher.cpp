#include "Launcher.h"
#include "BulletFactory.h"
#include "Manager.h"
USING_NS_CC;

Launcher* Launcher::create()
{
	auto l = new Launcher();
	if (l && l->init())
	{
		l->autorelease();
		return l;
	}
	CC_SAFE_DELETE(l);
	return nullptr;
}

bool Launcher::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_ltype = LauncherType::PLAYER_LAUNCHER;
	m_type = 0;
	m_level = 0;
	m_isshoot = false;
	m_count = 0;

	return true;
}

void Launcher::setLevel(int l)
{
	if (l > 3)
		return;
	else
		m_level = l;
}

void Launcher::update(float dt)
{
	switch (m_ltype)
	{
	case PLAYER_LAUNCHER:
	{
		if (m_count >= (4 - m_level) * 10)
		{
			produceBullet();
			m_count = 0;
		}
	}
		break;
	case ENEMY_LAUNCHER:
	{
		if (m_count >= (4 - m_level) * 30)
		{
			produceBullet();
			m_count = 0;
		}
	}
		break;
	case BOSS_LAUNCHER:
	{
		if (m_count >= (4 - m_level) * 10)
		{
			produceBullet();
			m_count = 0;
		}
	}
		break;
	default:
		break;
	}
	m_count++;
}

void Launcher::produceBullet()
{
	auto pos = this->convertToWorldSpace(Vec2::ZERO);
	auto bf = BulletFactory::getBulletFactory();
	switch (m_ltype)
	{
	case PLAYER_LAUNCHER:
	{
		switch (m_type)
		{
		case 1:
		{
			int offsetX = 23;
			switch (m_level)
			{
			case 1:
			{
				bf->produceBullet(m_type, pos, Vec2::ZERO, Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
			}
			break;
			case 2:
			{
				{
					bf->produceBullet(m_type, pos, Vec2(offsetX, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(-offsetX, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
			}
			break;
			case 3:
			{
				{
					bf->produceBullet(m_type, pos, Vec2(0, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(offsetX, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(-offsetX, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 2:
		{
			int offsetX = 24;
			switch (m_level)
			{
			case 1:
			{
				{
					bf->produceBullet(m_type, pos, Vec2(-offsetX, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(offsetX, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
			}
			break;
			case 2:
			{
				{
					bf->produceBullet(m_type, pos, Vec2(offsetX, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(offsetX * 2, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(-offsetX, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(-offsetX * 2, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
			}
			break;
			case 3:
			{
				{
					bf->produceBullet(m_type, pos, Vec2(offsetX, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(offsetX * 2, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(offsetX * 3, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(-offsetX, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(-offsetX * 2, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(-offsetX * 3, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 3:
		{
			int offsetX = 30;
			switch (m_level)
			{
			case 1:
			{
				{
					bf->produceBullet(m_type, pos, Vec2(0, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
			}
			break;
			case 2:
			{

				{
					bf->produceBullet(m_type, pos, Vec2(0, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(offsetX, 0), Vec2(0.5f, 0.866f), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(-offsetX, 0), Vec2(-0.5f, 0.866f), 500 + m_type * 100, 15 * m_type);
				}
			}
			break;
			case 3:
			{
				{
					bf->produceBullet(m_type, pos, Vec2(0, 0), Vec2(0, 1), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(offsetX, 0), Vec2(0.5f, 0.866f), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(-offsetX, 0), Vec2(-0.5f, 0.866f), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(offsetX, 0), Vec2(1.0f, 0), 500 + m_type * 100, 15 * m_type);
				}
				{
					bf->produceBullet(m_type, pos, Vec2(-offsetX, 0), Vec2(-1.0f, 0), 500 + m_type * 100, 15 * m_type);
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		default:
			break;
		}
	}
		break;
	case ENEMY_LAUNCHER:
	{
		auto hero = Manager::getManager()->getHero();
		auto heroPos = hero->convertToWorldSpace(Vec2::ZERO);
		auto dir = (heroPos - pos).getNormalized();
		bf->produceBullet(m_type, pos, Vec2(0, 0), dir, 200 * (m_type % 10), 10 * (m_type % 10));
	}
		break;
	case BOSS_LAUNCHER:
	{
		auto hero = Manager::getManager()->getHero();
		auto heroPos = hero->convertToWorldSpace(Vec2::ZERO);
		auto dir = (heroPos - pos).getNormalized();
		bf->produceBullet(m_type, pos, Vec2(0, 0), dir, 500 * (m_type % 10), 30 * (m_type % 10));
	}
		break;
	default:
		break;
	}

	
}
