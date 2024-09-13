#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {STOP, DOWN, LEFT, RIGHT, UP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* food, objPosArrayList* Bucket);
        ~Player();

        objPosArrayList* getPlayerPos();
        void updatePlayerDir();
        void movePlayer();
        bool checkFoodConsumptionNormal();
        bool checkFoodConsumptionSpecial();
        bool checkSelfCollision();
        
        
    private:
        objPosArrayList* playerPosList;
        objPosArrayList* foodBucket;
        enum Dir myDir;
        Food* foodInfo;
        
        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif