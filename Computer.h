#ifndef COMPUTER_H
#define COMPUTER_H
#include "Player.h"

#include <stdlib.h>
#include <time.h> 

class Computer : public Player
{
	public:
		Computer(string name);
		void makeSelection(int);
	protected:
};

#endif
