#include "Computer.h"

Computer::Computer(string name):Player(name){
	srand (time(NULL));
}
void Computer::makeSelection(int x){
	this->selection = this->selectionArray[rand() % 3];
}
