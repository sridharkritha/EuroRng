//EuroRnGNumGen.cpp:Definestheentrypointfortheconsoleapplication.
//
#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#pragmawarning(disable:4996)
#include"mersenneTwisterRandNumGen.h"
usingnamespacestd;



intmain(){

	intgenRand=0;
	//MersenneTwisterRandomNumberGenerator
	//initializerandomseed:-shouldonlybecalledonce.
	//unsignedlonginit[4J]={0x123,0x234,0x345,0x456},length=4;
	//MTRand_int32irand(init,length);//32-bitintgenerator
	unsignedlonginit[1]={(unsignedlong)time(NULL)},length=1;
	MTRand_int32irand(init,length);//32-bitintgenerator
	//MTRand_int32irand(time(NULL));
	srand((unsignedint)time(NULL));//Initializerandomseed
	std::stringline="";
	std::stringnum="";
	std::vector<int>Ball,Luc;
	//std::vector<int>BallResult,LucResult;
	set<int>BallResult,LucResult;
	pair<set<int>::iterator,bool>ret;
	set<int>::iteratorit;
	intn=0,randomNo=0;
	boolspace=true;
	intone=0,two=0,three=0,four=0,five=0;

	//BALL
	std::ifstreamBallfile("input\\Ball5.txt");
	//ClearInputStream
	Ballfile.clear();
	Ballfile.seekg(0,ios::beg);

	while(std::getline(Ballfile,line))
		{
		std::stringstreamlinestream(line);
		if(linestream>>one>>two>>three>>four>>five)
			{
			//Threevalueshavebeenreadfromtheline
			Ball.push_back(one);
			Ball.push_back(two);
			Ball.push_back(three);
			Ball.push_back(four);
			Ball.push_back(five);
			}
		}

	//BALL
	std::ifstreamLuckyfile("input\\Lucky2.txt");
	//ClearInputStream
	Luckyfile.clear();
	Luckyfile.seekg(0,ios::beg);
	while(std::getline(Luckyfile,line))
		{
		std::stringstreamlinestream(line);
		if(linestream>>one>>two)
			{
			//Threevalueshavebeenreadfromtheline
			Luc.push_back(one);
			Luc.push_back(two);
			}
		}

	//WritingtheMillionaireMakingNumber
	freopen("output\\MillionaireMakingNumber.txt","w",stdout);

	for(intcount=0;count<100;++count)
		{

		//5Balls
		for(intbCount=0;bCount<5;++bCount){
			ret=BallResult.insert(Ball[(int)irand()%Ball.size()]);
			//Checktheduplicate
			if(ret.second==false){
				bCount=bCount-1;
				continue;
				}
			}

		//2LuckyStars
		for(intbCount=0;bCount<2;++bCount){
			ret=LucResult.insert(Luc[(int)irand()%Luc.size()]);
			//Checktheduplicate
			if(ret.second==false){
				bCount=bCount-1;
				continue;
				}
			}


		//Printthefinal100results
		for(it=BallResult.begin();it!=BallResult.end();++it)
			cout<<*it<<"";
		cout<<"/";
		for(it=LucResult.begin();it!=LucResult.end();++it)
			cout<<*it<<"";
		cout<<endl;

		BallResult.clear();
		LucResult.clear();

		}

	//Outof100Resultselectone
	//PickarandomBALLLine
	std::ifstreamRNGfile("output\\MillionaireMakingNumber.txt");
	//ClearInputStream
	RNGfile.clear();
	RNGfile.seekg(0,ios::beg);
	line="";

	intmillionair=rand()%100;
	for(intLineCount=0;LineCount<millionair;++LineCount){
		std::getline(RNGfile,line);
		std::istringstreamiss(line);
		}
	cout<<"\n***************************************************\n";
	cout<<line;
	cout<<"\n***************************************************";

	return0;
	}


///////////////////////////////////////////////////////////////////////////////////

//BALL
/*
while(!infile.eof()){
std::getline(infile,line);
std::istringstreamiss(line);
for(inti=0;i<line.length();++i){
if((line[i]!='')&&(line[i]!='-')){
num+=line[i];
space=true;
}
elseif(line[i]==''){
if(space){
space=false;
n=atoi(num.c_str());
Ball.push_back(n);
num="";
i+=2;
}
}
}
//n=atoi(num.c_str());
//Ball.push_back(n);
num="";
}



//LUCKY
while(!Luckyfile.eof()){
std::getline(Luckyfile,line);
std::istringstreamiss(line);

for(inti=0;i<line.length();++i){
if((line[i]!='')&&(line[i]!='-')){
num+=line[i];
space=true;
}
elseif(line[i]==''){
if(space){
space=false;
n=atoi(num.c_str());
Luc.push_back(n);
num="";
i+=2;
}
}
}
n=atoi(num.c_str());
Luc.push_back(n);
num="";
}

*/