#include<iostream>
#include<vector>
#include<algorithm>
#include"stdlib.h"

using namespace std;

void ShowNewPermu( vector<int> newPermu){     //print newPermu
	for(int i=0; i<newPermu.size(); i++)
		cout<<newPermu[i];
	cout<<endl;
}

vector<int> GetMixRadixNum( int num0, int radixFlag, int firstRadix, int length){       //thansform decimal number num0 to mix radix number
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

void CalculatePermu( vector<int> &permu, vector<int> midnum, vector<int> fisPermu){   //get permutation from serials number
	
	vector<int> fisPermuIndex( fisPermu.size(),0);

	permu[0] = fisPermu[ midnum[0] ];                                        // for first location from left, there are midnum[0] numbers smaller
	fisPermuIndex[ midnum[0] ] = 1;
	for(int i=1; i<permu.size()-1; i++){
	    int Index = midnum[i];
		
		int count=0;
		for(int j=0; j<=Index; j++){
			if(fisPermuIndex[j]) count++;
		}
		int count1 = count;
		while(count1){
			count1=0;
			for(int j=Index+1; j<=Index+count; j++){
			if(fisPermuIndex[j]) count1++;
			}
			Index += count;
			count = count1;
		}
		/*for(int j=Index; j<Index+count; j++){
			if(fisPermuIndex[j]) count1++;
	
		}
		if(count1){
			Index += count;
			count += count1;
		}*/
		//Index += count;
		
		//while(fisPermuIndex[Index]) Index++;
		

	    permu[i] = fisPermu[Index];
		
		fisPermuIndex[Index] = 1;
	}
		
	for(int i=0;i<permu.size();i++){
			if(!fisPermuIndex[i]) {
				permu[permu.size()-1] = fisPermu[i];
				return;
			}
	}
}

void ShowPermus( int range){
    vector< int > NewPermu( range);   //new permutation
    vector< int > FisPermu( range); 

	vector< int > NewMidNum(range-1);    //
	for(int i = 0; i<range; i++){
		FisPermu[i] = NewPermu[i] = i;
		//NewMidNum[i] = 0;
	}
	/*cout<<"fisnum";
	for(int i=0;i< FisPermu.size();i++) cout<<FisPermu[i]; cout<<endl;
	cout<<"mudnum";
	for(int i=0;i< NewMidNum.size();i++) cout<<NewMidNum[i]; cout<<endl;*/

	int permuCount = 1;
	for(int i=1; i<=range; i++)
		permuCount *= i;

	for(int j=0; j<permuCount; j++){
		ShowNewPermu( NewPermu );
		NewMidNum = GetMixRadixNum( j+1, 1, 2, range-1 );
		//cout<<"mudnum";
	//for(int i=0;i< NewMidNum.size();i++) cout<<NewMidNum[i]; cout<<endl;
		CalculatePermu( NewPermu, NewMidNum, FisPermu);
	}
} 

void CalculateMidNum( vector<int> permu, vector<int> &midnum){
	for(int i=0; i<permu.size()-1; i++){
		int count = 0;
		for(int j=i; j<permu.size(); j++){                                      //count how many numbers from right side smaller than this location
			if(permu[j]<permu[i])
				count++;
		}
		midnum[i] = count;
	}
}

/*vector<int> GetMixRadixNum( int num0, int radixFlag, int firstRadix, int length){       //thansform decimal number to mix radix number
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
}*/

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

vector<int> MinusRadixNum(vector<int> V1, vector<int> V2, int radixFlag, int firstRadix){       //mixradix number V1 minus V2
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

void ShowSpecPermu( vector<int> permu0, int order){              //print the permutation that is order locations before or after permu0
	 vector< int > NewPermu = permu0;   //new permutation
    vector< int > FisPermu = permu0;   
	sort( FisPermu.begin(), FisPermu.end());
	vector< int > NewMidNum( permu0.size()-1 );    
	CalculateMidNum( permu0, NewMidNum);
	//cout<<"NewMidNum1:";
	//for(int i=0;i<NewMidNum.size();i++) cout<<NewMidNum[i];cout<<endl;
	vector<int> vOrder = GetMixRadixNum(abs(order), 1, 2, permu0.size()-1);
	//cout<<"vOrder:";
	//for(int i=0;i<vOrder.size();i++) cout<<vOrder[i];cout<<endl;
	NewMidNum = order>0? AddRadixNum(NewMidNum, vOrder, 1, 2):MinusRadixNum(NewMidNum, vOrder, 1, 2);
	//cout<<"NewMidNum2:";
	//for(int i=0;i<NewMidNum.size();i++) cout<<NewMidNum[i];cout<<endl;
	CalculatePermu( NewPermu, NewMidNum, FisPermu);
	ShowNewPermu( NewPermu );
}