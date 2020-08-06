#include "Design.h"



Design::Design(int level, int listLength) :Hangman(level, listLength)  // sets information for visual representation of game
{
	hungman = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		hungman[i] = new char[columns];
	}



	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			hungman[i][j] = ' ';
		}
	}

	hungman[1][14] = '|';
	hungman[2][14] = '|';
	for (int i = 1; i < 12; i++)
	{
		hungman[i][23] = '|';
	}
	for (int i = 15; i < 23; i++)
	{
		hungman[0][i] = '_';
	}
	for (int i = 0; i < columns; i++)
	{
		hungman[12][i] = '=';
	}
}

void Design::displayHangman()// cout the hangman visual
{
	int i; 
	for (i = 0; i < rows; i++)
	{
		cout << "     "; 
		for (int j = 0; j < columns; j++)
		{
			cout << hungman[i][j]; 
		}
		
		if (i == 5)
		{
			cout << "     Used Letters";
		}
		if (i == 6)
		{
			cout << "     "; 
			displayUsedLetters(); 
		}

		if (i == 3)
		{
			cout << "     "; 
			displayWord(); 
		}
		if (i == 10)
		{
			cout << "     Press '1' to save game for later"; 
		}
		cout << endl;
	}

	cout << endl; 
}

void Design::displayUsedLetters()// cout array of all user guesses 
{
	for (unsigned i = 0; i < usedLetters.size(); i++)
	{
		cout << usedLetters.at(i) << " "; 
	}
}

void Design::displayWord()	// cout the array of correct user guesses 
{
	for (int i = 0; i < wordLength; i++)
	{
		cout << guessDisplay.at(i) << " "; 
	}
}

void Design::updateHangman()// updates hangman visual 
{


	if (life <= 30) // head
	{
		hungman[3][13] = '(';
		hungman[3][15] = ')';
	}
	if (life <= 25) // neck
	{
		hungman[4][14] = '|';
	}
	if (life <= 20) // left arm
	{
		hungman[5][13] = '/';
		hungman[6][12] = '/';
	}
	if (life <= 15) // right arm
	{
		hungman[5][15] = '\\';
		hungman[6][16] = '\\'; 
	}
	if (life <= 10) // body
	{
		hungman[5][14] = '|';
		hungman[6][14] = '|';
		hungman[7][14] = '|';
	}
	if (life <= 5) // left leg
	{
		hungman[8][13] = '/';
		hungman[9][12] = '/';
	}
	if (life == 0) // right leg
	{
		hungman[8][15] = '\\';
		hungman[9][16] = '\\';
	}

}


	Design::~Design() // delete dynamic 2d array 
{
	for (int i = 0; i < rows; i++)
	{
		delete[] hungman[i];
	}
	delete[] hungman;
}
