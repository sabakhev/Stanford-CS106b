/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "map.h"
#include "simpio.h"
#include "vector.h"
#include <fstream>
#include "random.h"
using namespace std;

//Constants
const int NUM_CHARS = 2000;

//*This method creates the map storing information about the text. First it reads the k-order amount of characters,
//associates each one with following character, and repeats this process in the next step.
Map <string, Vector<char> > storeInfo (ifstream& infile, int order){
	Map <string, Vector<char> > info;
	int n = 0;
	bool p = false;
	string word;
	char ch;
	while (infile.get(ch)) {
		if(p){
			info[word].add(ch);
			word = word.substr(1,word.length()-1)+ch;
		}
		if(!p){
			word+=ch;
			n++;
			if(n==order){
				p = true;
			}
		} 
	}
	return info;
}
// Takes in the information about the text as a map and finds the most used sequence of characters of the specified order.
string getMostUsed(Map <string, Vector<char> >& info){
	string max = string("");
	int maxRepetitions = 0;
	foreach(string word in info){
		if(info[word].size()>maxRepetitions){
			maxRepetitions = info[word].size();
			max = word;
		}
	}
	return max;
}
// This void generates a proportionally random character for the last sequence in the text, then adds this character to text and
// then repeats this process for the new last sequence.
void generateText(Map <string, Vector<char> >& info){
	string currentWord = getMostUsed(info);
	string text = currentWord;
	for(int i = 0; i < NUM_CHARS; i++){
		int n = info[currentWord].size();
		int randInt = randomInteger(0, n-1);
		char ch = info[currentWord][randInt];
		text+=ch;
		currentWord = currentWord.substr(1)+ch;
	}
	cout<<text<<endl;
}
int main() {
	string fileName = getLine("Enter the source text: ");
	ifstream infile;
	infile.open(fileName.c_str());
	while(infile.fail()){
		fileName = getLine("Couldn't open the file. Try again: ");
		infile.clear();
		infile.open(fileName.c_str());
	}
	int order = getInteger("Enter the Markov order for this text[1-10]: ");
	while(order<1||order>10){
		order = getInteger("Order out of range. Try again[1-10]: ");
	}
	cout<<"Processing..."<<endl;
	Map <string, Vector<char> > info = storeInfo(infile, order);
	generateText(info);
    return 0;
}
