#include "Player.h"
#include "GameMechs.h"
#include "Food.h"



Player::Player(GameMechs* thisGMRef, Food* food, objPosArrayList* Bucket)
{
    mainGameMechsRef = thisGMRef;
    foodInfo = food;
    foodBucket = Bucket;
    myDir = STOP;

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'*'); //Initialize the head position 

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos); //Setting head position to the temp position created
}


Player::~Player()
{
    // delete heap members here
    delete mainGameMechsRef;
    delete playerPosList;
    delete foodInfo;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    
    switch(mainGameMechsRef->getInput()) //checks the input and switches the direction based on the input
    {
            case 'w':
                if(myDir != DOWN)
                {
                    myDir = UP;
                }
                break;

            case 's':
                if(myDir != UP)
                {
                    myDir = DOWN;
                }
                break;

            case 'a':
                if(myDir != RIGHT)
                {
                    myDir = LEFT;
                }
                break;

            case 'd':
                if(myDir != LEFT)
                {
                    myDir = RIGHT;
                }
                break;
                
            case ' ':
                mainGameMechsRef->setExitTrue();
                break;

            default:
                break;
    } 
}

void Player::movePlayer()
{
    //objPos newHead;
    objPos currentHead; // holding position info of the current head
    playerPosList->getHeadElement(currentHead);

    switch(myDir) //Move the snake based on the direction
    {
        case UP:
            if(currentHead.y == 1)
            {
                currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
                break;
            }
            currentHead.y--;
            break;

        case DOWN:
            if(currentHead.y == mainGameMechsRef->getBoardSizeY() - 2)
            {
                currentHead.y = 1;
                break;
            }
            currentHead.y++;
            break;

        case RIGHT:
            if(currentHead.x == mainGameMechsRef->getBoardSizeX() - 2)
            {
                currentHead.x = 1;
                break;
            }
            currentHead.x++;
            break;

        case LEFT:
            if(currentHead.x == 1)
            {
                currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
                break;
            }
            currentHead.x--;
            break;
        case STOP:
        default:
            break;
    }
    if(checkFoodConsumptionNormal()) //if normal food is consumed 
    {
        playerPosList->insertHead(currentHead); //increase the player 
        foodBucket->resetSize(); //reset the food bucket for new food
        foodInfo->generateFood(playerPosList, foodBucket); //Generate new food
        mainGameMechsRef->incrementScore(); //Increment the score 
    }
    else if(checkFoodConsumptionSpecial()) //if special food is consumed
    {
        playerPosList->insertHead(currentHead); //dont increase the player length
        playerPosList->removeTail();
        foodBucket->resetSize(); //reset food bucket for new food
        foodInfo->generateFood(playerPosList, foodBucket); //Generate new food
        for (int i = 0; i < 5; i ++)
        {
            mainGameMechsRef->incrementScore(); //Increment the score by 5
        }
    }
    else
    {
        playerPosList->insertHead(currentHead); //otherwise use regular moving algorithm
        playerPosList->removeTail();
    }
}

bool Player::checkFoodConsumptionNormal() //check normal food consumption
{
    objPos tempHeadPos;
    objPos tempFood;
    for(int i = 0; i < foodBucket->getSize(); i++) //Go through the food bucket and check if the head location is equal to the location of a 'o'
    {
        playerPosList->getHeadElement(tempHeadPos);
        foodBucket->getElement(tempFood, i);
        if(tempHeadPos.x == tempFood.x && tempHeadPos.y == tempFood.y)
        {
            if(tempFood.symbol == 'o')
            {
                return true;
            }
        }
    }
    return false;
}
bool Player::checkFoodConsumptionSpecial()
{
    objPos tempHeadPos;
    objPos tempFood;
    for(int i = 0; i < foodBucket->getSize(); i++)//Go through the food bucket and check if the head location is equal to the location of a 'x'
    {
        playerPosList->getHeadElement(tempHeadPos);
        foodBucket->getElement(tempFood, i);
        if(tempHeadPos.x == tempFood.x && tempHeadPos.y == tempFood.y)
        {
            if(tempFood.symbol == 'x')
            {
                return true;
            }
        }
    }
    return false;
}
bool Player::checkSelfCollision() //check if you run into yourself
{
    objPos tempHeadPos;
    playerPosList->getHeadElement(tempHeadPos);

    objPos tempPlayerElement;

    for(int i = 1; i < playerPosList->getSize(); i++) //Check if the head position is equal to any of the body positions 
    {
        playerPosList->getElement(tempPlayerElement, i);
        if(tempHeadPos.x == tempPlayerElement.x && tempHeadPos.y == tempPlayerElement.y)
        {
            return true;
        }
    }return false;

}
        