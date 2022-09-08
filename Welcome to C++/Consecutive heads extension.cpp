// Consecutive heads extension.cpp : main project file.

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "random.h"
using namespace std;
// Constants
const double CHANCE = 0.5;
const int CONSECUTIVE_N = 3;
const char SENTINEL = 'o';
// Takes in from the user the desired combination of heads and tails.
string getCombination(){
	cout<<"Enter your desired combination of heads and tails as h's and t's , then enter x to start."<<endl;
	string combination;
	while(true){
		string str = getLine("input: ");
		char ch = tolower(str[0]);
		if(str.length()>1||(ch!='h'&&ch!='t'&&ch!='x')){
			cout<<"Invalid input. Try again"<<endl;
		}
		if(ch=='h'||ch=='t'){
			combination+=ch;
		}
		if(ch=='x'){
			if(combination.length()==0){
				cout<<"You have to type in your combination first"<<endl;
			} else {
				return combination;
			}
		}
	}
}
void simulateTosses(string& combination){
	int count = 0;
	int total = 0;
	while(true){
		bool p = randomChance(CHANCE);
		if(p){
			if(combination[count]=='h'){
				count++;
			} else {
				count = 0;
			}
			cout<<"heads"<<endl;
		} else {
			if(combination[count]=='t'){
				count++;
			} else {
				count = 0;
			}
			cout<<"tails"<<endl;
		}
		total++;
		if(count == combination.length()) break;
	}
	cout<< "It took "<<total<<" tries to get "<<combination<<" , your desired combination"<<endl;
}
int main() {
	string combination = getCombination();
	simulateTosses(combination);
    return 0;
}