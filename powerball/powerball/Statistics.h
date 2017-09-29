#ifndef Statistics_h
#define Statistics_h

#include <iostream>
#include <fstream>
#include <vector>
#include "HistoryNum.h"
#include "Ball.h"

using namespace std;


class Statistics
{
private:
	vector <HistoryNum>historynumber;			//a vector to store all history data
	Ball whiteballrate[70];						//store white ball showup rate
	Ball powerballrate[27];						//store red ball showup rate

public:
	Statistics(void);
	~Statistics(void);
	void BallBubbleSort(Ball ball[], int len);			//a bubble sort method to sort ball array
	void Readhistorydata(void);							//read data in file
	void Statistic(void);								//generate statistics
	void WriteResult(void);								//write results in file
	int getBallNumber(int i, int clr);					//get ball nmber
	float getBallRate(int i, int clr);					//get ball rate
	int getHistoryBallNumber(int i, int clr, int j);	//get ball number in history draw
	int getHistorydataSize(void);						//get history data size
};


#endif

