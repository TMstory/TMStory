//
//  MyHero.cpp
//  TmStory
//
//  Created by neworigin on 14-12-10.
//
//

#include "MyHero.h"


MyHero * MyHero::create(const char *fileName)
{
    MyHero * hero = (MyHero *)CCSprite::create(fileName);
    hero->PH = 100;
    hero->money = 0.0;
    return hero;
}
MyHero::MyHero()
{
    this->PH = 100;
    this->money = 0.0;

}
void MyHero::HeroRunAction(ActionType HeroActionType)
{
   if (HeroActionType == StopAction){
        this->stopActionByTag(1101);
        return;
    }

    CCAnimate * animate = new CCAnimate();
    animate = Factory::shareFactory()->creatFrameAnimation(animate, "HeroAction.plist", "HeroAction.png",0.15);
    CCRepeatForever * forHeroEver = CCRepeatForever::create(animate);
    forHeroEver->setTag(1101);
    forHeroEver->retain();

    if (HeroActionType == WalkForward) {
        this->runAction(forHeroEver);
        this->setFlipX(false);
    }else if (HeroActionType == WalkBackwards){
        this->runAction(forHeroEver);
        this->setFlipX(true);
    }
}


float MyHero::getPH()
{
    return PH;
}

float MyHero::getMoney()
{
    return money;
}
void MyHero::setPH(float ph)
{
    PH = ph;
}
void MyHero::setMoney(float _money)
{
    money = _money;
}

























