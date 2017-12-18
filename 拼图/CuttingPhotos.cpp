#include "CuttingPhotos.h"
#include "HelloWorldScene.h"

Scene* CuttingPhotos::createScene(const char* photo, unsigned int rows, unsigned int columns)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto scene = Scene::create();
	auto ground = LayerColor::create(Color4B::WHITE);
	scene->addChild(ground);

	auto layer = CuttingPhotos::create(photo, rows, columns);
	layer->setAnchorPoint(Vec2::ZERO);
	layer->setPosition(
		origin.x + visibleSize.width / 2 - layer->getContentSize().width / 2,
		origin.y + visibleSize.height / 2 - layer->getContentSize().height / 2
		);
	ground->addChild(layer);

	auto oriPhoto = Sprite::create(photo);
	oriPhoto->setScale(0.3f);
	oriPhoto->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	oriPhoto->setPosition(0, visibleSize.height);
	ground->addChild(oriPhoto);


	return scene;

}

CuttingPhotos* CuttingPhotos::create(const char* photo, unsigned int rows, unsigned int columns)
{
	auto cp = new CuttingPhotos();
	if (cp != nullptr && cp->initWithPhoto(photo, rows, columns))
	{
		cp->autorelease();
		return cp;
	}
	CC_SAFE_DELETE(cp);
	return nullptr;
}

bool CuttingPhotos::initWithPhoto(const char* photo, unsigned int rows, unsigned int columns)
{
	bool ret = true;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("FX084.mp3");
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
	if (LayerColor::initWithColor(Color4B::WHITE))
	{
		_rows = rows;
		_columns = columns;
		if (initSlices(photo))
		{
			initTouchEventListener();
			restart();
			ret = true;
		}
		else
			ret = false;
	}
	else
		ret = false;
	return ret;
}

bool CuttingPhotos::initSlices(const char* photo)
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(photo);
	if (texture == nullptr)
		return false;

	//计算图片的宽和高
	auto size = texture->getContentSize();
	_sliceWidth = size.width / _columns;
	_sliceHeight = size.height / _rows;
	this->setContentSize(size);//设置Layer大小

	auto photo_frame = Sprite::create("photo_frame.png");
	photo_frame->setPosition(size / 2);
	this->addChild(photo_frame);

	steplabel = LabelTTF::create("Steps:0", "", 36);
	steplabel->setColor(Color3B::BLACK);
	this->addChild(steplabel);
	steplabel->setPosition(Vec2(this->getContentSize().width / 2, 0 - steplabel->getContentSize().height));

	//初始化二维数组
	for (int h = 0; h < _rows; ++h)
	{
		std::vector<Sprite*> row;
		for (int w = 0; w < _columns; ++w)
		{
			row.push_back(nullptr);
		}
		_slices.push_back(row);
	}

	//挖出最后一块切片
	auto endSlice = Sprite::createWithTexture(texture, Rect(_sliceWidth*(_columns - 1), _sliceHeight*(_rows - 1), _sliceWidth, _sliceHeight));
	endSlice->setAnchorPoint(Vec2::ZERO);
	endSlice->setPosition(_sliceWidth*(_columns - 1), 0);
	endSlice->setOpacity(100);//设置透明度0-255，越低越透明
	this->addChild(endSlice);

	for(int h = 0; h < _rows; ++h)
	{
		for (int w = 0; w < _columns; ++w)
		{
			if (w == _columns - 1 && h == _rows - 1)
				break;
			auto slice = Sprite::createWithTexture(texture, Rect(
				_sliceWidth*w,_sliceHeight*h,_sliceWidth,_sliceHeight
				));
			slice->setAnchorPoint(Vec2::ZERO);
			slice->setPosition(_sliceWidth*w, size.height - (h + 1)*_sliceHeight);
			this->addChild(slice);
			_slices[h][w] = slice;
		}
	}

	return true;
}

void CuttingPhotos::initTouchEventListener()
{
	//重置按键
	restartlabel = LabelTTF::create("Restart","",36);
	restartlabel->setColor(Color3B::BLACK);
	restartlabel->setPosition(
		this->getContentSize().width + restartlabel->getContentSize().width,
		0 - restartlabel->getContentSize().height);
	this->addChild(restartlabel);

	auto restartlistener = EventListenerTouchOneByOne::create();
	restartlistener->onTouchBegan = [&](Touch* t, Event* e){
		Point localposition = this->restartlabel->convertToNodeSpace(t->getLocation());
		Rect rect{ 0, 0, this->restartlabel->getContentSize().width, this->restartlabel->getContentSize().height };
		if (rect.containsPoint(localposition))
			this->restart();
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(restartlistener, this->restartlabel);
	
	//返回主界面按键
	backlabel = LabelTTF::create("BackToSelectPage","",36);
	backlabel->setColor(Color3B::BLACK);
	backlabel->setPosition(Vec2(0, 0 - backlabel->getContentSize().height));
	restartlabel->addChild(backlabel);

	auto backlistener = EventListenerTouchOneByOne::create();
	backlistener->onTouchBegan = [&](Touch* t, Event* e){
		Point localposition = this->backlabel->convertToNodeSpace(t->getLocation());
		Rect rect{ 0, 0, this->backlabel->getContentSize().width, this->backlabel->getContentSize().height };
		if (rect.containsPoint(localposition))
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelloWorld::createScene()));
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(backlistener, this->backlabel);


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* t, Event* e){

		Point localposition = this->convertToNodeSpace(t->getLocation());
		Rect rect{ 0, 0, this->getContentSize().width, this->getContentSize().height };
		if (rect.containsPoint(localposition))
		{
			return true;
		}
		else
		{
			return false;
		}

	};

	listener->onTouchEnded = [&](Touch* t, Event* e){
		Point localposition = this->convertToNodeSpace(t->getLocation());
		int w = static_cast<int>(localposition.x / this->_sliceWidth);
		int h = static_cast<int>(localposition.y / this->_sliceHeight);
		this->move(h, w);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void CuttingPhotos::move(int h, int w)
{
	h = _rows - 1 - h;
	auto slice = _slices[h][w];
	if (slice == nullptr)
		return;

	bool isfind = false;
	Point tarpos;
	
	if (h < _rows - 1 && _slices[h + 1][w] == nullptr)
	{
		tarpos.x = w;
		tarpos.y = h + 1;
		isfind = true;
	}
	else if (h > 0 && _slices[h - 1][w] == nullptr)
	{
		tarpos.x = w;
		tarpos.y = h - 1;
		isfind = true;
	}
	else if (w < _columns - 1 && _slices[h][w + 1] == nullptr)
	{
		tarpos.x = w + 1;
		tarpos.y = h;
		isfind = true;
	}
	else if (w > 0 && _slices[h][w - 1] == nullptr)
	{
		tarpos.x = w - 1;
		tarpos.y = h;
		isfind = true;
	}

	if (isfind == false)
	{
		return;
	}

	_steps++;
	char s[10]{};
	sprintf(s, "Steps:%d", _steps);
	steplabel->setString(s);
	SimpleAudioEngine::getInstance()->playEffect("FX084.mp3");
	slice->runAction(MoveTo::create(0.2f, Vec2(tarpos.x * _sliceWidth, (_rows - 1 - tarpos.y)*_sliceHeight)));
	_slices[tarpos.y][tarpos.x] = slice;
	_slices[h][w] = nullptr;


}

void CuttingPhotos::restart()
{
	//
	Vector<Sprite*> vec;

	for (int h = 0; h < _rows; ++h)
		for (int w = 0; w < _columns; ++w)
		{
			auto slice = _slices[h][w];
			if (slice != nullptr)
			{
				vec.pushBack(slice);
			}
		}
	
	for (int h = 0; h < _rows; ++h)
		for (int w = 0; w < _columns; ++w)
		{
			if (w == _columns - 1 && h == _rows - 1)
			{
				_slices[h][w] = nullptr;
				break;
			}
			auto length = vec.size();
			auto ran = static_cast<int>(CCRANDOM_0_1()*length);
			auto slice = vec.at(ran);
			vec.eraseObject(slice);
			
			slice->setPosition(_sliceWidth * w, _sliceHeight * (_rows - 1 - h));
			_slices[h][w] = slice;
			
		}

}
