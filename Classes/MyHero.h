//
//  MyHero.h
//  TmStory
//
//  Created by neworigin on 14-12-10.
//
//

#ifndef __TmStory__MyHero__
#define __TmStory__MyHero__

#include <stdio.h>
#include <istream>
#include "cocos2d.h"
#include "Factory.h"
USING_NS_CC;
enum ActionType{
    StopAction ,
    WalkForward ,
    WalkBackwards ,
};
class MyHero :public CCSprite
{
public:
    MyHero();
    static MyHero * create(const char * fileName);
    void setPH(float ph);
    void setMoney(float _money);
    float getPH();
    float getMoney();
 
    
    void HeroRunAction(ActionType HeroActionType);//front为1执行向前的动作，为2时向后跑，为0时没有跑步动作
    
    void setBeginRect(CCRect rect);
    CCRect getBeginRect();
private:
    float PH;
    float money;
    
    
};

#endif /* defined(__TmStory__MyHero__) */
