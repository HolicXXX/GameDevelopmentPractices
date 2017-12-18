#ifndef _TOLLGATESCENE_H_
#define _TOLLGATESCENE_H_

#include "Player.h"

class TollgateScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	
	CREATE_FUNC(TollgateScene);

	virtual void update(float dt);

private:
	void initBG();
	void addButton();
	void addScore();
	void lableCallBack(Ref* ref);
	void restartGame();

	void restartCallBack(Ref* ref);
	void quitCallBack(Ref* ref);

	Sprite* m_bgSprite1;
	Sprite* m_bgSprite2;
	Player* m_player;

	int m_Score;
	LabelTTF* m_scoreLabel;
	LabelTTF* m_HPLabel;

};

#endif