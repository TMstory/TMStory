//
//  MyStore.h
//  TmStory2
//
//  Created by neworigin on 14-12-12.
//
//

#ifndef __TmStory2__MyStore__
#define __TmStory2__MyStore__

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class MyStore :public CCLayer, public CCScrollViewDelegate
{
public:
    virtual bool init();
    static CCScene *scene();
    CREATE_FUNC(MyStore);
public:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
private:
    CCScrollView *scrollview;
    CCPoint point;
public:
    void readlist();
    void addmenu();
    void addscrollview(CCControlButton *button);
    void buyequip(CCControlButton *button);
    void sellequip(CCMenuItemImage *item);
    void changemove();
    void back();
};
#endif /* defined(__TmStory2__MyStore__) */
