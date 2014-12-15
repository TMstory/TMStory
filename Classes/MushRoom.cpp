//
//  MushRoom.cpp
//  TmStory2
//
//  Created by neworigin on 14-12-14.
//
//

#include "MushRoom.h"
MushRoom::MushRoom()
{
    PH = 10;
}
void MushRoom::setPH(float ph)
{
    PH = ph;
}
float MushRoom::getPH()
{
    return PH;
}