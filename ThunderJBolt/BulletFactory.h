#ifndef _BULLETFACTORY_H_
#define _BULLETFACTORY_H_

#include "cocos2d.h"
#include "Bullet.h"

class BulletFactory
{
public:
	static BulletFactory* getBulletFactory();

	Bullet* produceBullet(int type, const cocos2d::Vec2 & pos, const cocos2d::Vec2 & offset, const cocos2d::Vec2 & dir, float speed, unsigned int demage);

private:
	BulletFactory();
	~BulletFactory();
};


#endif