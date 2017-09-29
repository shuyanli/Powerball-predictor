#ifndef Ball_h
#define Ball_h
class Ball				//ball object
{
private:
	int color;				//ball's color 0 = white ball, 1 = red power ball
	int number;				//ball's number
	float rate;				//the rate of the showup of ball
public:
	int getColor(void);					//get the color of ball
	int getNumber(void);				//get the number of ball
	float getRate(void);				//get the rate of ball
	void setRate(float r);				//set the rate of ball
	void setNumber(int num);			//set the number of ball
	Ball(void);
	Ball(int clr, int num);				//constructor to create ball object
	~Ball(void);						//distructor, test only
};

#endif
