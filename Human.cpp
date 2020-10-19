#include "Human.h"

Human::Human(string name):Player(name){
	
}
void Human::makeSelection(int index){
	this->selection = this->selectionArray[index-1];
}
