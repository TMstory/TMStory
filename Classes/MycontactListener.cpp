//
//  MycontactListener.cpp
//  Box2DDemo
//
//  Created by neworigin on 14-11-20.
//
//

#include "MycontactListener.h"
bool yes = false;
using namespace std;
void MycontactListener::BeginContact(b2Contact* contact)
{

    //cout<<__FUNCTION__<<endl;
b2Body * bodyB = contact->GetFixtureB()->GetBody();
    if (bodyB->GetLinearVelocity().y<0) {
        yes = true;
    }
    
}

void MycontactListener::EndContact(b2Contact* contact)
{
    // cout<<__FUNCTION__<<endl;
}
void MycontactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
     //cout<<__FUNCTION__<<endl;
}
void MycontactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
   //  cout<<__FUNCTION__<<endl;
    //float force = impulse->normalImpulses[0];
    
  //  CCLOG("%f %f %f %f %d",impulse->normalImpulses[0],impulse->normalImpulses[1],impulse->tangentImpulses[0],impulse->tangentImpulses[1],impulse->count);
//    b2Body * bodyA = contact->GetFixtureA()->GetBody();
//    b2Body * bodyB = contact->GetFixtureB()->GetBody();
    //        CCLog("%f %f %f %f",bodyA->GetLinearVelocity().x,bodyA->GetLinearVelocity().y,bodyB->GetLinearVelocity().x,bodyB->GetLinearVelocity().y);
    if (impulse->count>1 && impulse->normalImpulses[0]>0) {
        if (yes) {
            Data * datazhi = Data::creat();
            datazhi->setCrash(true);
            yes = false;
        }
    }

}
