#include "Edge.h"
USING_NS_CC;

Edge* Edge::create()
{
	auto edge = new Edge();
	if (edge && edge->init())
	{
		edge->autorelease();
		return edge;
	}
	CC_SAFE_DELETE(edge);
	return nullptr;
}
bool Edge::init()
{
	Node::init();
	auto size = Director::getInstance()->getVisibleSize();
	setPhysicsBody(PhysicsBody::createEdgeBox(size));
	getPhysicsBody()->setDynamic(false);

	return true;

}