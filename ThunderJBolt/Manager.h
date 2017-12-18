#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "Hero.h"
#include "Target.h"
#include "Bullet.h"
#include "Item.h"

class Manager
{
public:
	static Manager* getManager();

	void bindLayer(cocos2d::Layer* l){ m_layer = l; }
	void releaseLayer(){ m_layer = nullptr; }
	void bindPlayer(Hero* h){ m_hero = h; }
	void releasePlayer(){ m_hero = nullptr; }

	cocos2d::Layer* getLayer(){ return m_layer; }
	Hero* getHero(){ return m_hero; }

	Target* getBoss(){ return m_boss; }

	void init();
	void update(float dt);
	void pauseAll();

	void playerAddBullet(Bullet*);
	void enemyAddBullet(Bullet*);
private:
	Manager();
	~Manager();

	cocos2d::Layer* m_layer;
	Hero* m_hero;
	Target* m_boss;
	cocos2d::Vector<Target*> m_targets;
	cocos2d::Vector<Bullet*> m_playerbullets;
	cocos2d::Vector<Bullet*> m_enemybullets;
	cocos2d::Vector<Item*> m_items;

	void produceEnemy();
	void detectEnemy();
	void detectBullet();
	void detectPlayer();
	void produceItem(cocos2d::Vec2 pos);

};


#endif