  #include "GameMechs.h"
  #include "MacUILib.h"

#include "objPosArrayList.h"

 //think aboutn where to seed the rmg
//objPos* randpos;

GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    loseFlag = false;
    exitFlag = false;
    boardSizeX = 30;
    boardSizeY = 15;

    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    loseFlag = false;
    exitFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;

    foodPos.setObjPos(-1, -1, 'f');
}

// do you need a destructor?


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus(){
    return loseFlag;
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag(){
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore(){
    return score;

}

void GameMechs::incrementScore(){
    score++;
}

