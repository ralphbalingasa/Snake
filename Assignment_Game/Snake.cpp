#include "stdafx.h"
#include "Snake.h"


Snake::Snake(int xPos, int yPos, int dir)
{
	headXPos = xPos;
	headYPos = yPos;
	headDirection = dir;
	length = 5;
	vecBends.clear();
}


Snake::~Snake()
{
}

void Snake::moveUp()
{
	if ((headDirection != 1) && (headDirection != 3))	//move up only if not LEFT or RIGHT
		return;

	Bend newBend;
	newBend.xPos = headXPos;
	newBend.yPos = headYPos;
	if (headDirection == 1)	//if direction is RIGHT moving UP bend going LEFT
		newBend.dir = 3;
	else if (headDirection == 3)	//if direction is LEFT moving UP bend going right
		newBend.dir = 1;

	vecBends.push_front(newBend); //record new bend

	headDirection = 0; //direction is now UP
}

void Snake::moveDown()
{
	if ((headDirection != 1) && (headDirection != 3))
		return;

	Bend newBend;
	newBend.xPos = headXPos;
	newBend.yPos = headYPos;
	if (headDirection == 1)
		newBend.dir = 3;
	else if (headDirection == 3)
		newBend.dir = 1;

	vecBends.push_front(newBend);

	headDirection = 2;
}


void Snake::moveRight()
{
	if ((headDirection != 0) && (headDirection != 2))
		return;

	Bend newBend;
	newBend.xPos = headXPos;
	newBend.yPos = headYPos;
	if (headDirection == 0)
		newBend.dir = 2;
	else if (headDirection == 2)
		newBend.dir = 0;
	
	vecBends.push_front(newBend);

	headDirection = 1;
}

void Snake::moveLeft()
{
	if ((headDirection != 0) && (headDirection != 2))
		return;

	Bend newBend;
	newBend.xPos = headXPos;
	newBend.yPos = headYPos;
	if (headDirection == 0)
		newBend.dir = 2;
	else if (headDirection == 2)
		newBend.dir = 0;

	vecBends.push_front(newBend);

	headDirection = 3;
}