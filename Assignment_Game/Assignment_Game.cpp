// Assignment_Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <process.h>
#include "conio.h"

#include "Snake.h"
#include "Food.h"

#include<iostream>

void InitWorld();
void DrawSnake(bool bDraw = true);
void DrawFood();
void DrawSuperFood();
bool UpdateWorld();
void UpdateSnake();
int UpdateScore(int Score);
void RenderWorld();
bool IsBendHit(int xPos, int yPos, std::list<Bend>::iterator iter);
bool CheckWallHit();
bool CheckBodyHit();
void GameOverDisplay();
void LoadScore();

void gotoxy(int x, int y);

const int speedUp = 3;
const int superFoodInstance = 5;
#define snakeStartPos 6,12,1

char memory[80][25] = { ' ' };
char currDisplay[80][25] = { ' ' };
int Score = 0;
int Speed = 150;
int foodPoint;
int superFoodCtr;
Snake* theSnake = NULL;
Food* theFood = NULL;
Food* theSuperFood = NULL;

int _tmain(int argc, _TCHAR* argv[])
{
	bool gameIsNotOver = true;
	
	while (gameIsNotOver)
	{
		InitWorld();					//loads characters for world
		while (true)					//checks key input while running
		{
			if (_kbhit() != 0)
			{
				switch (_getch())
				{
				case 27:
					return false;
				case 119:
					theSnake->moveUp();
					break;
				case 115:
					theSnake->moveDown();
					break;
				case 97:
					theSnake->moveLeft();
					break;
				case 100:
					theSnake->moveRight();
					break;
				case 224:
					switch (_getch())
					{
					case 72:
						theSnake->moveUp();
						break;
					case 80:
						theSnake->moveDown();
						break;
					case 75:
						theSnake->moveLeft();
						break;
					default:
						theSnake->moveRight();
					}
					break;
				default:
					break;
				}
			}

			if (!UpdateWorld())
			{
				break;
			}
			RenderWorld();		//displays world
			gotoxy(0, 0);		//location of cursor while game running
			Sleep(Speed);
		}
		GameOverDisplay();
		while (true)
		{
			if (_kbhit() != 0)
			{
				int keyPress = _getch();
				if (keyPress == 110)	//N
				{
					return false;
				}
				else if (keyPress == 78)	//n
				{
					return false;
				}
				else if (keyPress == 27)
				{
					return false;
				}
				else if (keyPress == 89)	//y
				{
					system("cls");
					break;
				}
				else if (keyPress == 121)	//Y
				{
					system("cls");
					break;
				}
			}
		}
	}
	//deletes created objects
	delete theSnake;
	delete theFood;
	delete theSuperFood;

	getchar();
	return 0;
}

void LoadScore()
{

}
void InitWorld()
{
	int x, y;

	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			memory[x][y] = ' ';
			currDisplay[x][y] = ' ';
		}
	}

	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			if (y == 2)
			{
				if (x == 0)
					memory[x][y] = 218; //┌
				else if (x == 79)
					memory[x][y] = 191;	//┐
				else
					memory[x][y] = 196;	//─
			}
			else if (y == 24)
			{
				if (x == 0)
					memory[x][y] = 192;	//└
				else if (x == 79)
					memory[x][y] = 217; //┘
				else
					memory[x][y] = 196;	//─
			}
			else if (x == 0 || x == 79)
				if (y>2)
					memory[x][y] = 179;	//│
		}
	}

	theSnake = new Snake(snakeStartPos);		//create theSnake
	theFood = new Food(1, 78, 3, 23);	//creat theFood
	
	//initial draw
	DrawSnake();
	DrawFood();
} 

bool IsBendHit(int xPos, int yPos, std::list<Bend>::iterator iter)
{
	if (iter == theSnake->vecBends.end()) return false;		//if bend ends return false
	return xPos == iter->xPos && yPos == iter->yPos;	//equates cordinates to current position
}

void DrawSnake(bool bDraw)
{
	char charToDraw;

	std::list<Bend>::iterator bendToCheck = theSnake->vecBends.begin();		//iteration grants access to list; creats variable for what to print

	int lastDir = theSnake->headDirection;	//sets lastDir as the CURRENT direction of the snake
	int snakeLength = theSnake->length;
	int x = theSnake->headXPos, y = theSnake->headYPos;

	do	//loop atleast once snake moves when game renders
	{
		switch (lastDir)
		{
		case 0:		//when direction is UP
			if (IsBendHit(x, y, bendToCheck))	
			{
				if (bendToCheck->dir == 1)
				{
					charToDraw = 200;	//╚
					lastDir = 3;
				}
				else
				{
					charToDraw = 188;	//╝
					lastDir = 1;
				}
				bendToCheck++;
				break;
			}
			charToDraw = 186;	//║
			break;

		case 2:
			if (IsBendHit(x, y, bendToCheck))
			{
				if (bendToCheck->dir == 3)
				{
					charToDraw = 187;	//╗
					lastDir = 1;
				}
				else
				{
					charToDraw = 201;	//╥
					lastDir = 3;
				}
				bendToCheck++;
				break;
			}
			charToDraw = 186;	//║
			break;
		case 1:
			if (IsBendHit(x, y, bendToCheck))
			{
				if (bendToCheck->dir == 0)
				{
					charToDraw = 200;	//╚
					lastDir = 2;
				}
				else
				{
					charToDraw = 201;	//╔
					lastDir = 0;
				}
				bendToCheck++;
				break;
			}
			charToDraw = 205;	//═
			break;
		case 3:
			if (IsBendHit(x, y, bendToCheck))
			{
				if (bendToCheck->dir == 0)
				{
					charToDraw = 188;	//╝
					lastDir = 2;
				}
				else
				{
					charToDraw = 187;	//╗
					lastDir = 0;
				}
				bendToCheck++;
				break;
			}
			charToDraw = 205;	//═
			break;
		}

		if (bDraw == false)
		{
			if (snakeLength == 1)
				memory[x][y] = ' ';
		}
		else
		{
			memory[x][y] = charToDraw;
		}

		switch (lastDir)
		{
		case 0:
			y++;
			break;
		case 1:
			x--;
			break;
		case 2:
			y--;
			break;
		case 3:
			x++;
			break;
		}

		snakeLength--;
	} while (snakeLength > 0);
}

void DrawFood()
{
	//randomize while location not empty
	while (memory[theFood->foodXPos][theFood->foodYPos] != ' ')
	{
		theFood->RandomizeFood();
	}

	memory[theFood->foodXPos][theFood->foodYPos] = 248;		//°
}

void DrawSuperFood()
{
	while (memory[theSuperFood->foodXPos][theSuperFood->foodYPos] != ' ')
	{
		theSuperFood->RandomizeFood();
	}
	
	memory[theSuperFood->foodXPos][theSuperFood->foodYPos] = 'O';
}

bool UpdateWorld()
{

	UpdateScore(Score);
	UpdateSnake();
	if (CheckWallHit() || CheckBodyHit())
		return false;
	
	//check if snake hits food
	if ((theSnake->headXPos == theFood->foodXPos) && (theSnake->headYPos == theFood->foodYPos))
	{		
		DrawFood();
		theSnake->length++;
		UpdateScore(Score++);
		superFoodCtr++;
		if (Speed >= 50)
		{
			Speed -= speedUp;
		}
	}

	if (superFoodCtr == superFoodInstance)
	{
		foodPoint = 50;
		theSuperFood = new Food(1, 79, 4, 23);	//theSuperFood only recieves ADDRESS; new creates SPACE for FOOD which returns the ADDRESS of FOOD
		DrawSuperFood();
		foodPoint = 100;
		superFoodCtr++;
	}
	
	if (theSuperFood != NULL)	//while super food is existing do not generate NEW superfood
	{
		if ((theSnake->headXPos == theSuperFood->foodXPos) && (theSnake->headYPos == theSuperFood->foodYPos))
		{
			theSnake->length++;
			Score += (foodPoint/10);
			superFoodCtr = 0;
			delete theSuperFood;
			theSuperFood = NULL;
			if (Speed >= 50)
			{
				Speed -= speedUp;
			}
		}
		else if (foodPoint == 0)
		{
			memory[theSuperFood->foodXPos][theSuperFood->foodYPos] = ' ';
			superFoodCtr = 0;
			delete theSuperFood;
			theSuperFood = NULL;
		}
	}

	if (foodPoint > 0)
		foodPoint--;

	DrawSnake();
	return true;
}

void UpdateSnake()
{
	DrawSnake(false);					//Erases snake's trail
	switch (theSnake->headDirection)
	{
	case 0:
		theSnake->headYPos--;
		break;
	case 1:
		theSnake->headXPos++;
		break;
	case 2:
		theSnake->headYPos++;
		break;
	case 3:
		theSnake->headXPos--;
		break;
	}

}

int UpdateScore(int Score)
{
	gotoxy(8, 1);
	printf("%d", Score);
	return Score;
}

bool CheckWallHit()
{
	unsigned char charToCheck = memory[theSnake->headXPos][theSnake->headYPos];
	switch (charToCheck)
	{
	case 196:	//─
	case 179:	//│
		return true;
		break;
	}
	return false;
}

bool CheckBodyHit()
{
	unsigned char charToCheck = memory[theSnake->headXPos][theSnake->headYPos];
	switch (charToCheck)
	{
	case 200:	//╚
	case 201:	//╔
	case 188:	//╝
	case 187:	//╗
	case 186:	//║
	case 205:	//═
		return true;
		break;
	}
	return false;
}

void RenderWorld()
{
	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			if (currDisplay[x][y] != memory[x][y])
			{
				gotoxy(x, y);
				currDisplay[x][y] = memory[x][y];

				printf("%c", currDisplay[x][y]);
			}
		}
	}

	gotoxy(1, 1);
	printf("Score: ");
}

void GameOverDisplay(){
	int x, y;

	for (y = 3; y < 24; y++)
	{
		for (x = 1; x < 79; x++)
		{
			gotoxy(x, y);
			printf(" ");
		}
	}
	gotoxy(31, 11);
	printf("Game Over [Y/N]?");
}

void gotoxy(int x, int y){
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;

	//cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}