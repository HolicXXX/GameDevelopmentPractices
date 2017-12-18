#include "Target.h"
#include "Manager.h"
#include "DataManager.h"
USING_NS_CC;

Target* Target::create(const std::string& str)
{
	auto t = new Target();
	if (t && t->init(str))
	{
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return nullptr;
}

bool Target::init(const std::string& str)
{
	return this->initWithFile(str);
}

void Target::initTarget(const Vec2& dir, float speed, unsigned int demage, unsigned int hp)
{
	m_hp = hp;
	setDir(dir);
	setSpeed(speed);
	setDemage(demage);

	this->scheduleUpdate();
}

void Target::initLauncher(int type)
{
	if (m_Launcher)
		this->removeChild(m_Launcher, true);
	auto launcher = Launcher::create();
	if (type / 10 == 2)
		launcher->setLauncherType(LauncherType::BOSS_LAUNCHER);
	else if (type / 10 == 1)
		launcher->setLauncherType(LauncherType::ENEMY_LAUNCHER);
	launcher->setType(type);
	launcher->setLevel(DataManager::getDataManager()->getLevel());
	launcher->setPosition(Vec2(0, 20) + this->getContentSize() / 2);
	m_Launcher = launcher;
	m_Launcher->scheduleUpdate();
	this->addChild(launcher);
}

void Target::endCall()
{
	this->unscheduleUpdate();
	m_Launcher->scheduleUpdate();
	if (m_bulletType / 10 == 1)
	{
		auto ani = Animate::create(AnimationCache::getInstance()->getAnimation("enemyexplode"));
		auto seq = Sequence::create(ani, CallFunc::create([this]()->void{
			this->removeFromParent();
		}), nullptr);
		this->runAction(seq);
	}
	else if (m_bulletType / 10 == 2)
	{
		auto ani = Animate::create(AnimationCache::getInstance()->getAnimation("bossexplode"));
		auto seq = Sequence::create(ani, CallFunc::create([this]()->void{
			this->removeFromParent();
		}), nullptr);
		this->runAction(seq);
	}
}

void Target::update(float dt)
{
	this->setPosition(this->getPosition() + m_speed * dt * m_dir);
}

void Target::pauseAll()
{
	this->pauseSchedulerAndActions();
	m_Launcher->unscheduleUpdate();
}

