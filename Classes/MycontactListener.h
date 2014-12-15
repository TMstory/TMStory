//
//  MycontactListener.h
//  Box2DDemo
//
//  Created by neworigin on 14-11-20.
//
//

#ifndef __Box2DDemo__MycontactListener__
#define __Box2DDemo__MycontactListener__

#include <iostream>
#include "Box2D/Box2D.h"
#include "Data.h"
#include "cocos2d.h"
USING_NS_CC;
class MycontactListener : public b2ContactListener
{
    
    virtual void BeginContact(b2Contact* contact);
    
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
};
#endif /* defined(__Box2DDemo__MycontactListener__) */
