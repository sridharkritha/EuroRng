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
#include "mersenneTwisterRandNumGen.h"
using namespace std;

int main() {
	
	int genRand = 0;		
	// Mersenne Twister Random Number Generator
	// initialize random seed: - should only be called once.
	//unsigned long init[4J] = {0x123, 0x234, 0x345, 0x456}, length = 4;
	//MTRand_int32 irand(init, length); // 32-bit int generator
	unsigned long init[1] = {time(NULL)}, length = 1;
	MTRand_int32 irand(init, length); // 32-bit int generator
	//MTRand_int32 irand(time(NULL));
	srand (time(NULL)); // Initialize random seed
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

	// BALL	
	std::ifstream Ballfile("input\\Ball5.txt");
	// Clear Input Stream
	Ballfile.clear();
	Ballfile.seekg(0, ios::beg);

	 while(std::getline(Ballfile, line))
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

	 // BALL
	 std::ifstream Luckyfile("input\\Lucky2.txt");
	 // Clear Input Stream
	Luckyfile.clear();
	Luckyfile.seekg(0, ios::beg);
	 while(std::getline(Luckyfile, line))
    {
        std::stringstream linestream(line);
        if (linestream >> one >> two)
        {
            // Three values have been read from the line
			Luc.push_back(one);	
			Luc.push_back(two);				
        }
	 }

 	// Writing the Millionaire Making Number
freopen("output\\MillionaireMakingNumber.txt", "w", stdout);

	for(int count=0; count<100; ++count)
		{
	// 5 Balls	
	for(int bCount=0; bCount<5; ++bCount) {
		//randomNo = (int)irand();
		//randomNo = (int)irand() % Ball.size();
		//g = g % Ball.size();
		ret = BallResult.insert(Ball[(int)irand() % Ball.size()]);
		 // Check the duplicate
		 if (ret.second==false) {
			 bCount = bCount -1;
			 continue;
				}
		}
	// 2 Lucky
	for(int bCount=0; bCount<2; ++bCount) {
		/*int g = irand();
		g = g % Luc.size();*/
		ret = LucResult.insert(Luc[(int)irand()%Luc.size()]);
		 // Check the duplicate
		 if (ret.second==false) {
			 bCount = bCount -1;
			 continue;
				}
		}


	// Print the final result
	 for ( it=BallResult.begin() ; it != BallResult.end(); ++it )
	     cout<<*it<<"  ";
	 cout<<" /  ";
	  for ( it=LucResult.begin() ; it != LucResult.end(); ++it )
	     cout<<*it<<"  ";
	  cout<<endl;

	  BallResult.clear();
	  LucResult.clear();  

	}

	// Out of 100 Result select one

	// Pick a randon BALL Line
	std::ifstream RNGfile("output\\MillionaireMakingNumber.txt");
	// Clear Input Stream
	RNGfile.clear();
	RNGfile.seekg(0, ios::beg);
	line = "";

	int millionair = rand()%100;
			for(int LineCount=0; LineCount < millionair; ++LineCount){
				std::getline(RNGfile, line);
				std::istringstream iss(line);
			}
	cout<<"\n***************************************************\n";
	cout<<line;
	cout<<"\n***************************************************";

	return 0;
}


///////////////////////////////////////////////////////////////////////////////////

// BALL	
	/*
	while(!infile.eof()) {
		std::getline(infile, line);
		std::istringstream iss(line);		
		for(int i =0; i< line.length(); ++i) {
				if((line[i] !=' ') && (line[i] != '-')) {
					num += line[i];
					 space = true;
				}
				else if(line[i] ==' '){
					 if(space) {
				    space = false;
					n = atoi (num.c_str());
					Ball.push_back(n);					
					num = "";
					i +=2;
					 }
				}
			}
		//n = atoi (num.c_str());
		//Ball.push_back(n);
		num = "";
	}



// LUCKY
	while(!Luckyfile.eof()) {
		std::getline(Luckyfile, line);
		std::istringstream iss(line);

		for(int i =0; i< line.length(); ++i) {
				if((line[i] !=' ') && (line[i] != '-')) {
					num += line[i];
					 space = true;
				}
				else if(line[i] ==' '){
					 if(space) {
				    space = false;
					n = atoi (num.c_str());
					Luc.push_back(n);					
					num = "";
					i +=2;
					 }
				}
			}
		n = atoi (num.c_str());
		Luc.push_back(n);
		num = "";
	}

	*/
