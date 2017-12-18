#include "Bullet.h"
USING_NS_CC;

Bullet* Bullet::create(const std::string& str)
{
	auto b = new Bullet();
	if (b && b->init(str))
	{
		b->autorelease();
		return b;
	}
	CC_SAFE_DELETE(b);
	return nullptr;
}

bool Bullet::init(const std::string& str)
{
	return this->initWithFile(str);
}

void Bullet::initBullet(int type,const Vec2& dir,float speed, unsigned int demage)
{
	setType(type);
	setDir(dir);
	if (dir.x >= 0)
		this->setRotation(Vec2::angle(dir, Vec2(0, 1)) / 6.28 * 360);
	else
		this->setRotation(360 - Vec2::angle(dir, Vec2(0, 1)) / 6.28 * 360);
	setSpeed(speed);
	setDemage(demage);
	
	this->scheduleUpdate();
	if (m_type / 10 == 0)
	{
		auto ani = Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("bullet%02d", m_type)));
		this->runAction(RepeatForever::create(ani));
	}
	else if (m_type / 10 == 2)
	{
		auto ani = Animate::create(AnimationCache::getInstance()->getAnimation("bossbullet01"));
		this->runAction(RepeatForever::create(ani));
	}
	
}

void Bullet::endCall()
{
	this->unscheduleUpdate();
	auto type = m_type / 10;
	this->stopAllActions();
	if (type == 0)
	{
		auto ani = Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("bulletex%02d", m_type)));
		auto seq = Sequence::create(ani, CallFunc::create([this]()->void{
			this->removeFromParent();
		}), nullptr);
		this->runAction(seq);
	}
	else if (type == 2)
	{
		auto ani = Animate::create(AnimationCache::getInstance()->getAnimation("bossbulletex01"));
		auto seq = Sequence::create(ani, CallFunc::create([this]()->void{
			this->removeFromParent();
		}), nullptr);
		this->runAction(seq);
	}
	else
		this->removeFromParent();
}

void Bullet::update(float dt)
{
	this->setPosition(this->getPosition() + m_dir * m_speed * dt);
}