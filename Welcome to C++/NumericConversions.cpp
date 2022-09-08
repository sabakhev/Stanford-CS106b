/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
string intToString2(int n);
int stringToInt(string str);
int stringToInt2(string str);
bool allNums(string);

/* Main program */

int main() {
	string str = getLine("Enter a number as a string to covert to an int: ");
	while(!allNums(str)){
		str = getLine("Invalid input. Try again: ");
	}
	cout<<stringToInt(str)<<endl;
	int n = getInteger("Enter a number as an int to convert to a string: ");
	cout<<intToString(n)<<endl;
    return 0;
}
// This is a recursive function where the main process happens.
string intToString2(int n){
    if(n < 10){
        return string()+char('0'+n);
    }
    return intToString2(n/10) + string()+char('0'+(n%10));
}
//This is a helper function to make it easier to operate with negative numbers.
string intToString(int n){
    if(n < 0){
        return "-"+intToString2(-1*n);
    }
    return intToString2(n);
}
// This also is a recursive function where the main process happens.
int stringToInt2(string str){
    if(str.length()==1){
		return str[0]-'0';
	}
	return stringToInt2(str.substr(0, str.length()-1))*10 + str[str.length()-1]-'0';
}
//This also is a helper function to make it easier to operate with negative numbers.
int stringToInt(string str){
    if(str[0]=='-'){
      return -1*stringToInt2(str.substr(1, str.length()-1));
    }
    return stringToInt2(str);
}
// This method checks if the input string only has digits as chars or not
bool allNums(string str){
	for(int i = 0; i < str.length(); i++){
		if(!isdigit(str[i])&&str[i]!='-') return false;
	}
	return true;
}