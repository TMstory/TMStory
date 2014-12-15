#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D/Box2D.h"
#include "MycontactListener.h"
//#include "GLES-Render.h"
//#include <OpenGLES/ES1/gl.h>
#include "Data.h"
#include "MyHero.h"
#include "MyStore.h"
#include "Factory.h"
#include "MushRoom.h"
USING_NS_CC_EXT;
USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    ~HelloWorld();
    
    void AdvaceCallBack();
    void RetreatCallBack();
    void JumpCallBack();
    void moveLayerWithheroPoint();
    void checkHeroPostion();
    void TmBeyondWorld();
    void GameOver();
    void afterJumpCallBack();
    void justjumpCallBack();
    void checkMollision();
    void wSkillCallBack();
    void dartCallBack(CCSprite * dart);
    void EnterStore();
    void GameNotActive();
    
    void creatWorld();
    void creatHeroBody();
    
    void update(float f);
    void draw();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    Data * datazhi;
    MyHero * Hero;

    CCTMXTiledMap * tiledMap;
    CCTMXLayer * masklayer;
    CCTMXLayer * grasslayer;
    CCTMXLayer * masklayer1;
    b2World * world;
    b2Body * dynamicBody;
    CCArray * normalmushroom1;
    CCArray * dartsArray;
    MycontactListener * c;
    
    int adva;
    int retr;
    int jump;
    bool beyond;
    bool Active;
    CCSize mapSize;
    CCSize tileSize;
    
};

#endif // __HELLOWORLD_SCENE_H__
