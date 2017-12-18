#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include"Card.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	int startX, startY, endX, endY;

	int score;
	LabelTTF* scoreLabel;

	bool doLeft();
	bool doRight();
	bool doUp();
	bool doDown();

	void createCard(cocos2d::Size size);

	void addRandomCard();

	void doCheckGameOver();

	std::vector<std::vector<Card*>> cardVec;


	void retCallBack(Ref* ref);

};

#endif // __HELLOWORLD_SCENE_H__
