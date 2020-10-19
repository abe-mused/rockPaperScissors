#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
using namespace std;

class Player
{
	protected:
		string name, selection;
		int wins, losses;
	public:
		string selectionArray[3] = {"rock", "paper", "scissors"};
		Player(string );
		void operator++(int);
		void operator--(int);
		string getSelection();
		string getName();
		int getWins();
		int getLosses();
		void displayData();
};

#endif
