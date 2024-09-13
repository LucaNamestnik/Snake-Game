#include "MacUILib.h"
#include "objPos.h"
#include "Food.h"
#include <cstdlib>
#include <time.h>



Food::Food(GameMechs* gameMechs)
{
    foodPos.setObjPos(-1, -1, 'o'); //initialize food position outside of game board
    mechInfo = gameMechs;
}

Food::~Food()
{
    delete mechInfo;
}
void Food::generateFood(objPosArrayList* blockOff, objPosArrayList* foodBucket)//generate random x and y coords and make sure they are not border or blockoff pos and puts then in the food bin.
{

    int count = 0;

    objPos randomPos;
    objPos tempBody;
    objPos tempFood;

    randomPos = objPos();
    while(count < 4) //Gets 4 food elements
    {
        randomPos.x = rand() % (mechInfo->getBoardSizeX() - 2) + 1; //Generates random x and y using the symbol 'o'
        randomPos.y = rand() % (mechInfo->getBoardSizeY() - 2) + 1;
        randomPos.symbol = 'o';
        bool validPos = true;

        for(int i = 0; i < blockOff->getSize(); i++)//to check each element of the current snake
        {
            blockOff->getElement(tempBody, i); //go to the element
            if(randomPos.x == tempBody.x && randomPos.y == tempBody.y)
            {
                validPos = false;
                break;
            }
        }
        for(int j = 0; j < foodBucket->getSize(); j++)//to check each element of the already spawned food
        {
            foodBucket->getElement(tempFood, j);
            if (randomPos.x == tempFood.x && randomPos.y == tempFood.y)//check if the elements position is equal to the random position
            {
                validPos = false;
                break;
            }
        }
        if(validPos) //If vaild position instert into food bin
        {
            foodBucket->insertTail(randomPos);
            count++;
        }
    }
    while(count > 3 && count < 5) //Gets 1 special food
    {
        randomPos.x = rand() % (mechInfo->getBoardSizeX() - 2) + 1; //Generates random x and y using the symbol 'x'
        randomPos.y = rand() % (mechInfo->getBoardSizeY() - 2) + 1;
        randomPos.symbol = 'x';
        bool validPos = true;

        for(int i = 0; i < blockOff->getSize(); i++)//to check each element of the current snake
        {
            blockOff->getElement(tempBody, i); //go to the element
            if(randomPos.x == tempBody.x && randomPos.y == tempBody.y)
            {
                validPos = false;
                break;
            }
        }
        for(int j = 0; j < foodBucket->getSize(); j++)//to check each element of the already spawned food
        {
            foodBucket->getElement(tempFood, j); //go to position
            if (randomPos.x == tempFood.x && randomPos.y == tempFood.y)//check if the elements position is equal to the random position
            {
                validPos = false;
                break;
            }
        }
        if(validPos) //If vaild position instert into food bin
        {
            foodBucket->insertTail(randomPos);
            count++;
        }
    }
}
             
void Food::getfoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);;
}