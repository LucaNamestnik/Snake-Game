
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

#ifndef FOOD_H
#define FOOD_H

class Food
{
    private:
        objPos foodPos;
        GameMechs* mechInfo;
        objPosArrayList* playerBody;
        objPosArrayList* foodBucket;
    public:

        Food(GameMechs* gameMechs);
        ~Food();

        void generateFood(objPosArrayList* blockOff, objPosArrayList* Bucket);
        void getfoodPos(objPos &returnPos);
};


#endif