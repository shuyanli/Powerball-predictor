#include "Ball.h"

Ball::Ball(void)
{
}

Ball::Ball(int clr, int num)		//initialize the ball
{
	color = clr;
	number = num;
	rate = 0;
}


Ball::~Ball(void)
{
}

int Ball::getColor(void)		//get color
{
	return color;
}

int Ball::getNumber(void)		//get number
{
	return number;
}

float Ball::getRate(void)		//get rate
{
	return rate;
}

void Ball::setRate(float r)		//set rate
{
	rate = r;
}

void Ball::setNumber(int num)		//set number
{
	number = num;
}