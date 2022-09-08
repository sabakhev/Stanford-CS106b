/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "tokenscanner.h"
using namespace std;
//Constants used in code
const string VOWELS    = string("aeiouy"); 
const double CONSTZERO = -15.59;
const double CONSTONE  = 0.39;
const double CONSTTWO  = 11.8;
// Private functions
void getInfo(ifstream&);
int countSyllables(string);
double grade(int, int, int);

int main() {
	ifstream infile;
	cout<<"Enter the name of the text: ";
	while(true){
		string filename = getLine();
		infile.open(filename.c_str());
		if(!infile.fail()) break;
		cout<< "Couldn't open the file. Try again: ";
		infile.clear();
	}
	getInfo(infile);
	infile.close();
    return 0;
}
// This method is used to do the most of the work in a program. It initializes token scanner and counts the desired types of the sentence.
void getInfo(ifstream& infile){
	TokenScanner tk (infile);
	tk.ignoreWhitespace();
	tk.addWordCharacters("'");
	int words = 1;
	int sentences = 1;
	int syllables = 0;
	bool w = false;
	bool s = false;
	while(tk.hasMoreTokens()){
		string str = tk.nextToken();
		TokenType type = tk.getTokenType(str);
		if(type==WORD&&isalpha(str[0])){
			if(w){
				words++;
			} else {
				w = true;
			}
			syllables += countSyllables(str);
		}
		if(type==OPERATOR){
			if(s){
				sentences++;
			} else {
				s = true;
			}
		}
	}
	cout<<"Words: "<<words<<endl;
	cout<< "Sentences: "<<sentences<<endl;
	cout<< "Syllables: "<<syllables<<endl;
	cout<<"Grade: "<<grade(words, sentences, syllables)<<endl;
}
// This particular method calculates the number of syllables in a word with a given method, which is implemented in the code.
int countSyllables (string str){
	int count = 1;
	bool p = false;
	for(int i = 0; i < str.length(); i++){
		if((VOWELS.find(str[i]+string()) != string::npos)){
			if((i!=str.length()-1&&VOWELS.find(str[i+1]+string())== string::npos)||(i==str.length()&&str[i]!='e')){
				if(p){
					count++;
				} else {
					p = true;
				}
			}
		}
	}
	return count;
}
// This method represents  a formula for a grade of a text.
double grade (int words, int sentences, int syllables){
	return CONSTZERO + CONSTONE*((double)words/sentences)+ CONSTTWO*((double)syllables/words);
}
