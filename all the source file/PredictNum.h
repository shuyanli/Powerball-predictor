#ifndef PredictNum_h
#define PredictNum_h

#include "HistoryNum.h"
#include <string>
using namespace std;

class PredictNum :
	public HistoryNum
{
private:

	float posibility;					//the posibility of the prediction

public:
	PredictNum(void);
	~PredictNum(void);
	void setPosibility(float p);		//methods to modify the posibility
	float getPosibilbity(void);			//get posibility

};

#endif

