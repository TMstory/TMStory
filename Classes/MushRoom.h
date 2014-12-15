//
//  MushRoom.h
//  TmStory2
//
//  Created by neworigin on 14-12-14.
//
//

#ifndef __TmStory2__MushRoom__
#define __TmStory2__MushRoom__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class MushRoom :public CCSprite
{
public:
    MushRoom();
    
    float getPH();
    void setPH(float ph);
private:
    float PH;
};

#endif /* defined(__TmStory2__MushRoom__) */
