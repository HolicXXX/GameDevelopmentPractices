
#ifndef __NoOneDies__FlashTool__
#define __NoOneDies__FlashTool__

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;

class FlashTool {
    
public:
    static Animate * readJsonSpriteSheet(std::string jsonFile,float delayPerUnit);
};


#endif 
