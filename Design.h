#ifndef DESIGN_H
#define DESIGN_H

#include "Hangman.h"
using namespace std; 

class Design : public Hangman
{
private:
	char** hungman; // 2d array depicting Hangman visuals
	int rows = 13; //dimensions of 2d array 
	int columns = 45;// dimenstions of 2d array 

public:
	Design() {}; 
	Design(int level, int listLength); // sets information for visual representation of game
	void displayHangman(); // cout the hangman visual
	void displayWord();	// cout the array of correct user guesses 
	void displayUsedLetters(); // cout array of all user guesses 
	void updateHangman(); // updates hangman visual 
	~Design(); 


}; 

#endif


//protected 
//int attempts; // set in constructor
//int wordLength;
//vector<char> word;
//vector<char> guessDisplay;
//vector<char> usedLetters;

/*                                            
1				________
2			   |		|
3			   |		|
4			  (	)		|
5			   |		|
6			  /|\		|
7			 / | \		|
8			   |		|
9			  / \		|
10			 /	 \		|
11						|
12						|
13	=========================================
*/
