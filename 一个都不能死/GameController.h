#pragma once
#include "Edge.h"
#include "Hero.h"
#include "Block.h"
#include "cocos2d.h"
USING_NS_CC;

class GameController : public Ref
{
private:
	Layer* _layer;
	float _positionY;
	Size visibleSize;
	int currentFrameIndex;
	int frameCount;
	Edge* edge;
	Hero* hero;
	Sprite* ground;

	float edgeheight;

	static int playerCount;
	GameController();
	~GameController();
public:

	static GameController* create(Layer* layer, float positionY, float height);
	virtual bool init(Layer* layer, float positionY, float height);
	void doUpdate(float dt);
	void onUserTouch();
	bool hitTestPoint(Vec2 point);
	bool isJump();

};
