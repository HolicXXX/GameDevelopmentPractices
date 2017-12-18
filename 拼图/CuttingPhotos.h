#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
class CuttingPhotos :
	public LayerColor
{
public:
	CuttingPhotos() : _rows(3), _columns(3),_steps(0){};
	virtual ~CuttingPhotos() { this->removeAllChildren(); };
	
	static Scene* createScene(const char* photo, unsigned int rows = 3, unsigned int columns = 3);
	static CuttingPhotos* create(const char* photo, unsigned int rows = 3, unsigned int columns = 3);
	void restart();
protected:
	unsigned int _rows;//行数
	unsigned int _columns;//列数
	unsigned int _sliceWidth;//格子的宽度
	unsigned int _sliceHeight;//格子的高度
	unsigned int _steps;

	LabelTTF* steplabel;
	LabelTTF* restartlabel;
	LabelTTF* backlabel;
	std::vector<std::vector<Sprite*>> _slices;//存储切片
	virtual bool initWithPhoto(const char* photo, unsigned int rows, unsigned int columns);//初始化
	bool initSlices(const char* photo);//切割图片
	void initTouchEventListener();//初始化事件监听
	void move(int x, int y);//移动图块

};

