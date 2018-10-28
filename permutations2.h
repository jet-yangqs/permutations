#include<iostream>
#include<vector>
#include<algorithm>
#include"stdlib.h"

using namespace std;

void ShowNewPermu( vector<int> newPermu){
	for(int i=0; i<newPermu.size(); i++)
		cout<<newPermu[i];
	cout<<endl;
}

vector<int> GetMixRadixNum( int num0, int radixFlag, int firstRadix, int length){       //thansform decimal number to mix radix number
	vector<int> mixRadixNum(length);                                                   //radixFlag>0 in increasing radix system, else in descending system
	int index0 = length-1;                                                                //firstRadix is '2' in '8765432' radix system
	int radix = firstRadix;
	while(num0 && index0>-1){
		mixRadixNum[index0] = num0%radix;
		num0 = num0/radix;
		if( radixFlag>0) radix++;
		else radix--;
		index0--;
	}
	return mixRadixNum;
}

void CalculatePermu( vector<int> &permu, vector<int> midNum, vector<int> fisPermu){   //get permutation from medium number (increasing radix method)
	int size0 = permu.size();
	vector<int> permuIndex( size0,0);
	int bankLoc = midNum[0];
	permu[size0-1-bankLoc] = fisPermu[ size0-1 ];
	permuIndex[size0-1-bankLoc] = 1;
	for(int i =1; i<size0-1; i++){
		bankLoc = midNum[i];
		//cout<<"i"<<i<<" bankloc:"<<bankLoc;
		int lBound = size0-1-bankLoc;
		//cout<<"lbound "<<lBound<<endl;
		for(int j=size0-1; j>=lBound; j--){
			if(permuIndex[j]){
				bankLoc++;
				lBound--;
				//cout<<"if bankloc "<<bankLoc<<"lbound "<<lBound<<endl;
			}
		}
		permu[size0-1-bankLoc] = fisPermu[size0-1-i];
		permuIndex[size0-1-bankLoc] = 1;
		//cout<<"permu[size0-1-bankLoc]:"<<size0<<" "<<bankLoc<<"fisPermu[size0-1-i] "<<fisPermu[size0-1-i]<<endl;
	}
	
	int bound0 = -1;
	for(int k=0; k<size0; k++){
		if(!permuIndex[k]) {
			bound0 = k;
			break;
		}
	}
	permu[bound0] = fisPermu[0];
}

void ShowSpecPermu( vector<int> permu0, int order);
void ShowPermus( int range){
    vector< int > NewPermu( range);   //new permutation
    vector< int > FisPermu( range); 
	for(int i=0; i<range; i++) FisPermu[i]=i;
	int permuCount = 1;
	for(int i=1; i<=range; i++)
		permuCount *= i;
	for(int i=0; i<permuCount; i++) ShowSpecPermu(FisPermu,i);
	
} 

void CalculateMidNum( vector<int> permu, vector<int> &midnum, vector<int> fisPermu){

	for(int i=0; i<permu.size()-1; i++){
		int iNum = fisPermu[ fisPermu.size()-1-i];
		int lBound = 0;
		for(int k=0;k<permu.size(); k++){
			if(permu[k] == iNum) {
				lBound = k;
				break;
			}
		}
		int count = 0;
		for(int j=lBound; j<permu.size(); j++){                                      //count how many numbers from right side smaller than this location
			if(permu[j]<permu[lBound])
				count++;
		}
		midnum[i] = count;
	}
}



vector<int> AddRadixNum( vector<int> V1, vector<int> V2, int radixFlag, int firstRadix){      //add two mix radix number
	vector<int> V = V1;
	int carryFlag = 0;
	int radix = firstRadix;
	for(int i=V1.size()-1; i>-1; i--){
		V[i] = (V1[i] + V2[i] + carryFlag)%radix;
		carryFlag = (V1[i] + V2[i] + carryFlag)/radix;
		if( radixFlag>0) radix++;
		else radix--;
	}
	return V;
}

vector<int> MinusRadixNum(vector<int> V1, vector<int> V2, int radixFlag, int firstRadix){       //V1 minus V2
	vector<int> V = V1;
	int carryFlag = 0;
	int radix = firstRadix;
	for(int i=V1.size()-1; i>-1; i--){
		if( (V1[i]-carryFlag) >= V2[i]){
			V[i] = V1[i] - carryFlag - V2[i];
			carryFlag = 0;
		}else{
			V[i] = radix + V1[i] - carryFlag - V2[i];
			carryFlag = 1;
		}

		if( radixFlag>0) radix++;
		else radix--;
	}
	return V;
}

void ShowSpecPermu( vector<int> permu0, int order){
	 vector< int > NewPermu = permu0;   //new permutation
    vector< int > FisPermu = permu0;   
	sort( FisPermu.begin(), FisPermu.end());
	vector< int > NewMidNum( permu0.size()-1 );    
	CalculateMidNum( permu0, NewMidNum, FisPermu);
	//cout<<"NewMidNum1:";
	//for(int i=0;i<NewMidNum.size();i++) cout<<NewMidNum[i];cout<<endl;
	vector<int> vOrder = GetMixRadixNum(abs(order), 1, 2, permu0.size()-1);
	
	NewMidNum = order>0? AddRadixNum(NewMidNum, vOrder, 1, 2):MinusRadixNum(NewMidNum, vOrder, 1, 2);
	
	CalculatePermu( NewPermu, NewMidNum, FisPermu);
	ShowNewPermu( NewPermu );
}