#include "Player.h"

Player::Player(string name){
	this->name = name;
	this->wins = 0;
	this->losses = 0;
}
void Player::operator ++(int x){
	this->wins++;
}
void Player::operator --(int x){
	this->losses++;
}
void Player::displayData(){
	system("cls");
	cout<<"player's name: "<<this->name<<endl;
	cout<<"player's wins: "<<this->wins<<endl;
	cout<<"player's losses: "<<this->losses<<endl<<endl;
}
string Player::getSelection(){
	return this->selection;
}
string Player::getName(){
	return this->name;
}
int Player::getWins(){
	return this->wins;
}
int Player::getLosses(){
	return this->losses;
}
