// Numeric conversions extension.cpp : main project file.

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;
/* Number of alphabetical characters in hexadecimal base */ 
const int NUM_ALPHA=6;
/* Function prototypes */
int hexadecimalToDecimal(string);
int hexadecimalToDecimal2(string);
bool isHexadecimal(string);
int powerFunction(int, int);
/* Main program */
int main() {
	string str = getLine("Enter a number as a hexadecimal to covert to decimal number: ");
	while(!isHexadecimal(str)){
		str = getLine("Invalid input. Try again: ");
	}
	cout<<"Your number in decimal base is "<<hexadecimalToDecimal(str)<<endl;
    return 0;
}
// Main method to which the parameter is passed.
int hexadecimalToDecimal(string str){
	if(str[0]=='-'){
		return -1*hexadecimalToDecimal2(str.substr(1, str.length()-1));
	} else {
		return hexadecimalToDecimal2(str);
	}
}
// This method converts the modulus of input hexadecimal
int hexadecimalToDecimal2(string str){
	if(str.length()==0){
		return 0;
	}
	int a;
	if(isalpha(str[0])){
		a = tolower(str[0])-'a'+10;
	} else {
		a = str[0]-'0';
	}
	int power = str.length()-1;
	return (powerFunction(16, power))*a + hexadecimalToDecimal2(str.substr(1, str.length()-1));
}
// This method checks if the input string is hexadecimal or not
bool isHexadecimal(string str){
	if(str.length()==0) return false;
	for(int i = 0; (i) < str.length(); i++){
		char ch = str[i];
		if(!isdigit(str[i])&&str[i]!='-'){
			if(isalpha(ch)){
				if(tolower(ch)-'a'>=NUM_ALPHA){
					return false;
				}
			} else {
				return false;
			}
		}
	}
	return true;
}
// Implementation of the power function.
int powerFunction (int a, int b){
	int result = 1;
	for(int i = 0; i < b; i++){
		result *= a;
	}
	return result;
}
