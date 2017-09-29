#include "Statistics.h"
#include <algorithm>
/*
================================================================================================================================================
For this part, the program read in the pbhistory.txt from internet that record all the previous winning powerball records.
Then by reading line by line, we store each line as a HistoryNumber object called "historynumber_" and finally store all the objects in a vector.
================================================================================================================================================
*/

Statistics::Statistics(void)		//initialize
{
	for (int i = 0; i < 70; i++)
	{
		whiteballrate[i] = Ball(0, i);
	}

	for (int i = 0; i < 27; i++)
	{
		powerballrate[i] = Ball(1, i);
	}
}


Statistics::~Statistics(void)
{
}

int Statistics::getBallNumber(int i, int clr)
{
	if (clr == 0 && i < 70)				//if the color is white and index is valid
	{
		return whiteballrate[i].getNumber();
	}
	else if (clr == 1 && i < 27)		//if the color is red and index is valid
	{
		return powerballrate[i].getNumber();
	}
	else return 0;
}

int Statistics::getHistorydataSize(void)
{
	return historynumber.size();
}

float Statistics::getBallRate(int i, int clr)
{

	if (clr == 0 && i < 70)
	{
		return whiteballrate[i].getRate();
	}
	else if (clr == 1 && i < 27)
	{
		return powerballrate[i].getRate();
	}
	else return 0;
}

int Statistics::getHistoryBallNumber(int i, int clr, int j)
{
	if (i >= historynumber.size())return 0;
	if (clr == 0 || clr == 1)
	{
		return historynumber[i].getBallNumber(clr, j);
	}

	return 0;
}

void Statistics::Readhistorydata(void)
{
	cout << "Reading history data..." << endl;
	ifstream f;

	f.open("pbhistory.txt");		//open the file 
	if (!f.is_open())
	{
		cout << "ERROR: File pbhistory.txt open failed!" << endl;
		return;
	}

	HistoryNum historynumber_;

	int wn[5];
	int rn;
	int pp;
	string date;
	char buffer[100];
	f.getline(buffer, 100);

	while (1)					//read all data
	{
		if (f.eof())break;
		f.getline(buffer, 100);
		int i = 0;
		date.clear();
		for (i = 0; i < strlen(buffer); i++)
		{
			if (buffer[i] == ' ')break;
			else date += buffer[i];
		}
		i = i + 2;						//the interval between date and balls is 2;
		for (int j = 0; j < 5; j++)
		{
			wn[j] = (buffer[i] - '0') * 10 + buffer[i + 1] - '0';
			i = i + 4;					//the interval between each win number is 4;
		}
		rn = (buffer[i] - '0') * 10 + buffer[i + 1] - '0';
		i = i + 4;						//red number interval is same interval as balls
		while (!buffer[i] == '\0')
		{
			pp = (buffer[i] - '0') + pp * 10;
			i++;
		}
		if (0 == pp)					//if no powerplay this round, the powerplay should be default as 1
		{ 
			pp = 1;
		}

		historynumber_ = HistoryNum(wn, rn, date);
		historynumber.push_back(historynumber_);
	}
	f.close();
}

bool operator < (Ball b1, Ball b2) {
	return b1.getRate() > b2.getRate();
}


void Statistics::BallBubbleSort(Ball ball[], int len)
{
	Ball temp(0, 0);
	for (int i = 0; i < len; i++)		//implementing bubble sort of the winning rate
	{
		for (int j = len - 1; j > i; j--)
		{
			if (ball[j].getRate() > ball[j - 1].getRate())
			{
				temp.setRate(ball[j - 1].getRate());
				temp.setNumber(ball[j - 1].getNumber());
				ball[j - 1].setRate(ball[j].getRate());
				ball[j - 1].setNumber(ball[j].getNumber());
				ball[j].setRate(temp.getRate());
				ball[j].setNumber(temp.getNumber());
			}
		}
	}
}



/*================================================================================================================================================
There are total of 70 while balls to pick, 27 red balls (also known as powerball) to pick. Whats more, the rule changed several times
It was 45 whilte balls and 45 red balls to pick. Evetually, the rule says pick 5 in 69 white, and 1 in 27 red. There are some results
like ten years ago that has some powerball(red) >27. In this program we didnt count those balls in, for simplicity
This program work as follow:
1: for each red ball(number 1-69), count each data in history number and increase the corresponding count(rate here).
for example, for data{16,10,52,40,55} as winball, we increase the # 16, 10, 52, 40, 55 whiteball by one.
As a result, we can find out the total number of the ball that win in the past decades.

2: do the same thing for white(power) ball, and power rate.

3: compute the history posibility by dividing total number of the specific balls, powerballs, and powerplay rate by the total number of games

4: sort all the data in desceding order using bubble sort so that the highest rate will be easy to obtained.

NOTE:
1: I didnt use index 0 for each object. so the index 1 to n is same as the number of the balls, rates.
For examle, winballrate[0] will never be used, winballrate[1] means for the # 1 redball.
2: I did both bubble sort and sorting using STL. std::sort take O(nlogn) and bubble sort take O(n*n).
I could use priority_queue for this but it is not necessary, 
since the time complexity is the same but it requires more space.
==================================================================================================================================================
*/
void Statistics::Statistic(void)
{
	Readhistorydata();

	cout << "Processing history data... " << endl;
	float wr[70] = { 0 };		//white ball rate
	float rr[27] = { 0 };		//red ball rate						

	for (int i = 0; i < historynumber.size(); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			wr[historynumber[i].getBallNumber(0, j)]++; //count each win whiteball and increase the count of that ball
		}
		if (historynumber[i].getBallNumber(1, 0) < 27)	//for simplicity, get rid of the old rule data(that there were 45 white(power) balls in the pool)
		{
			rr[historynumber[i].getBallNumber(1, 0)]++;
		}

	}

	//compute the history posibility for each ball
	//by dividing time of the specific balls and powerballs by the total number of games
	for (int i = 0; i < 70; i++)
	{
		wr[i] /= (5 * historynumber.size());		
		whiteballrate[i].setRate(wr[i]);
	}
	for (int i = 0; i < 27; i++)
	{
		rr[i] /= historynumber.size();			
		powerballrate[i].setRate(rr[i]);
	}

	
	/*BallBubbleSort(whiteballrate, 70);		//back up sorting algorithm, O(n*n)
	BallBubbleSort(powerballrate, 27);*/		
	std::sort(whiteballrate, whiteballrate + 70);	//O(nlogn)
	std::sort(powerballrate, powerballrate + 27);
	

	WriteResult();
}


void Statistics::WriteResult(void)  //debug purpose. the generated txt file can show the result of the algorithm
{
	ofstream f;
	f.open("statistic.txt");
	if (!f.is_open())
	{
		cout << "ERROR: File statistic.txt open failed!" << endl;
		return;
	}

	cout << "Writing statistic data in file..." << endl;
	f << "WhiteBall Number" << "\t" << "Rate" << endl;
	for (int i = 1; i < 70; i++)f << whiteballrate[i].getNumber() << "\t" << "\t" << whiteballrate[i].getRate() << endl;	//write the statistic data into file

	f << "PowerBall Number" << "\t" << "Rate" << endl;
	for (int i = 1; i < 27; i++)f << powerballrate[i].getNumber() << "\t" << "\t" << powerballrate[i].getRate() << endl;


	f.close();
}