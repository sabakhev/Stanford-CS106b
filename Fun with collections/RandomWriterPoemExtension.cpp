// RandomWriterPoemExtension.cpp : main project file.

#include <iostream>
#include "console.h"
#include "map.h"
#include "simpio.h"
#include "vector.h"
#include <fstream>
#include "random.h"
#include "tokenscanner.h"
using namespace std;
// In this extension i have added a feature that not series of characters, but words' combinations are stored in a map of information.
// Also, using this technique i generate the poem based on the authors use of words. User writes in name of the text, and number of stanzas
// wished to be generated. Main feature of a poem is having 8 words in a single line, and rhyme scheme ABAB, which means that first and third lines(A's)
// and second and fourth(B's) lines rhyme with each other. The words in a stanza maintain a patterned connection when possible.
//Number of words in each line of poem.
const int NUM_WORDS = 8;
//Number of characters repeating in lines.
const int NUM_CHARS = 3;
//Number of iterations before a random word is chosen
const int NUM_IT = 100;
//*This method creates the map storing information about the text. I use tokenscanner class and store only word type tokens.
// Each word is stored in a map with a vector consisting of strings following that word in a text.
Map <string, Vector<string> > storeWords (ifstream& infile){
	Map <string, Vector<string> > info;
	TokenScanner tk (infile);
	tk.ignoreWhitespace();
	tk.addWordCharacters("'");
	string current;
	bool first = true;
	while(tk.hasMoreTokens()){
		string following = tk.nextToken();
		if(tk.getTokenType(following)==WORD){
			if(!first){
				info[current].add(following);
				current = following;
			}else {
				current = following;
				first = false;
			}
		}
	}
	return info;
}
// Takes in the information about the text as a map and finds the most used word in a text.
string getMostUsed(Map <string, Vector<string> >& info){
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
// This method generates a random word of length more or equal to NUM_CHARS to avoid a never ending cycle. This method assumes for large texts
// that there exist words of length more or equal to NUM_CHARS. This method is also used another time if rhyming word can't be found.
string generateRandWord (Map <string, Vector<string> >& info){
	string word="";
	while(word.size()<NUM_CHARS){
		int n = randomInteger(0, info.size());
		int a = 0;
		foreach(string str in info){
			if(a==n){
				word = str;
			}
			a++;
		}
	}
	return word;
}
// This method generates first and second lines of the 4-lined stanza. The starting word in each line is the randomly chosen
// string based on the previous word which is given as a parameter. The last word has to be at least NUM_CHARS - of length for the 
// rhyme to work.
string generateNewLine(Map <string, Vector<string> >& info, string startWord){
	string currentWord = startWord;
	string line ;
	for(int i = 0; i < NUM_WORDS; i++){
		int n = info[currentWord].size();
		int randInt = randomInteger(0, n-1);
		while(n==0){
			currentWord = generateRandWord(info);
			n = info[currentWord].size();
			randInt = randomInteger(0, n-1);
		}
		string newWord = info[currentWord].get(randInt);
		if(i == NUM_WORDS-1&&newWord.length()<NUM_CHARS){
			newWord = generateRandWord(info);
		}
		line= line+" "+newWord;
		currentWord = newWord;
	}
	return line;
}
// This method looks takes in a word and looks for a new word in the map ending with the same NUM_CHAR characters as the given word.
// If there is no such word, a random word is generated.
string getRhymingWord(Map <string, Vector<string> >& info, string rhymingWord){
	rhymingWord = char(tolower(rhymingWord[0])) + rhymingWord.substr(1, rhymingWord.length()-1); 
	foreach(string word in info){
		word = char(tolower(word[0])) + word.substr(1, word.length()-1);
		if(word.length()>=NUM_CHARS&&word!=rhymingWord&&rhymingWord.length()>=NUM_CHARS&&
			word.substr(word.length()-NUM_CHARS,NUM_CHARS)==rhymingWord.substr(rhymingWord.length()-NUM_CHARS,NUM_CHARS)){
			return word;
		}
	}
	return generateRandWord(info);
}
//This method generates third and fourth lines in accordance of ending of first and second lines respectively. The starting word
// is also given which should yield a continuation for this lines.
string generateRhymingLine(Map <string, Vector<string> >& info, string rhymingWord, string startWord){
	string currentWord = startWord;
	string line ;
	for(int i = 0; i < NUM_WORDS-1; i++){
		int n = info[currentWord].size();
		int randInt = randomInteger(0, n-1);
		while(n==0){
			currentWord = generateRandWord(info);
			n = info[currentWord].size();
			randInt = randomInteger(0, n-1);
		}
		string newWord = info[currentWord].get(randInt);
		line= line+" "+newWord;
		currentWord = newWord;
	}
	currentWord = getRhymingWord(info, rhymingWord);
	line = line + " " +currentWord;
	return line;
}
// This method takes in a line and using tokenscanner class returns the last word in it.
string getLastWord(string line){
	TokenScanner tk(line);
	tk.ignoreWhitespace();
	string word = "";
	while(tk.hasMoreTokens()){
		word = tk.nextToken();
	}
	return word;
}
// This void generates lines of stanza given amount of times. The end of the lines are important, as each line continues from the previous's 
// last word, and also first and second lines' endings are used to rhyme.
void generateText(Map <string, Vector<string> >& info, int stanza){
	for(int i = 0; i < stanza; i++){
		string startWord1 = getMostUsed(info);
		string firstLine = generateNewLine(info, startWord1);

		string startWord2 = getLastWord(firstLine);
		string secondLine = generateNewLine(info, startWord2);

		string startWord3 = getLastWord(secondLine);
		string thirdLine = generateRhymingLine(info, startWord2, startWord3);

		string startWord4 = getLastWord(thirdLine);
		string fourthLine = generateRhymingLine(info, startWord3, startWord4);

		cout<<firstLine<<+","<<endl;
		cout<<secondLine<<+","<<endl;
		cout<<thirdLine<<+","<<endl;
		cout<<fourthLine<<+"."<<endl;
		cout<<endl;
	}
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
	int stanza = getInteger("Enter the number of stanzas you wish to have in your poem: ");
	while(stanza<1){
		stanza = getInteger("The number has to be positive: ");
	}
	cout<<"Processing..."<<endl;
	Map <string, Vector<string> > info = storeWords(infile);
	generateText(info, stanza);
    return 0;
}
