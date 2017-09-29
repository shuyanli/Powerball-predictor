#include "HistoryNum.h"

//using namespace std;

/*
place to store the history winning numbers
*/

HistoryNum::HistoryNum(void)
{

}

HistoryNum::HistoryNum(int whitenum[5], int rednum, std::string str)			//initialize all balls
{
	for (int i = 0; i < 5; i++)
	{
		whiteball[i] = Ball(0, whitenum[i]);
	}
	powerball = Ball(1, rednum);
	drawdate = str;
}


HistoryNum::~HistoryNum(void)
{
}

std::string HistoryNum::getdate(void)
{
	return drawdate;
}

Ball HistoryNum::getwhiteball(int i)
{
	if (i >= 5)
	{
		return whiteball[4];
	}
	return whiteball[i];
}

Ball HistoryNum::getpowerball(void)
{
	return powerball;
}

void HistoryNum::setWhiteBall(int num, int i)
{
	if (i < 5)
		whiteball[i].setNumber(num);
}

void HistoryNum::setPowerBall(int num)
{
	powerball.setNumber(num);

}


int HistoryNum::getBallNumber(int clr, int i)
{
	if (clr == 0 && i < 5)				//if the color is white and index is valid
	{
		return whiteball[i].getNumber();
	}
	else if (clr == 1 && i == 0)		//if color is red and index is valid
	{
		return powerball.getNumber();
	}
	else return 0;
}

void HistoryNum::setRate(int clr, int i, float r) //set rate based on color and index of the ball if it is white
{
	if (clr == 0 && i < 5)
	{
		whiteball[i].setRate(r);
	}
	else if (clr == 1 && i == 0)
	{
		powerball.setRate(r);
	}

}

float HistoryNum::getRate(int clr, int i)
{

	if (clr == 0 && i < 5)
	{
		return whiteball[i].getRate();
	}
	else if (clr == 1 && i == 0)
	{
		return powerball.getRate();
	}
	else return 0;
}

