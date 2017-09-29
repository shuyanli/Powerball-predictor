# Powerball-predictor
just for fun, don't use this for gamble or any busness activity! self made powerball predictor


For Linux user, please run the all the file I included in the folder. Note: you must include the pbhistory.txt in the same folder, otherwise the program will not run successfully.


The main program is called powerball.cpp

One can also run the powerballtest.txt to see the results. If you want to change the numbers of the output, please change it in GlobePara. Same as above, the pbhistory.txt should be included.
I added a lot of comments in the program that describe what I didn't for the functions and algorithms. Part of the code can be optimized in the future, like getting the combination of all the numbers using recursion or iteration. The time complexity should be similar but the code will look cleaner. Due to time limits, I just implement one algorithm instead of multi-algorithm for this part. 

Some resource I use for this program:
1.	Pbhistory.txt
This file contains all the previous record of winning combinations. It can be downloaded from powerball website at : http://www.powerball.com/powerball/pb_nbr_history.asp

2.	Powerball history:
As I mentioned in the code, the rules has changed several times. So some data is useless in our game. To see how the rule is changed, please come here: http://www.powerball.com/pb_history.asp 

 
The tool "SLH editor" can also be found on powerball website. It tells me the odd-even, high-low possibilities.
If one want to check this, please go to http://www.smartluck.com/slhdownloads.htm download the smart luck history editor and open the file pb0569.slh. This file is also found on powerball website, that has statistics about all the results, the address is same as the slh editor shown above.

I also include my whole project folder of this game, called /powerball. Just in case there are some problem to run it. In visual studio, click powerball.sln to open the project. The source code is the same, the .exe file is in the Debug folder.
