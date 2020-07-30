#include<iostream>
#include<string>
#include<fstream>
#include"Hangman.h"
#include "Design.h"

using namespace std; 

bool savedFile() // accesses 'save' file and determine whether there is a pre existing game. 
{
	int counter = 0; 
	string temp; 
	ifstream save("save.txt"); 
	while (getline(save, temp))
	{
		counter++; 
	}
	if (counter > 1)
	{
		return true; 
	}
	else
	{
		return false; 
	}
}

int fileSize(ifstream& file)//determine length file 
{
	int counter = 0; 
	string temp; 
	while (file >> temp)
	{
		counter++; 
	}
	file.close(); 
	return counter; 
}

void printTitle() // prints out title 
{
	cout << "      ______________________________________________________________" << endl;
	cout << "     |                                                              |" << endl;
	cout << "     |                __           ___    _    _   __               |" << endl;
	cout << "     |          |  | |  | |\\   |  /   \\  | \\  / | |  | |\\   |       |" << endl;
	cout << "     |          |__| |__| | \\  | |  __   |  \\/  | |__| | \\  |       |" << endl;
	cout << "     |          |  | |  | |  \\ | |    \\  |      | |  | |  \\ |       |" << endl;
	cout << "     |          |  | |  | |   \\|  \\___/  |      | |  | |   \\|       |" << endl;
	cout << "     |                                                              |" << endl;
	cout << "     |______________________________________________________________|" << endl;
	cout << endl << endl;
}

int main()
{

	// The hangman game is going to be played inside main.cpp with information supplemented by the 'Hangman' and 'Design' Classes
	// The game starts by printing the Title and setting certain variables to be used later. 

	printTitle();
	bool isSave = savedFile(), savedGame = false; // bool 'isSave' uses the savedFile() function
	int level, size, attempts, go;
	string guess, loop = "yes", used_letters; // string loop is set to keep going indefinitely

	if (isSave == false) // checks to see if a pre existing game exists , if not , start a new one by asking for a difficulty. 
	{
		cout << "     Choose a level: 1 - Easy     2 - Medium      3 - Hard" << endl;
		cin >> level;
		go = 0; 
	}
	else
	{
		// if a save exists, ask whether user would like to continue or start a new game 
		go = 1; 
		char cont;
		cout << endl << endl << "     Would you like to continue your game?" << endl;
		cout << "     y - yes        n - no" << endl;
		cin >> cont;
		while (loop == "yes")
		{
			if (cin.fail()) // handles unexpected variable type inputs 
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << endl << endl << "     Would you like to continue your game?" << endl;
				cout << "     y - yes        n - no" << endl;
				cin >> cont;
				continue;
			}
			if (cont == 'y') // continue old game
			{
				loop = "no";
				level = 1;
				size = 10;
				break; 
			}
			else if (cont == 'n') // start new game 
			{
				go = 0;
				system("CLS");
				isSave = false;
				cout << "     Choose a level: 1 - Easy     2 - Medium      3 - Hard" << endl;
				cin >> level;
				break; 
			}
			else // incase user does not provide either 'y' or 'n' as an input 
			{
				system("CLS"); 
				printTitle(); 
				cout << endl << endl << "     Would you like to continue your game?" << endl;
				cout << "     y - yes        n - no" << endl;
				cin >> cont;
			}
		}
	}
	


	ifstream words;
	while (loop == "yes") // This is where the majority of the game is played. 
	{
		
		if (cin.fail()) // handle unexpeced variable type inputs 
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "     \nInvalid value. Please Re-enter a number between 1 and 3\n";
			cout << "     Choose a level: 1 - Easy     2 - Medium      3 - Hard" << endl;
			cin >> level; 
			continue; 
		}

		// if / else-if statements based on user input to determine difficulty level and which text file to access

		if (level == 1) 
		{
			words.open("easy.txt");
			size = fileSize(words);
			break;
		}
		else if (level == 2)
		{
			words.open("medium.txt");
			size = fileSize(words);
			break;
		}
		else if (level == 3)
		{
			words.open("hard.txt");
			size = fileSize(words);
			break;
		}
		else
		{
			cout << "     Please Choose a number between 1 - 3" << endl;
			cout << "     Choose a level: 1 - Easy     2 - Medium      3 - Hard" << endl; 
			cin >> level; 
		}
	}
	words.close(); 
	///// ---------------------------------------

	Design newGame(level, size); // initiate game based on level 


	if (go == 0) // start a new game 
	{
		
		newGame.readFile(words);
		newGame.generateWord();
		attempts = newGame.getAttempts();
		newGame.getTheWord();
	}
	else if (go == 1) // open a saved game 
	{
		newGame.openSave(); 
		attempts = newGame.getAttempts(); 
	}

	while (attempts != 0) // "lives" which determine when to end the game
	{
		//=========================== Display functions from the class Design. These 4 functions will maintain the visuals throughout the game 
		system("CLS"); 
		printTitle(); 
		newGame.updateHangman(); 
		newGame.displayHangman();
		//============================
		cout << "     Guess a letter" << endl;
		cin >> guess;
		
		if (guess == "1") // Save and end the game if user inputs '1' 
		{
			savedGame = true; 
			newGame.saveGame(); 
			break; 
		}

		newGame.checkGuess(guess); // check user guess with the vectors 


		if (newGame.winner() == true) // if win condition is met, end game 
		{
			break;
		}

		attempts = newGame.getAttempts(); 
	}

	if (newGame.winner() == true) // message if player wins 
	{
		cout << "     Congratulations!!!! You Win!!" << endl; 
	}
	else if (newGame.winner() == false) // message if player runs out of lives 
	{
		system("CLS");
		printTitle(); 
		newGame.updateHangman(); 
		newGame.displayHangman(); 
		cout << "     You lose! Good Day Sir!" << endl;

	}

	if (savedGame == true) // message if player decides to save game 
	{
		system("CLS"); 
		printTitle(); 
		cout << endl << endl << "     Until next time!!" << endl; 
	}

	system("PAUSE");
	return 0;
}

