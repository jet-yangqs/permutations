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

void CalculatePermu( vector<int> &permu, vector<int> midNum, vector<int> fisPermu){   //get permutation from medium number (neighborhood exchange method)
	int size0 = permu.size();
	vector<int> permuIndex( size0,0);                                                 //using to mark the blank location
	int dirFlag = 0;                                          // dirflag mark the direction of each number
	for(int i=size0; i>1; i--){
		int iNum = fisPermu[i-1];
		if(i>2)dirFlag = i%2?( midNum[i-3]%2? 1: -1):( (midNum[i-3]+midNum[i-4])%2 ?1:-1 );
		else if(i==2) dirFlag = -1;
		//cout<<"i:"<<i<<" dirFlag:"<<dirFlag<<endl;
		int iBank = midNum[i-2];
		//cout<<"i:"<<i<<" midNum:"<<midNum[i-2]<<endl;
        int countBank = 0;
		if(dirFlag==1){
			int iIndex = 0;
			while(countBank < iBank){
				if( !permuIndex[ iIndex ]){
					countBank++;
					iIndex++;
				}else{
					iIndex++;
				}
			}
			while(permuIndex[ iIndex ]) iIndex++;
			//cout<<"i:"<<i<<" midNum:"<<midNum[i-2]<<" bank:"<<iBank<<"iIndex:"<<iIndex<<endl;
			permu[ iIndex ] = iNum;
			permuIndex[ iIndex ] = 1;
		}
		else if( dirFlag == -1){
			int iIndex = size0-1;
			while(countBank < iBank){
				if( !permuIndex[ iIndex ]){
					countBank++;
					iIndex--;
				}else{
					iIndex--;
				}
			}
			while(permuIndex[ iIndex ]) iIndex--;
			//cout<<"i:"<<i<<" midNum:"<<midNum[i-2]<<" bank:"<<iBank<<"iIndex:"<<iIndex<<endl;
			permu[ iIndex ] = iNum;
			permuIndex[ iIndex ] = 1;
		}
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

void CalculateMidNum( vector<int> permu, vector<int> &midnum, vector<int> fisPermu){        //calculate the medium number
	int size0 = permu.size();
	int dirFlag = -1;
	
	int iIndex = -1;
	for(int k=0; k<size0-1;){
		int count = 0;
	for(int i=0; i<size0; i++){
		if(permu[i] == fisPermu[k+1]){
			iIndex = i;
			break;
		}
	}
	//cout<<"iIndex:"<<iIndex<<endl;
	if(dirFlag<0){
		for(int j=iIndex; j<size0; j++){
		    if(permu[j]<permu[iIndex]) count++;
	    }
	}
	else{
		for(int j=0; j<iIndex; j++){
		    if(permu[j]<permu[iIndex]) count++;
	    }
	}
	//cout<<"dirflag:"<<dirFlag<<" count:"<<count<<endl;
	midnum[k] = count;
	 k++;
	 dirFlag = (k+2)%2 ? (midnum[k-1]%2? 1:-1):( (midnum[k-1]+midnum[k-2])%2? 1:-1);
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
	vector<int> vOrder = GetMixRadixNum(abs(order), -1, permu0.size(), permu0.size()-1);
	//cout<<"vOrder:";
	//for(int i=0;i<vOrder.size();i++) cout<<vOrder[i];cout<<endl;
	NewMidNum = order>0? AddRadixNum(NewMidNum, vOrder, -1, permu0.size()):MinusRadixNum(NewMidNum, vOrder, -1, permu0.size());
	//cout<<"NewMidNum2:";
	//for(int i=0;i<NewMidNum.size();i++) cout<<NewMidNum[i];cout<<endl;
	CalculatePermu( NewPermu, NewMidNum, FisPermu);
	ShowNewPermu( NewPermu );
}