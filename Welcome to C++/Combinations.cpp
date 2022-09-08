/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

//*This is a recursive function to calculate combinations with two integers as inputs.
//The base case is chosen in occurances when C = 1.
int Comb(int a, int b){
	if(b==0||a==b){
		return 1;
	}
	return Comb(a-1, b-1)+Comb(a-1, b);
}
// The C of a pair (a,b) where b is greater than a is not defined, so we ask the customer to type in valid numbers for calculation.
int main() {
	int a = getInteger("Enter the first number: ");
	int b = getInteger("Enter the second number: ");
	while(b>a){
		cout<<"Invalid input. Try again"<<endl;
		a = getInteger("Enter the first number: ");
		b = getInteger("Enter the second number: ");
	}
	cout<<"The value of C("<<a<<", "<<b<<") is "<<Comb(a, b)<<endl;
    return 0;
}
