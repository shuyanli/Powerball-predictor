#include "Prediction.h"
#include <cmath>
#include <algorithm>




struct greater {		//this is use for sorting the results
	bool operator()(PredictNum p1, PredictNum p2) {
		return p1.getPosibilbity() > p2.getPosibilbity();
	}
};


Prediction::Prediction(void)
{
	statistics = Statistics();		//generate statistics object
	statistics.Statistic();
}


Prediction::~Prediction(void)
{
}


/*==============================================================================================================================================
The object of the following program is to compute all the combinations of a given data set.
For example, if we want to find 3 numbers combinations among 4, one way is to enumerate all posible combos,
that is, {0,1,2},{0,1,3},{0,2,3},{1,23}.

the step is:
1. Since the stretegy(REPEAT HITS LOTTERY TIPS) says that there are 38% possibility that one repeat hit from last drawing
, no repeat 47%, and 15% that has more then one repeat number, if we want to pridict the next winning numbers, we need to
compare it with the most recent result and check the possibilities of the repeat numbers.

2.pick the top ten highest white ball among all the 47 white balls. compute all the combinations and its corresponding win possibilities,
and store the these possibilities in descending order in vector <PredictNum>results that defined in Prediction.h;
=================================================================================================================================================
*/

void Prediction::Analyzation(void)
{
	PredictNum temp;
	int i[5];
	int ri = 0;
	int odds, even, low, high;
	int repeat;
	int count = 0;

	cout << "start computing...";
	while (ri < 5)			//for each powerball
	{
		for (int j = 0; j < 5; j++)
		{
			i[j] = j;
		}
		while (1)	//for each combination
		{
			odds = 0, even = 0, low = 0, high = 0, repeat = 0;;
			temp.setPosibility(1.00);
			for (int j = 0; j < 5; j++)
			{
				temp.setWhiteBall(statistics.getBallNumber(i[j], 0), j);
				if (temp.getBallNumber(0, j) % 2 == 0) //count the odd and even number
				{ 
					even++;
				}
				else 
				{ 
					odds++; 
				}
				if (temp.getBallNumber(0, j)>35)	  //number greater then 35 is high number, where as number smaller or equal to 35 is low number
				{ 
					high++; 
				}
				else
				{
					low++;
				}
				temp.setRate(0, j, statistics.getBallRate(i[j], 0));
				for (int s = 0; s < 5; s++)
				{
					if (temp.getBallNumber(0, j) == statistics.getHistoryBallNumber(0, 0, s)) //the most recent win number
					{
						repeat++;
						if (repeat > 3)
						{
							repeat = 3;

						}
						break;
					}
				}//end of for (int s = 0; s<5; s++)
				temp.setPosibility(temp.getPosibilbity()*temp.getRate(0, j));	//for five balls, the total possibility should be the product of each individual balls
			}//end of for (int j = 0; j<5; j++)

			temp.setPowerBall(statistics.getBallNumber(ri, 1));
			temp.setRate(1, 0, statistics.getBallRate(ri, 1));


			//compute posibility, now we also need to blend in the odd-even, high-low, repeat posibilities for the final posibilities 
			temp.setPosibility(temp.getPosibilbity()*temp.getRate(1, 0)*odd_even[odds] * low_high[low] * repeats[repeat]);	

			for (int s = 0; s < statistics.getHistorydataSize(); s++)			//check if all number repeat to history records
			{
				repeat = 0;
				for (int k = 0; k < 5; k++)
				{
					for (int l = 0; l < 5; l++)
					{
						if (temp.getBallNumber(0, k) == statistics.getHistoryBallNumber(s, 0, l))
						{
							repeat++;
							break;
						}
					}
				}
				if (repeat == 5)
				{
					temp.setPosibility(0);
					break;
				}
			}//end of for (int s = 0; s < statistics.getHistorydataSize(); s++)
			results.push_back(temp);

/*==============================================================================================================================================
As stated above, we find all the possible combination for 10 highest white balls.
The result should be from {0,1,2,3,4} to {5,6,7,8,9}

The algorithm is as follow:
1: start with 0,1,2,3,4. and add 1 to the end each time.
2: The most difficult part is the carry. For example:
(0,1,7,8,9)+1. I need to first put all the numbers that will overlap after adding the carry. in this case the 3th,4th,5th number to 0: 0,2,0,0,0.
then starting with the number that will not overlap, in this case the second number, I add one to this second number for the rest number
for example: (0,2,2+1,(2+1)+1,((2+1)+1)+1) that is (0,2,3,4,5).
Note: since only one number is allowed in each combination, so the largest combination should be 5,6,7,8,9 respectively.
=================================================================================================================================================
*/

			i[4]++;						//find next combination
			int l = 4;
			int flag = 0;
			for (l = 4; l > 0; l--)
			{
				if (i[l] > l + 5)
				{
					if ((i[l - 1] + 1) <= (l - 1 + 5))
					{
						i[l - 1]++;
						i[l] = i[l - 1] + 1;
						break;
					}
					else
					{
						i[l] = 0;
						i[l - 1]++;
						flag = 1;
					}

				}
				else break;
			}//end of for (l = 4; l>0; l--)
			if (l > 0 && l < 5 && flag == 1)
			{
				for (; l < 5; l++)
				{

					i[l] = i[l - 1] + 1;
				}
			}

			//for(int j=0;j<5;j++)cout<<i[j]<<" ";
			//cout<<endl;
			if (i[0] == 5 && i[1] == 6 && i[2] == 7 && i[3] == 8 && i[4] == 9)break;//if we get (5,6,7,8,9), this is our last combination
			count++;

		}
		cout << "...";
		ri++;

	}//end of while(ri<5)
	cout << endl;
	cout << "Compute " << count << " combination in total" << endl;
	cout << "Sorting...." << endl;


    PredictNum temp_;
    for(int j=0;j<results.size();j++)			//sort the results
    {
        for(int k=results.size()-1;k>j;k--)
        {
            if(results[k].getPosibilbity()>results[k-1].getPosibilbity())
            {

                std::swap(results[k], results[k-1]);
                
            }
        }
    }


	//sort(results.begin(), results.end(), greater());			//sort the results

}


/*==============================================================================================================================================
simply display the top k results. one can set ResultNumber to any integer
and the program will show the top k highest results.
================================================================================================================================================
*/
void Prediction::display(void)
{

	for (int i = 0; i < ResultNumber; i++)					//show the results
	{
		cout << "WhiteBall: ";
		for (int j = 0; j < 5; j++)cout << results[i].getBallNumber(0, j) << " ";
		cout << "PowerBall: " << results[i].getBallNumber(1, 0) << endl;
	}
	system("pause");
}
