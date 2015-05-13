#pragma once
#include <list>

struct Bend
{
	int xPos;
	int yPos;
	int dir;
};

class Snake
{
public:
	Snake(int xPos, int yPos, int dir);
	~Snake();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	int length;
	int headXPos;
	int headYPos;
	int headDirection;

	std::list<Bend> vecBends;
};