/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
const int STANDARD_CUBES_SIZE = 16;
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};
const int BIG_BOGGLE_CUBES_SIZE = 25;
const int STANDART_GRID_SIZE = 4;
const int BIG_BOGGLE_GRID_SIZE = 5;
const int CUBE_N_SIDES = 6;
// * Structure used to store information about the points in the grid.
struct gridPoint{
	int y;
	int x;
};

/* Function prototypes */

void welcome();
void giveInstructions();
void initGame(Vector<string>& vec);
void lowerCharacters(string& str);
void loadVector(Vector<string>& vec, int size);
void loadVectorByUser(Vector<string>& vec, int size);
string getAnswer(string question);
void initCube(Vector<string>& vec, Grid<char>& grid, int gridColSize);
void playOfHuman(Grid<char>& grid, Lexicon& lex, Set<string>& usedWords);
bool canFindTheWord(Grid<char>& grid, string str, Vector <gridPoint>& points);
bool canFindTheWordRec(Grid<char>& grid, Vector <gridPoint>& points, string str, string sofar, gridPoint currPoint);
void implementChanges(Vector <gridPoint> & points, string str, Player player);
void playOfComputer (Grid<char>& grid, Lexicon& lex, Set<string>& usedWords);
void findTheWords(Grid<char>& grid, Lexicon& lex, Set<string>& usedWords, string sofar, gridPoint point, Vector <string>& computerWords, Vector <gridPoint> & points);
void putOutResults(Vector<string>& computerWords,Player player);
bool containsPoint(int i, int j, Vector<gridPoint> & points);
/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
	while(true){
		initGBoggle(gw);
		Vector <string> vec;
		Set <string> usedWords;
		Lexicon lex("EnglishWords.dat");
		initGame(vec);
		Grid <char> grid;
		if(vec.size() % 2 == 0){
			grid.resize(STANDART_GRID_SIZE, STANDART_GRID_SIZE);
			initCube(vec, grid, STANDART_GRID_SIZE);
		} else {
			grid.resize(BIG_BOGGLE_GRID_SIZE, BIG_BOGGLE_GRID_SIZE);
			initCube(vec, grid, BIG_BOGGLE_GRID_SIZE);
		}
		cout<<"Ok, take all the time you want and find all the words you can!  Signal that you're finished by entering an empty line."<<endl;
		playOfHuman(grid, lex, usedWords);
		playOfComputer(grid, lex, usedWords);
		string str = getAnswer("Would you like to play again?: ");
		if(str == "no"){
			break;
		}
	}
    return 0;
}
// * This void continues the game by searching all the other possible words.
void playOfComputer (Grid<char>& grid, Lexicon& lex, Set<string>& usedWords){
	Player player;
	player = COMPUTER;
	Vector <string> computerWords;
	Vector <gridPoint> points;
	string sofar = "";
	for(int i = 0; i < grid.numRows(); i++){
		for(int j = 0; j < grid.numCols(); j++){
			sofar += tolower(grid[i][j]);
			gridPoint point;
			point.y = i;
			point.x = j;
			points.add(point);
			findTheWords(grid, lex, usedWords, sofar, point, computerWords, points);
			sofar = sofar.substr(0, sofar.size() - 1);
			points.remove(points.size() - 1);
		}
	}
	putOutResults(computerWords, player);
}

// * This recursive void is designed to find all the remainig words on the board
void findTheWords(Grid<char>& grid, Lexicon& lex, Set<string>& usedWords, string sofar, gridPoint point, Vector <string>& computerWords, Vector <gridPoint> & points){
	if(lex.contains(sofar) && sofar.size() >= 4 && !usedWords.contains(sofar)){
		usedWords.add(sofar);
		computerWords.add(sofar);
	}
	if(!lex.containsPrefix(sofar)){
		return;
	}
	int row = point.y;
	int col = point.x;
	for(int i = row - 1; i <= row + 1; i++){
		for(int j = col - 1; j <= col + 1; j++){
			if(grid.inBounds(i, j) && !(i == row && j == col) && !containsPoint(i, j, points)){
				gridPoint newPoint;
				newPoint.y = i;
				newPoint.x = j;
				points.add(newPoint);
				sofar += tolower(grid[i][j]);
				findTheWords(grid, lex, usedWords, sofar, newPoint, computerWords, points);
				sofar = sofar.substr(0, sofar.size() - 1);
				points.remove(points.size() - 1);
			}
		}
	}
}

// * This void takes in the vector of words found by computer and adds it to the score.
void putOutResults(Vector<string>& computerWords,Player player){
	for(int i = 0; i < computerWords.size(); i++){
		recordWordForPlayer(computerWords[i], player);
	}
}

// * Function that allows user to enter words and play the game.
void playOfHuman(Grid<char>& grid, Lexicon& lex, Set<string>& usedWords){
	string str = getLine("Enter the word: ");
	Player player;
	player = HUMAN;
	while(str.size() != 0){
		lowerCharacters(str);
		if(str.size() >= 4){
			if(lex.contains(str)){
				if(!usedWords.contains(str)){
					Vector <gridPoint> points;
					if(canFindTheWord(grid, str, points)){
						usedWords.add(str);
						implementChanges(points, str, player);
					} else {
						cout<<"This word is not on the board."<<endl;
					}
				} else {
					cout<<"You have already guessed this word."<<endl;
				}
			} else {
				cout<<"This is not a valid english word."<<endl;
			}
		} else {
			cout<<"The word should have at least 4 characters."<<endl;
		}
		str = getLine("Enter the word: ");
	}
}
void implementChanges(Vector <gridPoint> & points, string str, Player player){
	recordWordForPlayer(str, player);
	for(int i = 0; i < points.size(); i++){
		highlightCube(points[i].y, points[i].x, true);
	}
	pause(1000);
	for(int i = 0; i < points.size(); i++){
		highlightCube(points[i].y, points[i].x, false);
	}
}
// * Wrapper function for the recursive function.
bool canFindTheWord(Grid<char>& grid, string str, Vector <gridPoint> & points){
	string sofar = "";
	for(int i = 0; i < grid.numRows(); i++){
		for(int j = 0; j < grid.numRows(); j++){
			gridPoint point;
			point.y = i;
			point.x = j;
			sofar += tolower(grid[i][j]);
			points.add(point);
			if(canFindTheWordRec(grid, points, str, sofar, point)){
				return true;
			}
			sofar = sofar.substr(0, sofar.size() - 1);
			points.remove(points.size() - 1);
		}
	}
	return false;
}
// * Recursive function to find the word given by user
bool canFindTheWordRec(Grid<char>& grid, Vector <gridPoint>& points, string str, string sofar, gridPoint currPoint){
	if(sofar == str){
		return true;
	}
	if(sofar[sofar.size() - 1] != str[sofar.size() - 1]){
		return false;
	}
	int row = currPoint.y;
	int col = currPoint.x;
	for(int i = row - 1; i <= row + 1; i++){
		for(int j = col - 1; j <= col + 1; j++){
			if(grid.inBounds(i, j) && !(i == row && j == col) && !containsPoint(i, j, points)){
				gridPoint newPoint;
				newPoint.y = i;
				newPoint.x = j;
				points.add(newPoint);
				sofar += tolower(grid[i][j]);
				if(canFindTheWordRec(grid, points, str, sofar, newPoint)){
					return true;
				}
				sofar = sofar.substr(0, sofar.size() - 1);
				points.remove(points.size() - 1);
			}
		}
	}
	return false;
}
// * This method checks if the given point is in the used points
bool containsPoint(int i, int j, Vector<gridPoint> & points){
	for(int a = 0; a < points.size(); a++){
		if(points[a].y == i && points[a].x == j){
			return true;
		}
	}
	return false;
}
// * Shuffles the cubes, according to it initializes the grid storing the info, and labels the cubes. 
void initCube(Vector<string>& vec, Grid<char>& grid, int gridColSize){
	for(int i = 0; i < vec.size(); i++){
		int x = randomInteger(i, vec.size() - 1);
		string str = vec[x];
		vec[x] = vec[i];
		vec[i] = str;
	}
	for(int i = 0; i < vec.size(); i++){
		string currStr = vec[i];
		int x = randomInteger(0, CUBE_N_SIDES - 1);
		char currChar = currStr[x];
		grid [(i/gridColSize)][(i%gridColSize)] = currChar;
	}
	for(int i = 0; i < grid.numRows(); i++){
		for(int j = 0; j < grid.numCols(); j++){
			labelCube(i, j, grid[i][j]);
		}
	}
}
// * This function lowers the characters of a string if necessary and is called after user answers the specified question.
void lowerCharacters(string& str){
	for(int i = 0; i < str.length(); i ++){
		str[i] = tolower(str[i]);
	}
}
// * This void takes in the input from the user and initializes the vector of cubes.
void initGame(Vector<string>& vec){
	welcome();
	string str = getAnswer("Would you like to read the instructions of the game?: ");
	if(str == "yes"){
		giveInstructions();
	}
	cout<<"You can choose standard Boggle (4x4 grid)"<<endl;
	cout<<"or Big Boggle (5x5)."<<endl;
	str = getAnswer("Would you like a Big Boggle?: "); 
	if(str == "yes"){
		drawBoard(BIG_BOGGLE_GRID_SIZE, BIG_BOGGLE_GRID_SIZE);
	} else {
		drawBoard(STANDART_GRID_SIZE, STANDART_GRID_SIZE);
	}
	string str2 = getAnswer("Would you like to configure the board yourself?: ");
	if(str == "yes"){
		if(str2 == "yes"){ 
			loadVectorByUser(vec, BIG_BOGGLE_CUBES_SIZE);
		}else{
			loadVector(vec, BIG_BOGGLE_CUBES_SIZE);
		}
	} else {
		if(str2 == "yes"){ 
			loadVectorByUser(vec, STANDARD_CUBES_SIZE);
		}else{
			loadVector(vec,  STANDARD_CUBES_SIZE);
		}
	}
}
//* General type of function where given a question only answer yes or no has to be returned.
string getAnswer(string question){
	string str = getLine(question);
	lowerCharacters(str);
	while(str != "yes" && str != "no"){
		cout<<"Please only enter yes or no. "<<endl;
		str = getLine(question);
	} 
	return str;
}
// *Loads a vector according the input by the user.
void loadVectorByUser(Vector<string>& vec, int size){
	string str;
	for(int i = 0; i < size; i++){
		str = getLine("Enter configuration of cube: ");
		vec.add(str);
	}
}
// *Loads a vector according to the given constant arrays.
void loadVector(Vector<string>& vec,  int size){
	if(size == BIG_BOGGLE_CUBES_SIZE){
		for(int i = 0; i < size; i++){
			vec.add(BIG_BOGGLE_CUBES[i]);
		}
		return;
	}
	for(int i = 0; i < size; i++){
		vec.add(STANDARD_CUBES[i]);
	}
}
/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */
void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}
