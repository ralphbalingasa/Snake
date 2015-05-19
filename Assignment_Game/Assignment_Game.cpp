// Assignment_Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <map>
#include <string>
#include "Snake.h"
#include "Food.h"
#include <iostream>

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
std::string GetHighScorerName();
void UpdateHighScore();
void PrintScore();
void GameOverDisplay();
void ClearDisplay();
void gotoxy(int x, int y);

const int speedUp = 3;
const int superFoodInstance = 5;
#define snakeStartPos 6,12,1	//(x,y,direction)

char memory[80][25] = { ' ' };
char currDisplay[80][25] = { ' ' };
int Score = 0;
int scoreYPos = 7;
int Speed = 150;
int foodPoint;
int superFoodCtr;
std::multimap <int, std::string> highScore;
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
	DrawSnake(true);
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
		superFoodCtr++;
	}
	
	if (theSuperFood != NULL)	//while super food is existing do not generate NEW superfood
	{
		gotoxy(69, 1);
		printf("          ");	//delete timer
		gotoxy(69, 1);
		printf("Timer: %d",foodPoint);
		if ((theSnake->headXPos == theSuperFood->foodXPos) && (theSnake->headYPos == theSuperFood->foodYPos))
		{
			theSnake->length++;
			Score += (foodPoint/10);
			gotoxy(68, 1);
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
			gotoxy(68, 1);
			superFoodCtr = 0;
			delete theSuperFood;
			theSuperFood = NULL;
		}

		//delete the timer
		if (theSuperFood == NULL)
		{
			gotoxy(69, 1);
			printf("          ");
		}

		if (foodPoint > 0)
			foodPoint--;
	}

	DrawSnake(true);
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

void LoadScore()
{

}

void UpdateHighScore()
{
	//record Score
	if (Score > 0)
	{
		if (highScore.size() < 10){	// change back to 10
			highScore.insert(std::make_pair(Score, GetHighScorerName()));
		}
		else if (highScore.size() == 10){	//change back to 10
			std::multimap <int, std::string>::iterator iter = highScore.begin();
			if (Score > iter->first)
			{
				highScore.erase(iter);
				highScore.insert(std::make_pair(Score, GetHighScorerName()));
			}
		}
	}

	//print Score
	for (std::multimap<int, std::string>::reverse_iterator r_iter = highScore.rbegin(); r_iter != highScore.rend(); r_iter++)
	{
		gotoxy(31, scoreYPos);// coordinates of high score
		printf("%d.) %s\t%d", scoreYPos - 6, r_iter->second.c_str(), r_iter->first);
		scoreYPos++;
	}

	scoreYPos = 8;
}

std::string GetHighScorerName(){
	std::string name;
	int letter;
	int eraseX = 45;

	RenderWorld();
	gotoxy(35, 5);
	printf("HIGH SCORE!!!");
	gotoxy(33, 10);
	printf("Input Name: ");
	while (true)
	{
		letter = _getch();
		if (letter == 13)
			break;
		if (letter >= 65 && letter <= 90)	//all caps
		{
			name.append((const char*)&letter);
			printf("%c", letter);
			eraseX++;
		}
		else if (letter >= 97 && letter <= 122)	//small caps
		{
			name.append((const char*)&letter);
			printf("%c", letter);
			eraseX++;
		}
		else if (letter == 8)	//backspace
		{
			if (eraseX > 45)
			{
				gotoxy(eraseX-1, 10);
				printf(" ");
				eraseX--;
				name.resize(name.size() - 1);
				gotoxy(eraseX, 10);
			}
		}
		else if (letter == 224)	//for arrow keys filter
			_getch();
	}

	ClearDisplay();
	return name;
}

void GameOverDisplay(){
	//reset
	foodPoint = 0;
	superFoodCtr = 0;
	scoreYPos = 7;
	Speed = 150;

	ClearDisplay();
	UpdateHighScore();
	gotoxy(34, 4);
	printf("Game Over?");
	gotoxy(31, 5);
	printf("Continue [Y/N]?");
	Score = 0;
}

void ClearDisplay(){
	int x, y;

	for (y = 3; y < 24; y++)
	{
		for (x = 1; x < 79; x++)
		{
			gotoxy(x, y);
			printf(" ");
		}
	}
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