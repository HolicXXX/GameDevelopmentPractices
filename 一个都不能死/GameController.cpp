#include "GameController.h"

int GameController::playerCount = 0;

GameController::GameController()
{
	GameController::playerCount++;
}

GameController::~GameController()
{
	GameController::playerCount--;
	_layer->removeAllChildren();
}

GameController* GameController::create(Layer* layer, float positionY,float height)
{
	auto gc = new GameController();
	gc->init(layer, positionY,height);
	gc->autorelease();
	return gc;
}

bool GameController::init(Layer* layer, float positionY, float height)
{
	_layer = layer;
	_positionY = positionY;
	edgeheight = height;
	currentFrameIndex = 0;
	frameCount = CCRANDOM_0_1() * 120 + 100;
	visibleSize = Director::getInstance()->getVisibleSize();

	this->edge = Edge::create();
	edge->setPosition(visibleSize.width / 2, visibleSize.height / 2 + _positionY);
	edge->setContentSize(visibleSize);
	layer->addChild(edge);

	ground = Sprite::create();
	ground->setTextureRect(Rect(0, 0, visibleSize.width, 3));
	ground->setColor(Color3B::BLACK);
	ground->setPosition(visibleSize.width / 2, 1.5 + _positionY);
	layer->addChild(ground);

	hero = Hero::create(GameController::playerCount);
	hero->setPosition(Vec2(50, hero->getContentSize().height / 2 + _positionY + 3));
	layer->addChild(hero);


	return true;
}

void GameController::doUpdate(float dt)
{
	currentFrameIndex++;
	if (currentFrameIndex >= frameCount)
	{
		auto b = Block::create();
		b->setPositionY(b->getContentSize().height / 2 + _positionY);
		b->getPhysicsBody()->setContactTestBitmask(GameController::playerCount);
		_layer->addChild(b);

		currentFrameIndex = 0;
		frameCount = CCRANDOM_0_1() * 120 + 100;
	}
}

bool GameController::hitTestPoint(Vec2 point)
{
	auto pos = edge->convertToNodeSpace(point);
	auto rect = Rect(0 - edge->getContentSize().width / 2, 0 - edge->getContentSize().height / 2, edge->getContentSize().width, edgeheight);

	return rect.containsPoint(pos);
	//return edge->getBoundingBox().containsPoint(point);
}

void GameController::onUserTouch()
{
	hero->getPhysicsBody()->setVelocity(Vec2(0, 500));
}

bool GameController::isJump()
{
	return hero->getPositionY() - ground->getPositionY() > hero->getContentSize().height / 2 + 5;
}