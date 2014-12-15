//
//  Data.h
//  GoldMiner
//
//  Created by neworigin on 14-11-12.
//
//

#ifndef __GoldMiner__Data__
#define __GoldMiner__Data__

#include <stdio.h>
#include <iostream>
using namespace std;
class Data{
public:
   
    ~Data();
    static Data * creat();
    bool getCrash();
    void setCrash(bool);
private:
    Data();
    bool crash;
public:
    int wskill;//w技能
private:
    int bloodvial;//血瓶
    int rainbow;//幻影之舞
    int hat;//帽子
    int shoe;//速度之靴
    int supershoe;//轻灵之靴
    int armor;//锁子甲
    int superarmor;//荆棘之甲
    int belt;//腰带
    int superbelt;//狂徒
    int lan;//兰博
    int ai;//艾希
    int si;//死歌
    int score;//分数
    int mushroom;//蘑菇
public:
    void setbloodvial(int a);
    void setrainbow(int a);
    void sethat(int a);
    void setshoe(int a);
    void setsupershoe(int a);
    void setarmor(int a);
    void setsuperarmor(int a);
    void setbelt(int a);
    void setsuperbelt(int a);
    void setlan(int a);
    void setai(int a);
    void setsi(int a);
    void setscore(int a);
    void setmushroom(int a);
    int getbloodvial();
    int getrainbow();
    int gethat();
    int getshoe();
    int getsupershoe();
    int getarmor();
    int getsuperarmor();
    int getbelt();
    int getsuperbelt();
    int getlan();
    int getai();
    int getsi();
    int getscore();
    int getmushroom();
};

#endif /* defined(__GoldMiner__Data__) */
