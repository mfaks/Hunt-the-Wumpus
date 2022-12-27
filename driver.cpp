/******************************************************
** Program: driver.cpp
** Author: Muhammad Faks
** Description: Driver file for Hunt the Wumpus adventure game
** Input: Cave dimensions, direction to move, direction to fire an arrow, restart game with the same settings, brand new position
** Output: Instructions, rooms, precepts, encounters, number of arrows, status of arrows after firing 
******************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "game.h"

using namespace std;

int main() {

	srand(time(NULL)); 
	string new_round;
	int new_round_value = -1;
	Game g; //class game to begin the game
	
	do {
		g.play_game(); //function that runs the game
		cout << "\nWould you like to play a brand new round? Enter '0' for no or '1' for yes: " ; //prompts for hard reset 
		cin >> new_round;
		g.string_to_int(new_round, new_round_value); //converts the string input into an integer for error handling 
	
		while (g.is_int(new_round) == false && new_round_value != 0 && new_round_value != 1) { //error handling for invalid input
			cout << "\n\nInvalid input! Would you like to play a new round? Enter any integer for no or '1' for yes: ";
			cin >> new_round;
			g.string_to_int(new_round, new_round_value);
		}
	} while (g.is_int(new_round) == true && new_round_value == 1); //runs again with new settings if the user enters a valid input 
	
	return 0; 
}
