#ifndef Prediction_h
#define Prediction_h

#include "PredictNum.h"
#include "Statistics.h"
#include "GlobePara.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
using namespace std;
									// using extern keyword, actually it is defined in GlobePara.h	
extern float odd_even[];			// the posibility of odd and even number
extern float low_high[];			// the posibility of low and high number
extern float repeats[];				// the posibility of repeated number

class Prediction
{
private:
	vector <PredictNum>results;		//state a vector to store reuslts
	Statistics statistics;			//the statistics object

public:
	Prediction(void);
	~Prediction(void);
	void Analyzation(void);		//method to ananlyze all combinations defined
	void display(void);			//display the results
};

#endif