#include "Player.h"

Player::Player()
	:m_isJumping(false),
	m_HP(1000)
{
}

Player::~Player()
{
}

bool Player::init()
{
	return true;
}

void Player::jump()
{
	if (getSprite() == nullptr)
		return;

	if (m_isJumping)
	{
		return;
	}
	m_isJumping = true;

	auto action = Sequence::create(JumpBy::create(2.0f, Vec2(0, 0), 160, 1), CallFunc::create([&](){m_isJumping = false; }), nullptr);

	this->runAction(action);
}

void Player::hit()
{
	if (getSprite() == nullptr)
		return;

	auto flowword = LabelTTF::create("-15", "fonts/Marker Felt.ttf", 24);
	flowword->setColor(Color3B(255, 0, 0));
	this->addChild(flowword);

	auto wordACT = Spawn::create(MoveBy::create(0.5f, Vec2(0, this->getContentSize().height)), FadeIn::create(0.5f), nullptr);
	auto s1 = Sequence::create(wordACT, CallFunc::create([this,flowword](){
		this->removeChild(flowword);
	}), nullptr);

	flowword->runAction(s1);

	

	auto backmove = MoveBy::create(0.1f, Vec2(-10, 0));
	auto formove = backmove->reverse();
	auto backrotate = RotateBy::create(0.1f, -5, 0);
	auto forrotate = backrotate->reverse();

	auto back = Spawn::create(backmove, backrotate, nullptr);
	auto forword = Spawn::create(formove, forrotate, nullptr);

	auto s2 = Sequence::create(back, forword, nullptr);

	this->stopAllActions();
	resetData();
	this->runAction(s2);

	m_HP -= 15;
	if (m_HP <= 0)
		m_HP = 0;
	log("HIT");

}

void Player::resetData()
{
	if (m_isJumping)
		m_isJumping = false;
	setPosition(Vec2(120, 80));
	setScale(1.0f);
	setRotation(0);
}

int Player::getHP()
{
	return m_HP;
}
