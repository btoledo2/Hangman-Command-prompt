#ifndef HANGMAN_H
#define HANGMAN_H

#include<iostream>
#include<string>
#include<fstream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <stdio.h>

using namespace std;

class Hangman
{

	bool win = false; 
	bool correct = false; 
	string difficulty; // set in constructor 
	string* words; //array with the randomized word 
	string theWord; //randomized word
	int size; //set in constructor for array size
protected:
	int life; // Determines what stage of the game the player is currently --> also determines how to update the hangman image
	int subtractor; // Operates in tangent with life to determine stage of game and hangman image display 
	int attempts; // set in constructor
	int wordLength; // length for loops
	vector<char> word; // store randomized word 
	vector<char> guessDisplay;  // store correct guesses by player
	vector<char> usedLetters; // store all guesses by player 
	
public:
	Hangman() {}; 
	Hangman(int level, int listLength);  // starts game
	void readFile(ifstream& inFile);	// replaces protected variables to intiate previously saved game
	void storeUsedLetters(char guess);  // used to add letters to vector usedLetters
	void generateWord();  // randomize a word to set vector word
	void checkGuess(string guess); // compares user input with the word, guessDisplay, and usedLetters vectors 
	void saveGame(); // store important information about game and ends it 
	void openSave(); // accesses saved game and replaces relevent information 
	int getAttempts() { return attempts;  } 
	string getDifficulty() { return difficulty;  } 
	string getTheWord() { return theWord;  } 
	bool winner(); // check if the win condition is met
	~Hangman() { delete[]words;  } // delete dynamic array words 





};

#endif