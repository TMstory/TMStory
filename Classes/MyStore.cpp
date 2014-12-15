//
//  MyStore.cpp
//  TmStory2
//
//  Created by neworigin on 14-12-12.
//
//

#include "MyStore.h"
#include "Constant.h"
#include "Data.h"
bool ismove=false;
CCLayer *layer[9];
Data *adata=Data::creat();
bool MyStore::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    this->setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);
    CCScale9Sprite *button1prite=CCScale9Sprite::create("heroBack1.png");
    CCControlButton *button1=CCControlButton::create(button1prite);
    button1->setPreferredSize(CCSizeMake(71, 71));
    button1->setPosition(visible_origin.x+50, visible_center.y+30);
    button1->setTag(1);
    button1->setTouchPriority(0);
    button1->addTargetWithActionForControlEvents(this, cccontrol_selector(MyStore::addscrollview), CCControlEventTouchUpInside);
    addChild(button1);
    CCScale9Sprite *button2prite=CCScale9Sprite::create("heroBack1.png");
    CCControlButton *button2=CCControlButton::create(button2prite);
    button2->setPreferredSize(CCSizeMake(71, 71));
    button2->setPosition(visible_origin.x+50, visible_center.y-70);
    button2->setTag(2);
    button2->setTouchPriority(0);
    button2->addTargetWithActionForControlEvents(this, cccontrol_selector(MyStore::addscrollview), CCControlEventTouchUpInside);
    addChild(button2);
    
    //添加分数和蘑菇显示
    CCSprite *scoresprite=CCSprite::create("NormalMushroom1.png");
    scoresprite->setPosition(ccp(visible_center.x-200, visible_Size.height-70));
    addChild(scoresprite);
    CCSprite *scoresprite2=CCSprite::create("NormalMushroom2.png");
    scoresprite2->setPosition(ccp(visible_center.x+50, visible_Size.height-70));
    addChild(scoresprite2);
    CCString *score=CCString::createWithFormat("%d",adata->getscore());
    CCString *mushroom=CCString::createWithFormat("%d",adata->getmushroom());
    CCLabelTTF *scorettf=CCLabelTTF::create(score->getCString(), "", 60);
    scorettf->setPosition(ccp(visible_center.x-100, visible_Size.height-70));
    scorettf->setTag(600);
    addChild(scorettf);
    CCLog("%p",scorettf);
    CCLabelTTF *scorettf2=CCLabelTTF::create(mushroom->getCString(), "", 60);
    scorettf2->setPosition(ccp(visible_center.x+150, visible_Size.height-70));
    scorettf2->setTag(601);
    addChild(scorettf2);
    CCLog("2%p",scorettf2);
    //首次进入的scroll:
    scrollview=CCScrollView::create(CCSizeMake(700, 215));
    scrollview->setPosition(visible_center);
    scrollview->setDirection(kCCScrollViewDirectionHorizontal);
    scrollview->ignoreAnchorPointForPosition(false);
    scrollview->setTag(10);
    addChild(scrollview);
    scrollview->setDelegate(this);
    scrollview->setContentSize(CCSizeMake(1440, 215));
    for (int i=0; i<9; i++) {
        CCString *equipstring=CCString::createWithFormat("equip_%d.png",i+1);
        CCScale9Sprite *buttonsprite=CCScale9Sprite::create(equipstring->getCString());
        CCControlButton *button=CCControlButton::create(buttonsprite);
        button->setPreferredSize(CCSizeMake(120, 215));
        button->setPosition(i*160, visible_origin.y);
        button->setTag(100+i);
        button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyStore::buyequip), CCControlEventTouchUpInside);
        scrollview->addChild(button);
    }
    CCMenuItemFont *font=CCMenuItemFont::create("BACK", this, menu_selector(MyStore::back));
    CCMenu* backmenu=CCMenu::create(font,NULL);
    backmenu->setPosition(ccp(visible_origin.x+50, visible_Size.height-50));
    addChild(backmenu);
    
    this->addmenu();
    return true;
}
//添加道具栏
void MyStore::addmenu()
{
    for (int i=0; i<6; i++) {
        layer[i]=CCLayer::create();
        layer[i]->setContentSize(CCSizeMake(65, 65));
        layer[i]->setPosition(visible_origin.x+320+i*56, visible_origin.y+100);
        addChild(layer[i]);
        CCMenuItemImage *equipimage=CCMenuItemImage::create("equip.png", "equip.png", this, menu_selector(MyStore::sellequip));
        CCMenu *equipmenu=CCMenu::create(equipimage,NULL);
        equipmenu->setPosition(ccp(23, 24));
        equipimage->setTag(300+i);
        layer[i]->addChild(equipmenu);
    }
    for (int i=0; i<3; i++) {
        layer[i+6]=CCLayer::create();
        layer[i+6]->setContentSize(CCSizeMake(65, 65));
        layer[i+6]->setPosition(visible_origin.x+370+i*56, visible_origin.y+20);
        addChild(layer[i+6]);
        CCMenuItemImage *equipimage=CCMenuItemImage::create("equip.png", "equip.png", this, menu_selector(MyStore::sellequip));
        CCMenu *equipmenu=CCMenu::create(equipimage,NULL);
        equipmenu->setPosition(ccp(23, 24));
        equipimage->setTag(400+i);
        layer[i+6]->addChild(equipmenu);
    }
    //读取记录
    this->readlist();
}
void MyStore::readlist()
{
    if(adata->getbloodvial()>0)
    {
        CCSprite *sprite=CCSprite::create("eq1.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(700);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[0]->addChild(sprite);
    }
    if(adata->getbloodvial()>1)
    {
        CCSprite *sprite=CCSprite::create("eq1_2.png");
        sprite->setScale(0.8);
        sprite->setZOrder(3);
        sprite->setTag(701);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[0]->addChild(sprite);
    }
    if(adata->getbloodvial()>2)
    {
        CCSprite *sprite=CCSprite::create("eq1_3.png");
        sprite->setScale(0.8);
        sprite->setZOrder(4);
        sprite->setTag(702);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[0]->addChild(sprite);
    }
    if(adata->getbloodvial()>3)
    {
        CCSprite *sprite=CCSprite::create("eq1_4.png");
        sprite->setScale(0.8);
        sprite->setZOrder(5);
        sprite->setTag(703);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[0]->addChild(sprite);
    }
    if(adata->getrainbow()>0)
    {
        CCSprite *sprite=CCSprite::create("eq2.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(705);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[1]->addChild(sprite);
    }
    if (adata->gethat()>0)
    {
        CCSprite *sprite=CCSprite::create("eq3.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(706);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[2]->addChild(sprite);
    }
    if(adata->getshoe()>0)
    {
        CCSprite *sprite=CCSprite::create("eq4.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(707);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[3]->addChild(sprite);
    }
    if (adata->getsupershoe()>0)
    {
        CCSprite *sprite=CCSprite::create("eq5.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(708);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[3]->addChild(sprite);
    }
    if (adata->getarmor()>0)
    {
        CCSprite *sprite=CCSprite::create("eq6.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(709);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[4]->addChild(sprite);
    }
    if (adata->getsuperarmor()>0)
    {
        CCSprite *sprite=CCSprite::create("eq7.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(710);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[4]->addChild(sprite);
    }
    if (adata->getbelt()>0)
    {
        CCSprite *sprite=CCSprite::create("eq8.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(711);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[5]->addChild(sprite);
    }
    if (adata->getsuperbelt()>0)
    {
        CCSprite *sprite=CCSprite::create("eq9.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(712);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[5]->addChild(sprite);
    }
    if (adata->getlan()>0)
    {
        CCSprite *sprite=CCSprite::create("eq10.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(713);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[6]->addChild(sprite);
    }
    if (adata->getai()>0)
    {
        CCSprite *sprite=CCSprite::create("eq11.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(714);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[7]->addChild(sprite);
    }
    if (adata->getsi()>0)
    {
        CCSprite *sprite=CCSprite::create("eq12.png");
        sprite->setScale(0.8);
        sprite->setZOrder(2);
        sprite->setTag(715);
        sprite->setAnchorPoint(ccp(0, 0));
        layer[8]->addChild(sprite);
    }
}
void MyStore::back()
{
    CCDirector::sharedDirector()->popScene();
}
void MyStore::sellequip(CCMenuItemImage *item)
{
    switch (item->getTag()) {
        case 300:
        {
            if (adata->getbloodvial()==4) {
                layer[0]->removeChildByTag(703);
                adata->setscore(adata->getscore()+MYbloodvial*MYrate);
                adata->setbloodvial(adata->getbloodvial()-1);
            }
            else if (adata->getbloodvial()==3)
            {
                layer[0]->removeChildByTag(702);
                adata->setscore(adata->getscore()+MYbloodvial*MYrate);
                adata->setbloodvial(adata->getbloodvial()-1);
            }
            else if (adata->getbloodvial()==2)
            {
                layer[0]->removeChildByTag(701);
                adata->setscore(adata->getscore()+MYbloodvial*MYrate);
                adata->setbloodvial(adata->getbloodvial()-1);
            }
            else if (adata->getbloodvial()==1)
            {
                layer[0]->removeChildByTag(700);
                adata->setscore(adata->getscore()+MYbloodvial*MYrate);
                adata->setbloodvial(adata->getbloodvial()-1);
            }
        }
            break;
        case 301:
        {
            if (adata->getrainbow()==1) {
                layer[1]->removeChildByTag(705);
                adata->setscore(adata->getscore()+MYrainbow*MYrate);
                adata->setrainbow(adata->getrainbow()-1);
            }
        }
            break;
        case 302:
        {
            if (adata->gethat()==1) {
                layer[2]->removeChildByTag(706);
                adata->setscore(adata->getscore()+MYhat*MYrate);
                adata->sethat(adata->gethat()-1);
            }
        }
            break;
        case 303:
        {
            if (adata->getshoe()==1) {
                layer[3]->removeChildByTag(707);
                adata->setscore(adata->getscore()+MYshoe*MYrate);
                adata->setshoe(adata->getshoe()-1);
            }
            else if (adata->getsupershoe()==1) {
                layer[3]->removeChildByTag(708);
                adata->setscore(adata->getscore()+MYsupershoe*MYrate);
                adata->setsupershoe(adata->getsupershoe()-1);
            }
        }
            break;
        case 304:
        {
            if (adata->getarmor()==1) {
                layer[4]->removeChildByTag(709);
                adata->setscore(adata->getscore()+MYarmor*MYrate);
                adata->setarmor(adata->getarmor()-1);
            }
            else if (adata->getsuperarmor()==1) {
                layer[4]->removeChildByTag(710);
                adata->setscore(adata->getscore()+MYsuperarmor*MYrate);
                adata->setsuperarmor(adata->getsuperarmor()-1);
            }
        }
            break;
        case 305:
        {
            if (adata->getbelt()==1) {
                layer[5]->removeChildByTag(711);
                adata->setscore(adata->getscore()+MYbelt*MYrate);
                adata->setbelt(adata->getbelt()-1);
            }
            else if (adata->getsuperbelt()==1) {
                layer[5]->removeChildByTag(712);
                adata->setscore(adata->getscore()+MYsuperbelt*MYrate);
                adata->setsuperbelt(adata->getsuperbelt()-1);
            }
        }
            break;
        case 400:
        {
            if (adata->getlan()==1) {
                layer[6]->removeChildByTag(713);
                adata->setmushroom(adata->getmushroom()+MYlan*MYmushrate);
                adata->setlan(adata->getlan()-1);
            }
        }
            break;
        case 401:
        {
            if (adata->getai()==1) {
                layer[7]->removeChildByTag(714);
                adata->setmushroom(adata->getmushroom()+MYai*MYmushrate);
                adata->setai(adata->getai()-1);
            }
        }
            break;
        case 402:
        {
            if (adata->getsi()==1) {
                layer[8]->removeChildByTag(715);
                adata->setmushroom(adata->getmushroom()+MYsi*MYmushrate);
                adata->setsi(adata->getsi()-1);
            }
        }
            break;
        default:
            break;
    }
    CCLabelTTF *label=(CCLabelTTF *)this->getChildByTag(600);
    CCLog("%p",label);
    CCString *labelstring=CCString::createWithFormat("%d",adata->getscore());
    label->setString(labelstring->getCString());
    CCLabelTTF *label2=(CCLabelTTF *)this->getChildByTag(601);
    CCString *labelstring2=CCString::createWithFormat("%d",adata->getmushroom());
    CCLog("%d",adata->getmushroom());
    label2->setString(labelstring2->getCString());
}
void MyStore::scrollViewDidScroll(CCScrollView* view)
{
    this->unschedule(schedule_selector(MyStore::changemove));
    ismove=true;
    this->scheduleOnce(schedule_selector(MyStore::changemove), 0.2);
}
void MyStore::scrollViewDidZoom(CCScrollView* view)
{
    
}
void MyStore::addscrollview(CCControlButton *button)
{
    
    if (button->getTag()==1) {
        //普通商城
        //scrollview->removeAllChildren();
        this->removeChildByTag(10);
        scrollview=CCScrollView::create(CCSizeMake(700, 215));
        scrollview->setPosition(visible_center);
        scrollview->setDirection(kCCScrollViewDirectionHorizontal);
        scrollview->ignoreAnchorPointForPosition(false);
        scrollview->setTag(10);
        addChild(scrollview);
        scrollview->setDelegate(this);
        scrollview->setContentSize(CCSizeMake(1400, 215));
        for (int i=0; i<9; i++) {
            CCString *equipstring=CCString::createWithFormat("equip_%d.png",i+1);
            CCScale9Sprite *buttonsprite=CCScale9Sprite::create(equipstring->getCString());
            CCControlButton *button=CCControlButton::create(buttonsprite);
            button->setPreferredSize(CCSizeMake(120, 215));
            button->setPosition(i*160, visible_origin.y);
            button->setTag(100+i);
            button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyStore::buyequip), CCControlEventTouchUpInside);
            scrollview->addChild(button);
        }
    }
    else if (button->getTag()==2)
    { //蘑菇商城
        this->removeChildByTag(10);
        scrollview=CCScrollView::create(CCSizeMake(700, 215));
        scrollview->setPosition(visible_center);
        scrollview->setDirection(kCCScrollViewDirectionHorizontal);
        scrollview->ignoreAnchorPointForPosition(false);
        scrollview->setTag(10);
        addChild(scrollview);
        scrollview->setDelegate(this);
        scrollview->setContentSize(CCSizeMake(700, 215));
        for (int i=0; i<3; i++) {
            CCString *equipstring=CCString::createWithFormat("equip_%d.png",i+10);
            CCScale9Sprite *buttonsprite=CCScale9Sprite::create(equipstring->getCString());
            CCControlButton *button=CCControlButton::create(buttonsprite);
            button->setPreferredSize(CCSizeMake(120, 215));
            button->setPosition(i*240, visible_origin.y);
            button->setTag(200+i);
            button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyStore::buyequip), CCControlEventTouchUpInside);
            scrollview->addChild(button);
        }
    }
}
void MyStore::changemove()
{
    ismove=false;
}
bool MyStore::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void MyStore::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
   
}
void MyStore::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
   
}
void MyStore::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void MyStore::buyequip(CCControlButton *button)
{
    
    if (!ismove)
    {
    switch (button->getTag()) {
        case 100:
        {
            if (adata->getscore()<MYbloodvial) {
                CCMessageBox("金钱不够", "提醒");
            }
            else if (adata->getbloodvial()>=4)
            {
                CCMessageBox("血瓶数量已经到上限", "提醒");
            }
            else if(adata->getbloodvial()==0)
            {
            adata->setscore(adata->getscore()-MYbloodvial);
            adata->setbloodvial(adata->getbloodvial()+1);
            CCSprite *sprite=CCSprite::create("eq1.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
                sprite->setTag(700);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[0]->addChild(sprite);
            }
            else if(adata->getbloodvial()==1)
            {
                adata->setscore(adata->getscore()-MYbloodvial);
                adata->setbloodvial(adata->getbloodvial()+1);
                CCSprite *sprite=CCSprite::create("eq1_2.png");
                sprite->setScale(0.8);
                sprite->setZOrder(3);
                sprite->setTag(701);
                sprite->setAnchorPoint(ccp(0, 0));
                layer[0]->addChild(sprite);
            }
            else if(adata->getbloodvial()==2)
            {
                adata->setscore(adata->getscore()-MYbloodvial);
                adata->setbloodvial(adata->getbloodvial()+1);
                CCSprite *sprite=CCSprite::create("eq1_3.png");
                sprite->setScale(0.8);
                sprite->setZOrder(4);
                sprite->setTag(702);
                sprite->setAnchorPoint(ccp(0, 0));
                layer[0]->addChild(sprite);
            }
            else if(adata->getbloodvial()==3)
            {
                adata->setscore(adata->getscore()-MYbloodvial);
                adata->setbloodvial(adata->getbloodvial()+1);
                CCSprite *sprite=CCSprite::create("eq1_4.png");
                sprite->setScale(0.8);
                sprite->setZOrder(5);
                sprite->setTag(703);
                sprite->setAnchorPoint(ccp(0, 0));
                layer[0]->addChild(sprite);
            }
        }
            break;
        case 101:
        {
            if (adata->getscore()<MYrainbow) {
                CCMessageBox("金钱不够", "提醒");
            }
            else if (adata->getrainbow()>=1)
            {
                CCMessageBox("数量已经到上限", "提醒");
            }
            else
            {
            adata->setscore(adata->getscore()-MYrainbow);
            adata->setrainbow(adata->getrainbow()+1);
            CCSprite *sprite=CCSprite::create("eq2.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
                 sprite->setTag(705);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[1]->addChild(sprite);
            }
        }
            break;
        case 102:
        {
            if (adata->getscore()<MYhat) {
                CCMessageBox("金钱不够", "提醒");
            }
            else if (adata->gethat()>=1)
            {
                CCMessageBox("数量已经到上限", "提醒");
            }
            else
            {
            adata->setscore(adata->getscore()-MYhat);
            adata->sethat(adata->gethat()+1);
            CCSprite *sprite=CCSprite::create("eq3.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
                 sprite->setTag(706);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[2]->addChild(sprite);
            }
        }
            break;
        case 103:
        {
            if (adata->getscore()<MYshoe) {
                CCMessageBox("金钱不够", "提醒");
            }
            else if (adata->getshoe()>=1||adata->getsupershoe()>=1)
            {
                CCMessageBox("已经购买过该类装备,请先出售", "提醒");
            }
            else
            {
            adata->setscore(adata->getscore()-MYshoe);
            adata->setshoe(adata->getshoe()+1);
            CCSprite *sprite=CCSprite::create("eq4.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
                 sprite->setTag(707);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[3]->addChild(sprite);
            }
        }
            break;
        case 104:
        {
            if (adata->getscore()<MYsupershoe) {
                CCMessageBox("金钱不够", "提醒");
            }
            else if (adata->getshoe()>=1||adata->getsupershoe()>=1)
            {
                CCMessageBox("已经购买过该类装备,请先出售", "提醒");
            }
            else
            {
            adata->setscore(adata->getscore()-MYsupershoe);
            adata->setsupershoe(adata->getsupershoe()+1);
            CCSprite *sprite=CCSprite::create("eq5.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
                 sprite->setTag(708);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[3]->addChild(sprite);
            }
        }
            break;
        case 105:
        {
            if (adata->getscore()<MYarmor) {
                CCMessageBox("金钱不够", "提醒");
            }
            else if (adata->getarmor()>=1||adata->getsuperarmor()>=1)
            {
                CCMessageBox("已经购买过该类装备,请先出售", "提醒");
            }
            else
            {
            adata->setscore(adata->getscore()-MYarmor);
            adata->setarmor(adata->getarmor()+1);
            CCSprite *sprite=CCSprite::create("eq6.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
                 sprite->setTag(709);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[4]->addChild(sprite);
            }
        }
            break;
        case 106:
        {
            if (adata->getscore()<MYsuperarmor) {
                CCMessageBox("金钱不够", "提醒");
            }
            else if (adata->getarmor()>=1||adata->getsuperarmor()>=1)
            {
                CCMessageBox("已经购买过该类装备,请先出售", "提醒");
            }
            else
            {
            adata->setscore(adata->getscore()-MYsuperarmor);
            adata->setsuperarmor(adata->getsuperarmor()+1);
            CCSprite *sprite=CCSprite::create("eq7.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
            sprite->setTag(710);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[4]->addChild(sprite);
            }
        }
            break;
        case 107:
        {
            if (adata->getscore()<MYbelt) {
                CCMessageBox("金钱不够", "提醒");
            }
            else if (adata->getbelt()>=1||adata->getsuperbelt()>=1)
            {
                CCMessageBox("已经购买过该类装备,请先出售", "提醒");
            }
            else
            {
            adata->setscore(adata->getscore()-MYbelt);
            adata->setbelt(adata->getbelt()+1);
            CCSprite *sprite=CCSprite::create("eq8.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
                 sprite->setTag(711);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[5]->addChild(sprite);
            }
        }
            break;
        case 108:
        {
            if (adata->getscore()<MYsuperbelt) {
                CCMessageBox("金钱不够", "提醒");
            }
            else if (adata->getbelt()>=1||adata->getsuperbelt()>=1)
            {
                CCMessageBox("已经购买过该类装备,请先出售", "提醒");
            }
            else
            {
            adata->setscore(adata->getscore()-MYsuperbelt);
            adata->setsuperbelt(adata->getsuperbelt()+1);
            CCSprite *sprite=CCSprite::create("eq9.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
                 sprite->setTag(712);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[5]->addChild(sprite);
            }
        }
            break;
        case 200:
        {
            if (adata->getmushroom()<MYlan) {
                CCMessageBox("蘑菇不够", "提醒");
            }
            else if (adata->getlan()>=1)
            {
                CCMessageBox("数量已经到上限", "提醒");
            }
            else
            {
            adata->setmushroom(adata->getmushroom()-MYlan);
            adata->setlan(adata->getlan()+1);
            CCSprite *sprite=CCSprite::create("eq10.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
                 sprite->setTag(713);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[6]->addChild(sprite);
            }
        }
            break;
        case 201:
        {
            if (adata->getmushroom()<MYai) {
                CCMessageBox("蘑菇不够", "提醒");
            }
            else if (adata->getai()>=1)
            {
                CCMessageBox("数量已经到上限", "提醒");
            }
            else
            {
            adata->setmushroom(adata->getmushroom()-MYai);
            adata->setai(adata->getai()+1);
            CCSprite *sprite=CCSprite::create("eq11.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
                 sprite->setTag(714);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[7]->addChild(sprite);
            }
        }
            break;
        case 202:
        {
            if (adata->getmushroom()<MYsi) {
                CCMessageBox("蘑菇不够", "提醒");
            }
            else if (adata->getsi()>=1)
            {
                CCMessageBox("数量已经到上限", "提醒");
            }
            else
            {
            adata->setmushroom(adata->getmushroom()-MYsi);
            adata->setsi(adata->getsi()+1);
            CCSprite *sprite=CCSprite::create("eq12.png");
            sprite->setScale(0.8);
            sprite->setZOrder(2);
                 sprite->setTag(715);
            sprite->setAnchorPoint(ccp(0, 0));
            layer[8]->addChild(sprite);
                CCLog("%d",adata->getmushroom());
            }
        }
            break;
        default:
            break;
    }
        CCLabelTTF *label=(CCLabelTTF *)this->getChildByTag(600);
        CCLog("%p",label);
        CCString *labelstring=CCString::createWithFormat("%d",adata->getscore());
        label->setString(labelstring->getCString());
        CCLabelTTF *label2=(CCLabelTTF *)this->getChildByTag(601);
        CCString *labelstring2=CCString::createWithFormat("%d",adata->getmushroom());
        CCLog("%d",adata->getmushroom());
        label2->setString(labelstring2->getCString());
    }
}
CCScene * MyStore::scene()
{
    CCScene *scene=CCScene::create();
    CCLayer *layer=MyStore::create();
    scene->addChild(layer);
    return scene;
}