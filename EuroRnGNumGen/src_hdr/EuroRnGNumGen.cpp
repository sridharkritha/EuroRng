// EuroRnGNumGen.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <set>
#pragma warning(disable: 4996)
#include "mersenneTwisterRandNumGen.h"
using namespace std;
////////////////////////////// PRIME NUMBER TEST /////////////////////////////////////////////////
/* Miller-Rabin primality test, iteration signifies the accuracy of the test */
/* This function calculates (ab)%c */
int modulo(int a,int b,int c){
    long long x=1,y=a; // long long is taken to avoid overflow of intermediate results
    while(b > 0){
        if(b%2 == 1){
            x=(x*y)%c;
        }
        y = (y*y)%c; // squaring the base
        b /= 2;
    }
    return x%c;
}
/* This function calculates (a*b)%c taking into account that a*b might overflow */
long long mulmod(long long a,long long b,long long c){
    long long x = 0,y=a%c;
    while(b > 0){
        if(b%2 == 1){
            x = (x+y)%c;
        }
        y = (y*2)%c;
        b /= 2;
    }
    return x%c;
}
/* Find the number is prime or not */
bool isPrime_Miller(long long p,int iteration){
    if(p<2){
        return false;
    }
    if(p!=2 && p%2==0){
        return false;
    }
    long long s=p-1;
    while(s%2==0){
        s/=2;
    }
    for(int i=0;i<iteration;i++){
        long long a=rand()%(p-1)+1,temp=s;
        long long mod=modulo(a,temp,p);
        while(temp!=p-1 && mod!=1 && mod!=p-1){
            mod=mulmod(mod,mod,p);
            temp *= 2;
        }
        if(mod!=p-1 && temp%2==0){
            return false;
        }
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// PERCENTAGE (%) OF WINNING CHANCE //////////////////////////////////////
bool YESorNO(int percentage) {
  return rand()%100 < percentage; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// 5 Number Rule //////////////////
// Accept Condition for the 5 number combination
#define MIN_EVEN_COUNT_5N  2
#define MIN_ODD_COUNT_5N   1
#define MIN_PRIME_COUNT_5N 1
// Reject Condition for the 5 number combination
#define MAX_SINGLE_DIGIT   4
//#define MAX_PRIME_COUNT_5N 3 
// 50% Accept / Reject 
#define HALF_PROB_EVEN_COUNT_5N 3 /* Accept/Reject - 50% of time if the prime count is 3*/
#define HALF_PROB_ODD_COUNT_5N 2
#define HALF_PROB_PRIME_COUNT_5N 2 
// 80% Accept 
#define EIGHTY_PERCENTAGE_SINGLE_DIGIT 1
#define FORTY_PERCENTAGE_SINGLE_DIGIT  2
#define TEN_PERCENTAGE_SINGLE_DIGIT    3  /* Three single digit combination */


///////////////////////////////////////////////
bool is_5_NumberProperty(int* pA) {
	int prime =0, odd =0, even =0, single = 0;
	for(int i=0; i<5; ++i) {
		if(0 == pA[i] % 2)
			 ++even;
		else if(isPrime_Miller(pA[i],3))
			++prime;
		else
			++odd;

		// Single Digit
		if(pA[i] < 10)
			++single;
	}

	if (single >=MAX_SINGLE_DIGIT) // 4 Single digit
		return false;
	else if (single = TEN_PERCENTAGE_SINGLE_DIGIT) // 3 Single digit
		    if (!YESorNO(10))
				return false;		
	else if (single = FORTY_PERCENTAGE_SINGLE_DIGIT) // 2 Single digit		
		   if(!YESorNO(40))
		     return false;
	else if (single = EIGHTY_PERCENTAGE_SINGLE_DIGIT) // 1 Single digit		
		   if(!YESorNO(80))
		     return false;

	if(even > (HALF_PROB_EVEN_COUNT_5N +1))  // Reject
		return false;

	if(prime == HALF_PROB_EVEN_COUNT_5N) {
		   if(YESorNO(50))  /*Check the 50% probability  or [ rand() % 2 ] - like Coin toss */
			  return false;
		}

   if(even > (HALF_PROB_ODD_COUNT_5N +1))  // Reject
		return false;

	if(even == HALF_PROB_ODD_COUNT_5N) {
		 if(YESorNO(50)) /*Check the 50% probability */
			return false;
		}

	if(even > (HALF_PROB_PRIME_COUNT_5N +1))  // Reject
		return false;

	if(even == HALF_PROB_PRIME_COUNT_5N) {
		 if(YESorNO(50)) /*Check the 50% probability */
			return false;
		}

	
	 if((even >= MIN_EVEN_COUNT_5N) && (odd >= MIN_ODD_COUNT_5N )   
		                       && (prime >= MIN_PRIME_COUNT_5N )) // Accept
							   return true;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// 2 Number Rule //////////////////
// Accept Condition for the 2 number combination
#define MIN_EVEN_COUNT_2N  2
#define MIN_ODD_COUNT_2N   1
#define MIN_PRIME_COUNT_2N 1
// Reject Condition for the 2 number combination
#define MAX_PRIME_COUNT_2N 3  
///////////////////////////////////////////////
bool is_2_NumberProperty(int* pA) {
	int prime =0, odd =0, even =0;
	for(int i=0; i<2; ++i) {
		if(0 == pA[i] % 2)
			 ++even;
		else if(isPrime_Miller(pA[i],3))
			++prime;
		else
			++odd;
	}

	 if(prime == MAX_PRIME_COUNT_2N)  // Reject
		return false;
	else if((even == MIN_EVEN_COUNT_2N) && (odd == MIN_ODD_COUNT_2N)   
		                       && (prime == MIN_PRIME_COUNT_2N )) // Accept
							   return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	int genRand = 0;
	// Mersenne Twister Random Number Generator
	// initialize random seed: - should only be called once.
	//unsigned long init[4J] = {0x123, 0x234, 0x345, 0x456}, length = 4;
	//MTRand_int32 irand(init, length); // 32-bit int generator
	unsigned long init[1] = {(unsigned long)time(NULL)}, length = 1;
	MTRand_int32 irand(init, length); // 32-bit int generator
	//MTRand_int32 irand(time(NULL));
	srand ((unsigned int)time(NULL)); // Initialize random seed
	std::string line = "";
	std::string num = "";
	std::vector<int> Ball,Luc;
	//std::vector<int> BallResult,LucResult;
	set<int> BallResult,LucResult;
	pair<set<int>::iterator,bool> ret;
	set<int>::iterator it;
	int n=0, randomNo = 0;
	bool space = true;
	int one=0,two=0,three=0,four=0,five=0;
	int millionairLine_5 = 0, millionairLine_2 = 0;

	// 5 Balls
	std::ifstream iBallfile("input\\Ball5.txt");
	// Clear Input Stream
	iBallfile.clear();
	iBallfile.seekg(0, ios::beg);

	while(std::getline(iBallfile, line))
		{
		std::stringstream linestream(line);
		if (linestream >> one >> two >> three >> four >> five)
			{
			// Three values have been read from the line
			Ball.push_back(one);
			Ball.push_back(two);
			Ball.push_back(three);
			Ball.push_back(four);
			Ball.push_back(five);
			}
		}
	iBallfile.close();

	//  2 Lucky Stars
	std::ifstream iLuckyfile("input\\Lucky2.txt");
	// Clear Input Stream
	iLuckyfile.clear();
	iLuckyfile.seekg(0, ios::beg);
	while(std::getline(iLuckyfile, line))
		{
		std::stringstream linestream(line);
		if (linestream >> one >> two)
			{
			// Three values have been read from the line
			Luc.push_back(one);
			Luc.push_back(two);
			}
		}
	iLuckyfile.close();	

// STAGE 1: Process - Shuffle the numbers
	ofstream oS_BallFile("output\\stage1_Shuffle_Ball5.txt");
	ofstream oS_Luckyfile("output\\stage1_Shuffle_Lucky2.txt");
	///int BallNo = 0;
	

	for(int count=0; count<199; ++count)
		{
		
       // Generate Millionaire random number samples	

		// 5 Balls
		for(int bCount=0; bCount<5; ++bCount) {
			// Store the Random values in sorted order
			ret = BallResult.insert(Ball[(int)irand() % Ball.size()]);			
			// Check the duplicate
			if (ret.second==false) {
				bCount = bCount - 1;
				continue;
				}
			}

		// 2 Lucky Stars
		for(int bCount=0; bCount<2; ++bCount) {
			ret = LucResult.insert(Luc[(int)irand()%Luc.size()]);
			// Check the duplicate
			if (ret.second==false) {
				bCount = bCount - 1;
				continue;
				}
			}	

		// Print the randomly generated Millionaire number with lucky star
		for ( it=BallResult.begin() ; it != BallResult.end(); ++it ) {
			cout<<*it<<" ";   // Writing in console
			oS_BallFile<<*it<<" "; // Writing in file
			}
		oS_BallFile<<endl;
		cout<<" / ";
		for ( it=LucResult.begin() ; it != LucResult.end(); ++it ) {
			cout<<*it<<" ";
			oS_Luckyfile<<*it<<" ";
			}
		oS_Luckyfile<<endl;
		cout<<endl;

		// Clear the set containers
		BallResult.clear();
		LucResult.clear();
}

	oS_BallFile.close();
	oS_Luckyfile.close();
//////////////////////////////////////////////////////////////////////////////////////////////////
// STAGE 2: Select the number sets which satisfies the combination property(rule) 
ifstream iRandBallFile("output\\stage1_Shuffle_Ball5.txt");
ofstream oRuleBallFile("output\\stage2_Rule_Select_Ball5.txt");
int nLines_ruleBallFile =0;

// Clear Input Stream
	iRandBallFile.clear();
	iRandBallFile.seekg(0, ios::beg);
	int fiveBall[5] = {0};
	while(std::getline(iRandBallFile, line))
		{
		std::stringstream linestream(line);
		if (linestream >> fiveBall[0] >> fiveBall[1] >> fiveBall[2] >> fiveBall[3] >> fiveBall[4])
			{

			  if(is_5_NumberProperty(fiveBall)) {
				  oRuleBallFile << fiveBall[0] <<" "<< fiveBall[1] <<" "<< fiveBall[2] <<" "
				  << fiveBall[3] <<" "<< fiveBall[4] << endl;
				  ++nLines_ruleBallFile;
				  }

			}
		}

	if(0 == nLines_ruleBallFile){
oRuleBallFile<<"There is no BALL 5 combination satisfies the rules - Try once again !!!";
}

	oRuleBallFile.close();
	iRandBallFile.close();


ifstream iRandLuckyFile("output\\stage1_Shuffle_Lucky2.txt");
ofstream oRuleLuckyFile("output\\stage2_Rule_Select_Lucky2.txt");
int nLines_ruleLuckyFile = 0;

// Clear Input Stream
	iRandLuckyFile.clear();
	iRandLuckyFile.seekg(0, ios::beg);
	int twoBall[2] = {0};
	while(std::getline(iRandLuckyFile, line))
		{
		std::stringstream linestream(line);
		if (linestream >> twoBall[0] >> twoBall[1])
			{
			  if(is_2_NumberProperty(twoBall)) {
				  oRuleLuckyFile << twoBall[0] <<" "<< twoBall[1] << endl;
				  ++nLines_ruleLuckyFile;
				  }
			}
		}

	if(0 == nLines_ruleLuckyFile){
oRuleLuckyFile<<"There is no BALL 2 combination satisfies the rules - Try once again !!!";
}

oRuleLuckyFile.close();
iRandLuckyFile.close();

ifstream iRuleBallFile("output\\stage2_Rule_Select_Ball5.txt");
ifstream iRuleLuckyFile("output\\stage2_Rule_Select_Lucky2.txt");
// Writing the Millionaire Making Number
freopen("output\\MillionaireMakingNumber.txt", "w", stdout);

// Clear Input Stream
iRuleBallFile.clear();
iRuleBallFile.seekg(0, ios::beg);
iRuleLuckyFile.clear();
iRuleLuckyFile.seekg(0, ios::beg);
line = "";

if((0 == nLines_ruleBallFile) || (0 == nLines_ruleLuckyFile)){
cout<<"There is no BALL 5 / Ball 2 combination satisfies the rules - Try once again !!!";
millionairLine_5 = millionairLine_2 = 0;
	}else
		{
millionairLine_5 = rand() % nLines_ruleBallFile;
millionairLine_2 = rand() % nLines_ruleLuckyFile;
}

// 5 Numbers - Pick a random BALL Line
for(int LineCount=0; LineCount < millionairLine_5; ++LineCount){
		std::getline(iRuleBallFile, line);
		std::istringstream iss(line);
		}
	cout<<"\n***************************************************\n";
	cout<<line;

// 2 Numbers - Pick a random BALL Line
for(int LineCount=0; LineCount < millionairLine_2; ++LineCount){
		std::getline(iRuleLuckyFile, line);
		std::istringstream iss(line);
		}
	cout<<" / ";
	cout<<line;
	cout<<"\n***************************************************";

//////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}

