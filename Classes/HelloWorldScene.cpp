#include "HelloWorldScene.h"
#include "Constant.h"
USING_NS_CC;
CCPoint heroAn = ccp(0.5,0.3);
CCControlButton * Advance;
CCControlButton * Retreat;
CCScene *scene1;
CCScene* HelloWorld::scene()
{
   CCScene * scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();



    scene->addChild(layer);
    

    
    Advance = CCControlButton::create(CCScale9Sprite::create("MoveButton.png"));
    Advance->setBackgroundSpriteForState(CCScale9Sprite::create("MoveButtonSelected.png"), CCControlStateHighlighted);
    Advance->setAnchorPoint(ccp(0, 0.5));
    Advance->setPosition(ccp(visible_origin.x+780, visible_origin.y+40));
    Advance->setPreferredSize(CCSizeMake(172, 60));
   // Advance->setScale(4.0);
    scene->addChild(Advance);
    
    Retreat = CCControlButton::create(CCScale9Sprite::create("MoveButton.png"));
    Retreat-> setBackgroundSpriteForState(CCScale9Sprite::create("MoveButtonSelected.png"), CCControlStateHighlighted);
    Retreat->setAnchorPoint(ccp(0, 0.5));
    Retreat->setPosition(ccp(780, 40));
    Retreat->setPreferredSize(CCSizeMake(172, 60));
   // Retreat->setScale(4.0);
    Retreat->setRotation(180);
    scene->addChild(Retreat);
    
    
    CCMenuItemImage * Jump = CCMenuItemImage::create("MoveButton.png", "MoveButtonSelected.png",layer,menu_selector(HelloWorld::JumpCallBack));
    
    Jump->setAnchorPoint(ccp(0, 0.5));
    Jump->setPosition(ccp(780,40));
    Jump->setRotation(270);
    Jump->setScale(4.0);
    
    CCMenuItemImage * wskill = CCMenuItemImage::create("w.png", "wselected.png",layer,menu_selector(HelloWorld::wSkillCallBack));
    
    wskill->setAnchorPoint(ccp(0, 0.5));
    wskill->setPosition(ccp(40,30));
    wskill->setScale(2.0);
    
    CCMenuItemFont * store = CCMenuItemFont::create("STORE", layer, menu_selector(HelloWorld::EnterStore));
    store->setPosition(900, 610);
    
    CCMenuItemFont * close = CCMenuItemFont::create("close", layer, menu_selector(HelloWorld::menuCloseCallback));
    close->setPosition(60,610);
    
    CCMenu * menu = CCMenu::create(Jump,wskill,store,close,NULL);
    menu->setAnchorPoint(CCPointZero);
    menu->setPosition(CCPointZero);
    scene->addChild(menu);
    
    CCParticleSnow * sy1 = CCParticleSnow::create();
    sy1->setBlendAdditive(true);
    sy1->setPosition(ccp(480,640));
    sy1->setDuration(-1);
    scene->addChild(sy1);
    sy1->setAutoRemoveOnFinish(true);
    scene1 = scene;

    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    datazhi = Data::creat();
    adva = 0;
    retr = 0;
    jump = 0;
    beyond = false;
    Active = true;
    
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);

    
    tiledMap = CCTMXTiledMap::create("Grass3.tmx");
    this->addChild(tiledMap);
    grasslayer = tiledMap->layerNamed("grass");
    masklayer = tiledMap->layerNamed("mask");
    masklayer1 = tiledMap->layerNamed("mask1");
    mapSize = tiledMap->getMapSize();
    tileSize = tiledMap->getTileSize();

    for (int i = 0; i<mapSize.width*mapSize.height; i++) {
        int x = i%(int)mapSize.width;
        int y = i/(int)mapSize.width;
        int gid5 = grasslayer->tileGIDAt(ccp(x, y));
        //int gid1 = masklayer1->tileGIDAt(ccp(x, y));
        
        if (gid5) {
            CCDictionary * dic = tiledMap->propertiesForGID(gid5);
            
            if (dic && dic->valueForKey("Grass")->intValue()==1) {
                CCLOG("Grass is exist");
            }
        }
    }

    //获得对象组
    normalmushroom1 = CCArray::create();
    
    CCTMXObjectGroup * objectgroup = tiledMap->objectGroupNamed("object");
    if (objectgroup) {

    CCArray * Mushrome = objectgroup->getObjects();
    for (int i = 0; i<Mushrome->count(); i++) {
        CCDictionary * dic = (CCDictionary *)Mushrome->objectAtIndex(i);
        if (dic->valueForKey("Name")->compare("NormalMushroom1") == 0 ) {
            float x = dic->valueForKey("x")->floatValue();
            float y = dic->valueForKey("y")->floatValue();
            MushRoom * sp = new MushRoom();
            sp->initWithFile("NormalMushroom1.png");
            float ph = dic->valueForKey("blood")->floatValue();
            sp->setPH(ph);
            sp->setPosition(CCPointMake(x, y));
            sp->setAnchorPoint(CCPointZero);
            sp->setScale(0.5);
           this->addChild(sp);
            normalmushroom1->addObject(sp);
        }
        if (dic->valueForKey("Name")->compare("Snake")== 0) {
            float x = dic->valueForKey("x")->floatValue();
            float y = dic->valueForKey("y")->floatValue();
            float front = dic->valueForKey("Front")->floatValue();
            float behind = dic->valueForKey("Behind")->floatValue();
            
            MushRoom * snake = new MushRoom();
            snake->initWithFile("w.png");
            snake->setAnchorPoint(ccp(0.5,0));
            snake->setPosition(ccp(x,y));

            float distance = ccpDistance(ccp(x-front*32.0,y), ccp(x+behind*32.0, y));
            CCAnimate * ani = new CCAnimate();
            ani = Factory::shareFactory()->creatFrameAnimation(ani, "SnakeWalk.plist", "SnakeWalk.png",0.2);
            CCRepeat * repeat = CCRepeat::create(ani, int(distance/SnakeDuration/0.8));
            CCMoveTo * to1 = CCMoveTo::create(distance/SnakeDuration, ccp(x-front*32.0, y));
            CCFlipX * flipx1 = CCFlipX::create(snake->getPositionX());
            CCMoveTo * to2 = CCMoveTo::create(distance/SnakeDuration, ccp(x+behind*32.0, y));
            CCSequence * que = CCSequence::create(to1,flipx1,to2,flipx1->reverse(),NULL);
            CCSpawn * spawn = CCSpawn::create(repeat,que,NULL);
            CCRepeatForever * forever = CCRepeatForever::create(spawn);
            snake->runAction(forever);
            this->addChild(snake);
        }
    }
        
    }
    normalmushroom1->retain();
    this->creatWorld();
    c = new MycontactListener();
    world->SetContactListener(c);
    
    Hero = new MyHero();
    Hero->initWithFile("hero1.png");
    Hero->setAnchorPoint(heroAn);
    Hero->setPosition(ccp(80, 250));
    this->addChild(Hero);
    this->creatHeroBody();
    dynamicBody->ApplyLinearImpulse(b2Vec2(1.0,0), b2Vec2(Hero->getPositionX()/32.0,Hero->getPositionY()/32.0));


    dartsArray = CCArray::create();
    dartsArray->retain();

    this->schedule(schedule_selector(HelloWorld::moveLayerWithheroPoint), 0.01);
    this->schedule(schedule_selector(HelloWorld::checkMollision), 0.01);
    this->scheduleUpdate();
    return true;
}
HelloWorld::~HelloWorld()
{
    normalmushroom1->release();
    dartsArray->release();
    delete world;
    delete c;
    
}

void HelloWorld::update(float f)
{
    if (Advance->isPushed()) {
        adva +=1;
        if (adva == 1) {
            this->AdvaceCallBack();
            Hero->HeroRunAction(WalkForward);
        }
    }else{
        adva = 0;
        Hero->stopActionByTag(1001);
    }
    if (Retreat->isPushed()) {
        retr +=1;
        if (retr == 1) {
            this->RetreatCallBack();
            Hero->HeroRunAction(WalkBackwards);
        }
    }else{
        retr = 0;
        Hero->stopActionByTag(1002);
       
    }
    if (!Advance->isPushed()&& !Retreat->isPushed()) {
         Hero->HeroRunAction(StopAction);
    }
    
    if (datazhi->wskill<=100) {
        datazhi->wskill += 1;
    }
    int velocityIterations = 8;
    int positionIterations = 3;
    world->Step(f, velocityIterations, positionIterations);
    for (b2Body * b = world->GetBodyList(); b; b = b->GetNext()) {
        if (b->GetUserData() != NULL) {
            MyHero * sp = (MyHero *)b->GetUserData();
            if (datazhi->getCrash()) {
                sp->setPosition(ccp(b->GetPosition().x*32.0,b->GetPosition().y*32.0+5.0));
                world->DestroyBody(b);
                datazhi->setCrash(false);
                jump = 0;
                if (beyond) {
                    beyond = false;
                }
                return;
            }
            sp->setPosition(ccp(b->GetPosition().x*32.0,b->GetPosition().y*32.0));
            if (sp->getPositionY()<=0) {
                world->DestroyBody(b);
                Hero->stopAllActions();
                jump = 0;
                this->TmBeyondWorld();
                Active = false;
                return;
            }

            }
    }
}

void HelloWorld::EnterStore()
{
    CCScene * scene = MyStore::scene();
    CCDirector::sharedDirector()->pushScene(scene);
}
void HelloWorld::checkMollision()
{
    if (normalmushroom1->count() == 0 ) {
        this->unschedule(schedule_selector(HelloWorld::checkMollision));
    }
    
    for (int i = 0; i<normalmushroom1->count(); i++) {
         MyHero * sp = (MyHero *)normalmushroom1->objectAtIndex(i);
        CCRect rect1 = sp->boundingBox();
        for (int j = 0; j<dartsArray->count(); j++) {
            CCSprite * dart = (CCSprite *)dartsArray->objectAtIndex(j);
            CCPoint point = dart->getPosition();
            if (rect1.containsPoint(point)) {
                dart->stopAllActions();
               this->dartCallBack(dart);
               sp->setPH(sp->getPH()-5);
                if (sp->getPH() <= 0) {
                    normalmushroom1->removeObjectAtIndex(i);
                    sp->removeFromParent();
                }
                return;
            }
        }

    }
}
void HelloWorld::checkHeroPostion()
{
    if (Hero->getPositionX()<=0) {
        Hero->setPositionX(0);
    }
    if (Hero->getPositionX()>=tiledMap->getMapSize().width*tiledMap->getTileSize().width) {
        Hero->setPositionX(tiledMap->getMapSize().width*tiledMap->getTileSize().width);
    }
    CCPoint point = Hero->getPosition();
    int x = point.x/tileSize.width;
    int y = mapSize.height-point.y/tileSize.height;
    
    //检查遮罩层中的x，y点是否有图块（标记）
    int gid = grasslayer->tileGIDAt(ccp(x, y));
    
    if (!beyond) {
    if (gid == 0) {
        Hero->stopActionByTag(1001);
        Hero->stopActionByTag(1002);
        this->creatHeroBody();
        if (adva) {
            adva = false;
        }else if (retr){
            retr = false;
        }
        beyond = true;
    }
    }

}

void HelloWorld::TmBeyondWorld()
{
    CCSprite * information = CCSprite::create("information.png");
    information->setPosition(visible_center);
    scene1->addChild(information);
    CCDelayTime * delaytime = CCDelayTime::create(2.0);
    CCCallFunc * func = CCCallFunc::create(this, callfunc_selector(HelloWorld::GameOver));
    CCSequence * quene = CCSequence::create(delaytime,func,NULL);
    this->runAction(quene);
   
}
void HelloWorld::GameOver()
{
    CCScene * pScene = HelloWorld::scene();
     CCDirector::sharedDirector()->replaceScene(pScene);
}
void HelloWorld::creatHeroBody()
{
    CCPoint position = Hero->getPosition();
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = Hero;
    bodyDef.position.Set(position.x/32.0, position.y/32.0);
    
    dynamicBody = world->CreateBody(&bodyDef);
    
    b2PolygonShape shap;
    shap.SetAsBox(0.5, 0.4);
    
//    b2CircleShape shap;
//    shap.m_radius = 0.4f;

    
    b2FixtureDef fixturedef;
    fixturedef.shape = &shap;
    fixturedef.density = 2.0;//密度
    fixturedef.friction = 1.0;//磨擦系数
    fixturedef.restitution = 0.0;//恢复(反弹)
    dynamicBody->CreateFixture(&fixturedef);
    //dynamicBody->ApplyAngularImpulse(5);
    // dynamicBody->ApplyLinearImpulse(b2Vec2(25,15), bodyDef.position);
    

}


void HelloWorld::creatWorld()
{

    //获取坐标对
    float startX[200];
    float startY[200];
    float endX[200];
    float endY[200];
    float width = mapSize.width;
    float height = mapSize.height;
    CCLOG("width = %f * %f",width,height);
    int a = 0;
    for (int i = 0; i<width*height; i++) {
        int x = i%(int)width;
        int y = i/(int)width;
        int gid = masklayer->tileGIDAt(ccp(x, y));
        int gid1 = masklayer1->tileGIDAt(ccp(x, y));
        
        if (gid) {
                startX[a] = x;
                startY[a] =height - y -1;
        }
        if (gid1) {
            endX[a] = x+1;
            endY[a] =height - y -1;
            a++;
        }
}
       
    
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
    world->SetAllowSleeping(true);
    world->SetContinuousPhysics(true);
    
    b2BodyDef bodrDef;
    bodrDef.position.Set(0, 0);
    b2Body * groundBody = world->CreateBody(&bodrDef);
    
    b2EdgeShape shap;
    for (int i = 0; i<=a; i++) {
        shap.Set(b2Vec2(startX[i],startY[i]), b2Vec2(endX[i],endY[i]));
        groundBody->CreateFixture(&shap, 0);
    }
//    shap.Set(b2Vec2(0,0), b2Vec2(mapSize.width*tileSize.width,0));
//    groundBody->CreateFixture(&shap, 0);
    shap.Set(b2Vec2(0,0), b2Vec2(0,(mapSize.height+10)*tileSize.height));
    groundBody->CreateFixture(&shap, 0);
    shap.Set(b2Vec2(mapSize.width*tileSize.width,0), b2Vec2(mapSize.width*tileSize.width,(mapSize.height+10)*tileSize.height));
    groundBody->CreateFixture(&shap, 0);

    
//    GLESDebugDraw * m_debugDraw = new GLESDebugDraw(32.0);
//   
//    uint32 flag = 0;
//    flag += GLESDebugDraw::e_shapeBit;
//    flag += b2Draw::e_jointBit;
//    flag += b2Draw::e_aabbBit;
//    flag += b2Draw::e_pairBit;
//    flag += b2Draw::e_centerOfMassBit;
//    m_debugDraw->SetFlags(flag);
//     world->SetDebugDraw(m_debugDraw);
    
  }

void HelloWorld::draw()
{
//    CCLayer::draw();
//    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
//    
//    kmGLPushMatrix();
//    
//    world->DrawDebugData();
//    
//    kmGLPopMatrix();
//    
//    CHECK_GL_ERROR_DEBUG();
}
void HelloWorld::moveLayerWithheroPoint()
{
    CCPoint heroPoint = Hero->getPosition();
    CCSize tiledSize = tiledMap->getTileSize();//获取每一块的像素大小
    CCSize mapSize = tiledMap->getMapSize();//获取块数
    float x = MAX(240, heroPoint.x);
    float y = MAX(320, heroPoint.y+40);
    x = MIN(x, tiledSize.width * mapSize.width-240);
    y = MIN(y, tiledSize.height * mapSize.height-160);
   // y = MIN(y, 640);
    CCPoint subpoint = ccpSub(ccp(240,320), ccp(x, y));
    this->setPosition(subpoint);
}
bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{

    return true;
}
void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}
void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}
void HelloWorld::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}



void HelloWorld::AdvaceCallBack()
{
    if (Active) {
        Hero->HeroRunAction(WalkForward);
    if (adva) {

        if (jump) {
            dynamicBody->ApplyLinearImpulse(b2Vec2(2,0), b2Vec2(Hero->getPositionX()/32.0,Hero->getPositionY()/32.0));
            return;
        }
        if (!jump) {
    CCMoveBy * moveby = CCMoveBy::create(0.1, ccp(10, 0));
        CCCallFunc * func = CCCallFunc::create(this, callfunc_selector(HelloWorld::checkHeroPostion));
        CCSequence * quene = CCSequence::create(moveby,func,NULL);
    CCRepeatForever * forever = CCRepeatForever::create(quene);
    forever->setTag(1001);
    Hero->runAction(forever);
        }
    }
    }
}

void HelloWorld::RetreatCallBack()
{
    if (Active) {
        Hero->HeroRunAction(WalkBackwards);
    if (retr) {

        if (jump) {            
            dynamicBody->ApplyLinearImpulse(b2Vec2(-2,0), b2Vec2(Hero->getPositionX()/32.0,Hero->getPositionY()/32.0));
            return;
        }
        CCMoveBy * moveby = CCMoveBy::create(0.1, ccp(-10, 0));
        CCCallFunc * func = CCCallFunc::create(this, callfunc_selector(HelloWorld::checkHeroPostion));
        CCSequence * quene = CCSequence::create(moveby,func,NULL);
        CCRepeatForever * forever = CCRepeatForever::create(quene);
        forever->setTag(1002);
        Hero->runAction(forever);
    }
    }
}

void HelloWorld::JumpCallBack()
{
    if (Active) {
    if (!jump) {

        jump = 1;
        this->creatHeroBody();
 dynamicBody->ApplyLinearImpulse(b2Vec2(0,15), b2Vec2(Hero->getPositionX()/32.0,Hero->getPositionY()/32.0));
    }else if (jump == 1) {
         dynamicBody->ApplyLinearImpulse(b2Vec2(0,10), b2Vec2(Hero->getPositionX()/32.0,Hero->getPositionY()/32.0));
        jump=2;
    }
    }
}
void HelloWorld::justjumpCallBack()
{
    this->schedule(schedule_selector(HelloWorld::checkHeroPostion), 0.01);
}
void HelloWorld::afterJumpCallBack()
{
    jump = false;
}

void HelloWorld::wSkillCallBack()
{
    if (Active) {
    if (datazhi->wskill>=40) {
        CCSprite * darts = CCSprite::create("darts.png");
        darts->setPosition(Hero->getPosition());
        this->addChild(darts);
        dartsArray->addObject(darts);


        if (Hero->isFlipX()) {
            darts->setFlipX(true);
            CCMoveBy * moveby = CCMoveBy::create(0.5, ccp(-150,0));
            CCCallFuncN * func = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::dartCallBack));
            CCSequence * quence = CCSequence::create(moveby,func,NULL);
            darts->runAction(quence);
            datazhi->wskill = 0;
        }else{
            CCMoveBy * moveby = CCMoveBy::create(0.5, ccp(150,0));
            CCCallFuncN * func = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::dartCallBack));
            CCSequence * quence = CCSequence::create(moveby,func,NULL);
            darts->runAction(quence);
        datazhi->wskill = 0;
        }
    }
    }

}
void HelloWorld::dartCallBack(CCSprite * dart)
{
    dart->removeFromParent();
    dartsArray->removeObject(dart);
    
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
