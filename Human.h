#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player
{
	public:
		Human(string);
		void makeSelection(int);
	protected:
};

#endif
