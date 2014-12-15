//
//  Data.cpp
//  GoldMiner
//
//  Created by neworigin on 14-11-12.
//
//

#include "Data.h"

static Data * data = NULL;
Data::Data()
{
    wskill = 40;
    bloodvial=0;//血瓶
    rainbow=0;//幻影之舞
    hat=0;//帽子
    shoe=0;//速度之靴
    supershoe=0;//轻灵之靴
    armor=0;//锁子甲
    superarmor=0;//荆棘之甲
    belt=0;//腰带
    superbelt=0;
    lan=0;
    ai=0;
    si=0;
    score=30000;
    mushroom=300;
}
Data * Data::creat()
{
    if (!data) {
        data = new Data();
        return data;
    }
    else{
        return data;
    }
}
bool Data::getCrash()
{
    return crash;
}
void Data::setCrash(bool yes)
{
    crash = yes;
}
void Data::setbloodvial(int a)
{
    bloodvial=a;
}
void Data::setrainbow(int a)
{
    rainbow=a;
}
void Data::sethat(int a)
{
    hat=a;
}
void Data::setshoe(int a)
{
    shoe=a;
}
void Data::setsupershoe(int a)
{
    supershoe=a;
}
void Data::setarmor(int a)
{
    armor=a;
}
void Data::setsuperarmor(int a)
{
    superarmor=a;
}
void Data::setbelt(int a)
{
    belt=a;
}
void Data::setsuperbelt(int a)
{
    superbelt=a;
}
void Data::setlan(int a)
{
    lan=a;
}
void Data::setai(int a)
{
    ai=a;
}
void Data::setsi(int a)
{
    si=a;
}
int Data::getbloodvial()
{
    return bloodvial;
}
int Data::getrainbow()
{
    return rainbow;
}
int Data::gethat()
{
    return hat;
}
int Data::getshoe()
{
    return shoe;
}
int Data::getsupershoe()
{
    return supershoe;
}
int Data::getarmor()
{
    return armor;
}
int Data::getsuperarmor()
{
    return superarmor;
}
int Data::getbelt()
{
    return belt;
}
int Data::getsuperbelt()
{
    return superbelt;
}
int Data::getlan()
{
    return lan;
}
int Data::getai()
{
    return ai;
}
int Data::getsi()
{
    return si;
}
void Data::setscore(int a)
{
    score=a;
}
void Data::setmushroom(int a)
{
    mushroom=a;
}
int Data::getscore()
{
    return score;
}
int Data::getmushroom()
{
    return mushroom;
}

