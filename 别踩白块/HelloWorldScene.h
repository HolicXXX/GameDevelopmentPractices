#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"

class HelloWorld : public cocos2d::Layer
{
private:
	Size visibleSize;
	int lineIndex;
	int lineCount;
	bool showEnd;

	long startTime;
	bool isRunning;

	Label* timerLabel;
	Node* gameLayer;


	void reStart();
	void clickCallBack(Ref* ref);

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void update(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void startGame();

	void addStartLine();
	void addEndLine();
	void addNormalLine(int index);
	void moveDown();
	void startTimer();
	void stopTimer();
};

#endif // __HELLOWORLD_SCENE_H__
