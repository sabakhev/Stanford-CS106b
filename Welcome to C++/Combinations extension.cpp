// Combinations extension.cpp : main project file.

// In this extension I use the additive feature of pascal's triangle to calculate a'th line from this triangle, 
// where a is the positive integer typed in by the user. 
#include <iostream>
#include "console.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

//This recursive method calculates a'th line from pascal's triangle and returns it as a vector.
Vector<int> pascalLine(int a){
	if(a==1){
		Vector<int> first(1,1);
		return first;
	}
	Vector<int> athLine(a,0);
	Vector<int> prevLine = pascalLine(a-1);
	for(int i = 0; i < a; i++){
		if(i>0){
			athLine[i]+=prevLine[i-1];
		}
		if(i<a-1){
			athLine[i]+=prevLine[i];
		}
	}
	return athLine;
}
// This method just prints out the components of calculated vector.
void printInputLine(Vector<int>& vector){
	for(int i = 0; i < vector.size(); i++){
		cout<<vector[i]<<" ";
	}
	cout<<endl;
}

int main() {
	int a = getInteger("Your input: ");
	while(a<1){
		a = getInteger("Input has to be positive: ");
	}
	printInputLine(pascalLine(a));
    return 0;
}