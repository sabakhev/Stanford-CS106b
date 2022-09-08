/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "lexicon.h"
#include "console.h"
#include "simpio.h"
#include "vector.h"
#include "queue.h"
// This method is responsible for finding the ladder. It uses breadth-first algorithm to do so.
using namespace std;
Vector <string> findLadder(string& start, string& end, Lexicon& english){
	Queue <Vector<string> > queue;
	Vector <string> startVec;
	Lexicon usedWords;

	startVec.add(start);
	queue.enqueue(startVec);

	while(!queue.isEmpty()){
		Vector <string> vec = queue.dequeue();
		string lastWord = vec[vec.size()-1];
		if(lastWord==end){
			return vec;
		}
		for(int i = 0; i < lastWord.length(); i++){
			for(char ch = 'a'; ch <='z'; ch++){
				string newWord = lastWord.substr(0,i) + ch + lastWord.substr(i+1);
				if(english.contains(newWord)&&!usedWords.contains(newWord)){
					usedWords.add(newWord);
					Vector <string> newVec = vec;
					newVec.add(newWord);
					queue.enqueue(newVec);
				}
			}
		}
	}
	Vector <string> emptyVec;
	return emptyVec;
}
int main() {
	while(true){
		string start = getLine("Enter the starting word (or nothing to quit): ");
		if(start.length()==0){
			break;
		}
		string end = getLine("Enter the end word: ");
		Lexicon english("EnglishWords.dat");
		if(start.length()==end.length()&&english.contains(start)&&english.contains(end)){
			cout<<"Searching..."<<endl;
			Vector <string> vec = findLadder(start, end, english);
			if(vec.size()>0){
				cout<<"The ladder was found: "<<vec.toString()<<endl;
			} else {
				cout<<"The ladder couldn't be found"<<endl;
			}
		} else {
			cout<<"The ladder is impossible to find."<<endl;
		}
	}
	cout<<"Goodbye!"<<endl;
    return 0;
}
