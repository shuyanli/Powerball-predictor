#ifndef HistoryNum_h
#define HistoryNum_h

#include "Ball.h"
#include <string>


/*
place to store the history winning numbers
*/


class HistoryNum		//store history draw information
{
private:
	std::string drawdate;		//the date of draw	
	Ball whiteball[5];		    //five white balls
	Ball powerball;		        //one red power ball


public:
	HistoryNum(void);
	HistoryNum(int whitenum[5], int rednum, std::string str);		//initialize object
	~HistoryNum(void);

	std::string getdate(void);				//get draw date
	Ball getwhiteball(int i);				//get the white ball
	Ball getpowerball(void);				//get the red power ball
	void setWhiteBall(int num, int i);		//set white ball number
	void setPowerBall(int num);				//set red power ball number
	int getBallNumber(int clr, int i);		//get ball number based on color
	void setRate(int clr, int i, float r);	//set rate based on color/index
	float getRate(int clr, int i);			//get rate based on color/index

};

#endif
