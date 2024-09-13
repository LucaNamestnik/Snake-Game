#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000


//Declaring global variables / pointers
GameMechs* myGM;
Player* myPlayer;
Food* foodPos;
objPos playerPos;
objPosArrayList* playerBody;
objPosArrayList* foodBucket;




void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  //Check to see if the exit flag is triggered
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //Allocating memory on the heap for the pointers
    myGM = new GameMechs(30, 15); //makes board size 30 and 15 
    foodBucket = new objPosArrayList(); //Creates an array list for the food bucket
    foodPos = new Food(myGM); //Creates a food position
    myPlayer = new Player(myGM, foodPos, foodBucket); //Creates a pointer that controls the snake

    playerBody = myPlayer->getPlayerPos(); //Gets the starting position of the snake body
    foodPos->generateFood(playerBody, foodBucket); //Generates food
}

void GetInput(void)
{
    if (MacUILib_hasChar()){
        myGM->setInput(MacUILib_getChar()); //Gets input from user
    }
    
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir(); //Sets player direction
    if(myPlayer->checkSelfCollision()) //Checks if there is a self collision
    {
        myGM->setLoseFlag();
    }else
    {
        myPlayer->movePlayer(); //moves player and clears input
        myGM->clearInput();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); //Clears screen

    bool drawn;
    bool food;

    objPos tempBody;
    objPos tempF;

    for(int y = 0; y <= myGM->getBoardSizeY() - 1; y++) //Loop running through the y values of the board
    {
        for(int x = 0; x <= myGM->getBoardSizeX() - 1; x++) //Loop running through the x values of the board
        {
            drawn = false;
            food = true;

            for(int k = 0; k < playerBody->getSize(); k++) //Loop checking each element in the snake list and printing it
            {
                playerBody->getElement(tempBody, k); //Getting the snake body element at index k

                if(tempBody.x == x && tempBody.y == y) //Checking if it equals the position on the board it is printing
                {
                    MacUILib_printf("%c", tempBody.symbol); //Print the snake symbol
                    drawn = true;
                    break;
                }
            }
            if(drawn) continue; //if player body was drawn do not draw anything below

            for(int i = 0; i < foodBucket->getSize(); i++) //Loop checking each element in the food bin
            {
                foodBucket->getElement(tempF, i); //Gets the food element at each index

                if (x == tempF.x && y == tempF.y) //Checking if it equals the position on the board it is printing
                {
                    MacUILib_printf("%c", tempF.symbol); //Print the food symbol
                    food = false;
                }
            }
            if(food) //if food is drawn do not draw anything else
            {
                if(y == 0 || y == myGM->getBoardSizeY() - 1) //Prints a # at the boarder
                {
                    MacUILib_printf("%c", '#');
                }
                else if(x == 0 || x == myGM->getBoardSizeX() - 1) //Prints a # at the boarder
                {
                    MacUILib_printf("%c", '#');
                }
                else
                {
                    MacUILib_printf("%c", ' '); //Prints a space everywhere else
                }
            }
        }
        MacUILib_printf("%c",'\n');
    }    
    
    MacUILib_printf("Score: %d\n", myGM->getScore()); //Print the score

    MacUILib_printf("Collect an X: Add 5 to Score, 0 to Length\n"); //Food rules
    MacUILib_printf("Collect an o: Add 1 to Score, 1 to Length\n");

    if(myGM->getLoseFlagStatus()) //If loseflag is true exit the program
    {
        MacUILib_printf("You ate yourself: GAME OVER");
    }
    else if(myGM->getExitFlagStatus()) //If exitflag is true exit the program
    {
        MacUILib_printf("You have exited the game");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  
    
    //Delete memory allocated on the heap
    delete myGM;
    delete myPlayer;
    delete foodPos;
    delete playerBody;
    delete foodBucket;

    MacUILib_uninit();
}
