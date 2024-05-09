#include "Game.h"
#include "Board.h"
#include "Solve.h"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

string instruction()
{
	string ans;
	do
	{
		system("cls");
		cout << "\t\t\tDo you want to show the instruction?\n\t\t\t"
			<< "(y or Y for continue, n or N for exit) : ";
		cin >> ans;
		if (ans == "y" || ans == "Y" || ans == "n" || ans == "N")
		{
			break;
		}

		cout << "\t\t\t--> You typed the wrong choice. Type again!\n";
		system("pause");

	} while (ans != "y" && ans != "Y");

	if (ans == "Y" || ans == "y")
	{
		// show the instruction
		cout << "\n\n";
		cout << "\t\t\t _____________________________________________________________ \n";
		cout << "\t\t\t|                                                             |\n";
		cout << "\t\t\t|                        How to play Sudoku                   |\n";
		cout << "\t\t\t|                                                             |\n";
		cout << "\t\t\t|_____________________________________________________________|\n\n";

		cout << "\t\t\t|  1. You will solve the puzzle by type the number from 1 - N |\
			\n\t\t\t|     (N is the size of the board).                           |\n";
		cout << "\t\t\t|  2. The condition to win the game that each nunber can show |\
			\n\t\t\t|     one time in its row, column and its box.                |\n";
		cout << "\t\t\t|  3. To type the number you will type a line following rule  |\
			\n\t\t\t|     pos of row( )pos of col( )number to fill.               |\n";
		cout << "\t\t\t|  4. Type \"sovle\" to solve the puzzle when you get stuck.    |\n";
		cout << "\t\t\t|  5. Type \"clear\" to clear all the number you type.          |\n";
		cout << "\t\t\t|  6. Type \"over\" to end the game.                            |\n\n";
	}
	
	ans = "";
	do
	{
		cout << "\n\t\t\tAre you ready for the game?\n\t\t\t"
			<< "(y or Y for continue, n or N for exit) : ";
		char ch = cin.peek();
		while (isspace(ch))
		{
			cin.ignore();
			ch = cin.peek();
		}
		cin >> ans;
		if (ans == "y" || ans == "Y" || ans == "n" || ans == "N")
		{
			break;
		}

		cout << "\t\t\t--> You typed the wrong choice. Type again!\n";
		system("pause");

	} while (ans != "y" && ans != "Y");
	
	return ans;

}

void playGame(int size)
{
	string playOrNot = instruction();

	string user_entry;			// for user typing
	int input_int[3];			// contain user typing
	bool solveSuccess = false;

	// for checking input every time you input
	regex rgx("[0-9]{1,}");		// meaning appear int in 1 - 9 at least 1 time and number will begin
	smatch match;

	if (playOrNot == "n" || playOrNot == "N")
	{
		return;
	}

	playOrNot = "";
	
	system("cls");
	cout << "\n\n\n";
	cout << "\t\t\t _____________________________________________________________ \n";
	cout << "\t\t\t|                                                             |\n";
	cout << "\t\t\t|                      Welcome to Sudoku                      |\n";
	cout << "\t\t\t|                                                             |\n";
	cout << "\t\t\t|_____________________________________________________________|\n\n";

	Board* board = generateBoard(size);
	

	while (!solveSuccess)
	{
		cout << "\n\n";
		board->printPuzzle();

		if (board->checkPuzzle())
		{
			cout << "\n\n\t\t\tYOU WONT THE GAME!! CONGRATULATION!!!!";
			solveSuccess = true;
			break;
		}
		clearWhiteSpace();
		cout << "\n\t\t\t" << "Enter: ";
		getline(cin, user_entry);
		//cout << "You typed " << user_entry << endl;

		// if you type solve
		if (user_entry == "solve" || user_entry == "Solve")
		{
			if (solve(board, 0, 0)) {
				cout << "\t\t\t--> The puzzle was solved\n\n";
				board->printPuzzle();
				solveSuccess = true;
				break;
			}
			else
			{
				cout << "\t\t\tThe puzzle couldn't be solved\n\n";
				continue;		// turn to new loop 
								// use clear to delete all the number you typed
								// or try to change some position
								// or over to end this game
			}
		}

		if (user_entry == "clear" || user_entry == "Clear") {
			board->clearPuzzle();
			continue;
		}

		// if you want to end the game
		if (user_entry == "over" || user_entry == "Over")
		{
			return;
		}

		// if you don't enter 3 word above, start seperate the user enter into array
		int count = 0;
		for (sregex_iterator i = sregex_iterator(user_entry.begin(),
			user_entry.end(), rgx);
			i != sregex_iterator();
			++i)
		{
			smatch m = *i;
			input_int[count] = stoi(m.str());
			++count;
		}

		// check if the value input is possible
		bool invalid = false;
		for (size_t i = 0; i < 3; i++)
		{
			if (!board->inBounds(input_int[i])) {
				invalid = true;
				break;
			}
		}
		if (invalid)
		{
			cout << "\n\n\t\t\t--> You need to entered number in range 1 to " << board->getSize() << endl;
			continue;		// come to new loop to type new command
		}
		
		for (size_t i = 0; i < 3; i++)
		{
			cout << "Input " << i + 1 << input_int[i] << endl;
		}
		if (board->possibleUser(input_int[0] - 1, input_int[1] - 1, input_int[2]) == true)
		{
			// check if this slot is immutable or not
			if (board->checkImmutable(input_int[0] - 1, input_int[1] - 1))
			{
				cout << "\n\t\t\t--> This slot is immutable";
			}
			else
			{
				board->assignValue(input_int[0] - 1, input_int[1] - 1, input_int[2]);
			}
		}
		else
		{
			cout << "\n\t\t\t--> This slot is impossible";
		}

		// reset input_int for sure
		for (int i = 0; i < 3; i++)
		{
			input_int[i] = 0;
		}

	}
		
	
}

void clearWhiteSpace()
{
	char ch = cin.peek();
	while (isspace(ch))
	{
		cin.ignore();
		ch = cin.peek();
	}
}
