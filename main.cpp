//abe mused
//this is a rock paper scissors game
#include <iostream>
#include<fstream>
#include <stdio.h>
#include <conio.h>
#include<vector>

#include "Player.h"
#include "Human.h"
#include "Computer.h"
using namespace std;
void getNamesOfPlayers(string&, string&);
void writeDataToFile(Player, Player);

template<class Base, class T>
inline bool instanceof(const T*) {
   return is_base_of<Base, T>::value;
}//i made this template to figure out wether the player is a human or a computer
void validate(int upperLimit, int lowerLimit, int &number){
	while(number > upperLimit || number < lowerLimit){
		cout<<"please enter a number between "<<lowerLimit<<" and "<<upperLimit<<":";
		cin>>number;
			if (cin.fail()){
				cin.clear();
				cin.ignore(10, '\n');
			}	
	}
}//i created this method to validate data throughout the program
int determineWinner(string firstSelection, string secondSelection){
	if(firstSelection == secondSelection)
	return 3;
	if(firstSelection == "rock" && secondSelection == "scissors")
	return 1;
	if(firstSelection == "paper" && secondSelection == "rock")
	return 1;
	if(firstSelection == "scissors" && secondSelection == "paper")
	return 1;
	return 2;
}//returning 3 means it's a tie, returning 1 or 2 means that's the number of the player who won 

template<class player, class otherPlayer> //made this a template sos it can take humans and computers
void playGame(player playerOne, otherPlayer playerTwo){
	
	int selectionIndex, continuePlaying;
	
	while(1){
		playerOne.displayData();
		if(instanceof<Human>(&playerOne)){
			cout<<"please make a selection:"<<endl;
			for(int i = 0; i < 3; i++){
				cout<<i+1<<") "<<playerOne.selectionArray[i]<<endl;
			}
			cin>>selectionIndex;
			validate(3,1,selectionIndex);
			
			playerOne.makeSelection(selectionIndex);
		} else {
			playerOne.makeSelection(0);
		} // if player one is human i'll ask them to make a selection, otherwise a selection is made randomly 
		
		cout<<"press any button to continue..."<<endl<<endl;
		getch();
		
		playerTwo.displayData();
		if(instanceof<Human>(&playerTwo)){
			cout<<"please make a selection:"<<endl;
			for(int i = 0; i < 3; i++){
				cout<<i+1<<") "<<playerTwo.selectionArray[i]<<endl;
			}
			cin>>selectionIndex;
			validate(3,1,selectionIndex);
			
			playerTwo.makeSelection(selectionIndex);
		} else {
			playerTwo.makeSelection(0);
		}// if player two is human i'll ask them to make a selection, otherwise a selection is made randomly
		
		cout<<"press any button to reveal the winner..."<<endl<<endl;
		getch();
		cout<<playerOne.getName()<<" chose "<<playerOne.getSelection()<<" and ";
		cout<<playerTwo.getName()<<" chose "<<playerTwo.getSelection()<<" so the winner is ";
		switch(determineWinner(playerOne.getSelection(), playerTwo.getSelection())){
		//sending selections to determineWinner()
			case 1:
				cout<<playerOne.getName()<<", congrats!"<<endl;
				playerOne++;
				playerTwo--;
				break;
			case 2:
				cout<<playerTwo.getName()<<", congrats!"<<endl;
				playerTwo++;
				playerOne--;
				break;
			case 3:
				cout<<"no one. It is a tie!"<<endl;
				break;
			default:
				cout<<"we faced a problem figuring out who's the winner of this round, we apologize."<<endl;
		}
		cout<<endl<<"press 0 to quit playing or any other button to continue playing... "<<endl;
		continuePlaying = getch();
		if(continuePlaying == 48){ //is the user presses 0 the game is over and they're asked whether they want to create a file
			cout<<"thanks for playing!"<<endl<<endl;
			cout<<"press 0 to write the data of this game to file or anything else to not do that..."<<endl;
			continuePlaying = getch();
				if(continuePlaying == 48)
				writeDataToFile(playerOne, playerTwo);
			break;	
		}	
	}
}

int main(int argc, char** argv) {
	int gameMode;
	string firstPlayerName, secondPlayerName;

	cout<<"select how you want to play:"<<endl;
	cout<<"\t1) player vs player"<<endl;
	cout<<"\t2) player vs computer"<<endl;
	cout<<"\t3) computer vs computer"<<endl;
	cin>>gameMode;
	validate(3,1,gameMode);
	getchar();
	switch(gameMode){
	//based on the user's entry, i'll call the appropriate functions and create the appropriate objects 
		case 1:
			getNamesOfPlayers(firstPlayerName, secondPlayerName);
				cout<<"press any button to start the game..."<<endl;
				getch();
			playGame(Human(firstPlayerName),Human(secondPlayerName));
			break;
		case 2:
			secondPlayerName = "computer";
			getNamesOfPlayers(firstPlayerName, secondPlayerName);
				cout<<"press any button to start the game..."<<endl;
				getch();
			playGame(Human(firstPlayerName),Computer("computer"));
			break;
		case 3:
			playGame(Computer("computer one"),Computer("computer two"));
			break;
		default:
			cout<<"error, invalid selection for game mode"<<endl;
			break;
	}
	return 0;
}

void getNamesOfPlayers(string &firstPlayerName, string &secondPlayerName){
	
	int choice;	
	cout<<"would you like to (1) enter the names manually or (2) import the names from a file? ";
	cin>>choice;
	validate(2,1,choice);
	
	if (choice == 1){//if the user chose 1 they'll be asked to enter the name(s)
		getchar();
		cout<<"enter the name of the first player: ";
		getline(cin,firstPlayerName);
		if (secondPlayerName != "computer"){
		//if the name of the second player is "computer" that means it's a Computer object and the user won't be asked to enter a name for it 
			cout<<"enter the name of the second player: ";
			getline(cin,secondPlayerName);
		}
	} else {
	string temp;// to store the names before adding them to the vector of names
	int playerNameIndex; 
	vector<string> playersNames; 
	ifstream inputFile("playersNames.txt");// could've asked the user for that but it's unnecessary
		if(inputFile.fail()){// if the file can't be opened i just assign names to the players
			cout<<"error, couldn't open file";
			firstPlayerName = "the first player";
			secondPlayerName = "the second player";
		}else{
			while(!inputFile.eof()){
				inputFile >> temp;
				playersNames.push_back(temp);
			}
			for(int i = 0 ; i < playersNames.size(); i++){
				cout<<"\t"<<i+1<<") "<<playersNames.at(i)<<endl;
			}
			cout<<"Enter the number of the name of the first player from the list above: ";
			cin>>playerNameIndex;
			validate(playersNames.size(),1,playerNameIndex);
			firstPlayerName = playersNames.at(playerNameIndex-1);
			
			if(secondPlayerName != "computer"){
			//if the name of the second player is "computer" that means it's a Computer object and it's automatically named computer 
				cout<<"Enter the number of the name of the second player from the list above: ";
				cin>>playerNameIndex;
				validate(playersNames.size(),1,playerNameIndex);
				secondPlayerName = playersNames.at(playerNameIndex-1);
			}
		}
	}
}

void writeDataToFile(Player playerOne, Player playerTwo){
	ofstream outputFile("output.txt");
	if(playerOne.getName() != "computer one"){
		outputFile<<"player's name: "<<playerOne.getName()<<"\twins: "<<playerOne.getWins()<<"\t\tlosses: "<<playerOne.getLosses()<<endl;
			if(playerTwo.getName() != "computer")
			outputFile<<"player's name: "<<playerTwo.getName()<<"\twins: "<<playerTwo.getWins()<<"\t\tlosses: "<<playerTwo.getLosses()<<endl;
		cout<<"data written to file successfully."<<endl;
	}//this function only writes the data of human players
	outputFile.close();
}
