//
//  Factory.cpp
//  TmStory2
//
//  Created by neworigin on 14-12-14.
//
//

#include "Factory.h"
Factory * Factory::factory = NULL;
Factory::Factory()
{
    
}
Factory * Factory::shareFactory()
{
    if (!factory) {
        factory = new Factory();
    }
    return factory;
}

CCAnimate * Factory::creatFrameAnimation(CCAnimate *animate, const char *Fileplist, const char *filePng,float delay)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Fileplist, filePng);
    CCDictionary * dic = CCDictionary::createWithContentsOfFile(Fileplist);
    CCDictionary * dic1 = (CCDictionary *)dic->objectForKey("frames");
    CCArray * Names = dic1->allKeys();
    CCArray * array = CCArray::create();
    for (int i = 0; i<Names->count(); i++) {
        CCString * str = (CCString *)Names->objectAtIndex(i);
        const char * name = str->getCString();
        CCSpriteFrame * fg = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
        array->addObject(fg);
    }
   // float de = delay/Names->count();
    CCAnimation * animation = CCAnimation::createWithSpriteFrames(array,delay);
    animate = CCAnimate::create(animation);
    return animate;
}
