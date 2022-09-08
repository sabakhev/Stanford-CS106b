// Numeric conversions extension 2.cpp : main project file.

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;
//In this extention, I allow users to choose the radix(the basis) for the numerical system they want to convert from.
/* Function prototypes */
int numericalToDecimal(string, int);
int numericalToDecimal2(string, int);
bool isValid(string, int);
int powerFunction(int, int);
/* Main program */
int main() {
	int base = getInteger("Enter the radix(the base) of your desired numeral system(for example binary system has radix-2, hexadecimal-16 and etc.): ");
		while(base<=0||base>36){
			base = getInteger("Please, enter nonnegative values that are less than 36: " );
		}
	string str = getLine("Enter a number in your numerical system to covert to decimal number: ");
	while(!isValid(str, base)){
		str = getLine("Invalid input. Try again: ");
	}
	cout<<"Your number in decimal base is "<<numericalToDecimal(str, base)<<endl;
    return 0;
}
// Main method to which the parameter is passed.
int numericalToDecimal(string str, int base){
	if(str[0]=='-'){
		return -1*numericalToDecimal2(str.substr(1, str.length()-1), base);
	} else {
		return numericalToDecimal2(str, base);
	}
}
// This method converts the modulus of input hexadecimal
int numericalToDecimal2(string str, int base){
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
	return (powerFunction(base, power))*a + numericalToDecimal2(str.substr(1, str.length()-1), base);
}
// This method checks if the input string is hexadecimal or not
bool isValid(string str, int base){
	if(str.length()==0) return false;
	for(int i = 0; i < str.length(); i++){
		char ch = str[i];
		if(ch!='-'&&!isalpha(ch)&&!isdigit(ch)) return false;
		if(base>10){
			if(isalpha(ch)){
				if(tolower(ch)-'a'>=base-10){
					return false;
				}
			}
		} else {
			if(isalpha(ch)){
				return false;
			}
			if(isdigit(ch)){
				if(ch-'0'>=base){
					return false;
				}
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
