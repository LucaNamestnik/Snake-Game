#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        
        int boardSizeX;
        int boardSizeY;

        objPos foodPos;
        bool loseFlag;
        int score;

    public:
        objPos* randpos;
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus();
        bool getLoseFlagStatus();
        void setLoseFlag();
        void setExitTrue();

        char getInput();
        void setInput(char thisInput);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();
        
        int getScore();
        void incrementScore();
        
        void generateFood(objPos blockOff); ///need to upgrade this somehow...
        void getfoodPos(objPos &returnPos);

};

#endif