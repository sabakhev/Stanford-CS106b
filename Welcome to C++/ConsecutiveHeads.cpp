/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "random.h"
using namespace std;
// Constants
const double CHANCE = 0.5;
const int CONSECUTIVE_N = 3;

int main() {
	int count = 0;
	int total = 0;
	while(true){
		bool p = randomChance(CHANCE);
		if(p){
			count ++;
			cout<<"heads"<<endl;
		} else {
			count = 0;
			cout<<"tails"<<endl;
		}
		total++;
		if(count == CONSECUTIVE_N) break;
	}
	cout<< "It took "<<total<<" tries to get "<<CONSECUTIVE_N<<" consecutive heads"<<endl;
    return 0;
}
