//
//  Factory.h
//  TmStory2
//
//  Created by neworigin on 14-12-14.
//
//

#ifndef __TmStory2__Factory__
#define __TmStory2__Factory__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Factory
{
public:
    static Factory * shareFactory();
    CCAnimate * creatFrameAnimation(CCAnimate * animate,const char * Fileplist,const char * filePng,float delay);
    ~Factory();

private:
    Factory();
private:
    static Factory * factory;
};

#endif /* defined(__TmStory2__Factory__) */
