#pragma once

class Food
{
public:
	Food(int xMin, int xMax, int yMin, int yMax);
	~Food();

	void RandomizeFood();
	//limits
	int m_xMin;
	int m_xMax;
	int m_yMin;
	int m_yMax;

	int foodXPos;
	int foodYPos;
};