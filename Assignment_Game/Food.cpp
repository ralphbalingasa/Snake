#include "stdafx.h"
#include "Food.h"

#include <ctime>
#include <stdlib.h>

Food::Food(int xMin, int xMax, int yMin, int yMax)
{
	m_xMin = xMin;
	m_xMax = xMax;
	m_yMin = yMin;
	m_yMax = yMax;

	//seed randomizer
	srand(time(0));
	RandomizeFood();
}

void Food::RandomizeFood()			//randomizes the location of ANY food object
{
	foodXPos = (rand() % (m_xMax - m_xMin + 1)) + m_xMin;
	foodYPos = (rand() % (m_yMax - m_yMin + 1)) + m_yMin;
}

Food::~Food()
{
}