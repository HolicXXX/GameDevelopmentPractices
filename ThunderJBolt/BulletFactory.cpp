#include "BulletFactory.h"
#include "Manager.h"
USING_NS_CC;

static BulletFactory* _bulletFactory = nullptr;

BulletFactory::BulletFactory()
{

}
BulletFactory::~BulletFactory()
{

}

BulletFactory* BulletFactory::getBulletFactory()
{
	if (!_bulletFactory)
	{
		_bulletFactory = new BulletFactory();
	}
	return _bulletFactory;
}

Bullet* BulletFactory::produceBullet(int type, const Vec2 & pos, const cocos2d::Vec2 & offset, const Vec2 & dir, float speed, unsigned int demage)
{
	auto layer = Manager::getManager()->getLayer();
	auto truepos = layer->convertToNodeSpace(pos) + offset;
	if (type / 10 == 0)
	{
		auto str = StringUtils::format("bullet/bullet_%02d(1).png", type);
		auto bullet = Bullet::create(str);
		bullet->initBullet(type, dir, speed, demage);
		bullet->setPosition(truepos);
		Manager::getManager()->playerAddBullet(bullet);
		return bullet;
	}
	else if (type / 10 == 1)
	{
		auto str = StringUtils::format("bullet/enemybullet_%02d.png", type % 10);
		auto bullet = Bullet::create(str);
		bullet->initBullet(type, dir, speed, demage);
		bullet->setPosition(truepos);
		Manager::getManager()->enemyAddBullet(bullet);
		return bullet;
	}
	else if (type / 10 == 2)
	{
		auto str = StringUtils::format("bullet/bossbullet_%02d(1).png", type % 10);
		auto bullet = Bullet::create(str);
		bullet->initBullet(type, dir, speed, demage);
		bullet->setPosition(truepos);
		Manager::getManager()->enemyAddBullet(bullet);
		return bullet;
	}
}

