/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence){
	if(subsequence.size() == 0){
		return true;
	}
	if(text.size() == 0){
		return false;
	}
	if(text[0] == subsequence[0]){
		return isSubsequence(text.substr(1, text.length()-1), subsequence.substr(1, subsequence.length()-1));
	}
	return isSubsequence(text.substr(1, text.length()-1), subsequence);
}

int main() {
	string text = getLine("Enter the first (subsequence of) string: ");
	string subsequence = getLine("Enter the second (subsequence) string: ");
	if(isSubsequence(text, subsequence)){
		cout<<subsequence + " is a subsequence of " + text<<endl;
	} else {
		cout<<subsequence + " is not a subsequence of " + text<<endl;
	}
    return 0;
}
