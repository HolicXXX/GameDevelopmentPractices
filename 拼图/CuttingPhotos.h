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
	unsigned int _rows;//����
	unsigned int _columns;//����
	unsigned int _sliceWidth;//���ӵĿ��
	unsigned int _sliceHeight;//���ӵĸ߶�
	unsigned int _steps;

	LabelTTF* steplabel;
	LabelTTF* restartlabel;
	LabelTTF* backlabel;
	std::vector<std::vector<Sprite*>> _slices;//�洢��Ƭ
	virtual bool initWithPhoto(const char* photo, unsigned int rows, unsigned int columns);//��ʼ��
	bool initSlices(const char* photo);//�и�ͼƬ
	void initTouchEventListener();//��ʼ���¼�����
	void move(int x, int y);//�ƶ�ͼ��

};

