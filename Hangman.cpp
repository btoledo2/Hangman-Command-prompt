#include "Hangman.h"


Hangman::Hangman(int level, int listLength)  // starts game
{
	
	if (level == 1)
	{
		attempts = 7; 
		difficulty = "easy.txt"; 
	}
	else if (level == 2)
	{
		attempts = 7; 
		difficulty = "medium.txt"; 
	}
	else if (level == 3)
	{
		attempts = 5;
		difficulty = "hard.txt"; 
	}
	size = listLength;
	words = new string[size]; 

	life = 35; 
	if (attempts == 7) { subtractor = 5; }
	else { subtractor = 7; }


}

void Hangman::readFile(ifstream& inFile) // replaces protected variables to intiate previously saved game
{
	inFile.open(difficulty); 
	for (int i = 0; i < size; i++)
	{
		inFile >> words[i]; 
	}
	inFile.close(); 
}

void Hangman::generateWord()// randomize a word to set vector word
{

	srand(time(0));
	int r = (rand() % size); 

	theWord = words[r]; 
	 

	wordLength = theWord.length();

	word.resize(wordLength); 
	guessDisplay.resize(wordLength); 

	for (int i = 0; i < wordLength; i++)
	{
		word.at(i) = theWord[i];
	}

	for (int i = 0; i < wordLength; i++)
	{
		guessDisplay.at(i) = '_';
	}
	
}


void Hangman::storeUsedLetters(char guess) // used to add letters to vector usedLetters
{

	usedLetters.push_back(guess); 
	 
}


void Hangman::checkGuess(string guess) // compares user input with the word, guessDisplay, and usedLetters vectors 
{
	
	if (guess.length() > 1)
	{
		if (guess == theWord)
		{
			win = true; 
		}
		else
		{
	
			attempts--; 
			life -= subtractor; 
		}
	}
	else // COMPARE WORD WITH ARRAY 
	{
		
		correct = false; 
		char temp = guess[0]; 
		
		for (int i = 0; i < wordLength; i++)
		{

			if (temp == theWord[i])
			{
				guessDisplay.at(i) = guess[0];  
				correct = true; 

			}
		}


		if (usedLetters.size()== 0)
		{
			
			if (correct == false)
			{
				cout << "     Guess is wrong" << endl;
				attempts--;
				life -= subtractor;

			}
			this->storeUsedLetters(guess[0]); // dont repeat letters 
		}
			

		for (unsigned i = 0; i < usedLetters.size(); i++)
		{
			if (guess[0] == usedLetters.at(i))
			{
				break; 
			}
			if (guess[0] != usedLetters.at((usedLetters.size() - 1)))
			{
				if (correct == false)
				{
					cout << "     Guess is wrong" << endl;
					attempts--;
					life -= subtractor;

				}
				this->storeUsedLetters(guess[0]); // dont repeat letters 
			}
		}

		
	}


}


bool Hangman::winner()  // check if the win condition is met
{
	bool checker = false; 

	for (int i = 0; i < wordLength; i++)
	{
		if (guessDisplay.at(i) == theWord[i])
		{
		
			checker = true; 
		}
		else if (guessDisplay.at(i) != theWord[i])
		{
			checker = false; 
			break; 
		}
	}

	if (checker == true)
	{
		return true; 
	}
	return win;
}

void Hangman::saveGame() // store important information about game and ends it 
{
	remove("save.txt"); 

	ofstream save("save.txt"); 

	save << attempts << endl;
	save << subtractor << endl;
	save << life << endl;
	save << wordLength << endl;
	save << theWord << endl;  //  Word
	for (int i = 0; i < wordLength; i++)
	{
		save << guessDisplay.at(i); 
	}
	save << endl; 
	for (unsigned i = 0; i < usedLetters.size(); i++)
	{
		save << usedLetters.at(i); 
	}

	save.close(); 
}

void Hangman::openSave()// accesses saved game and replaces relevent information 
{
	

	string guess_display; 
	string used_letters; 
	ifstream save("save.txt"); 

	save >> attempts >> subtractor >> life >> wordLength; 
	save >> theWord >> guess_display >> used_letters;

	word.resize(wordLength); 
	guessDisplay.resize(guess_display.length());
	usedLetters.resize(used_letters.length()); 

	
	for (int i = 0; i < wordLength; i++)
	{
		

		cout << theWord[i] << endl; 
		word.at(i) = theWord[i]; 
	}

	for (int i = 0; i < guess_display.length(); i++)
	{
		guessDisplay.at(i) = guess_display[i]; 
	}

	for (int i = 0; i < used_letters.length(); i++)
	{
		usedLetters.at(i) = used_letters[i]; 
	}

	save.close(); 
}
