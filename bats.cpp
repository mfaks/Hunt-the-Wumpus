/******************************************************
** Program: bats.cpp
** Author: Muhammad Faks
** Description: Inhereted polymorphically from event class
** Input: n/a
** Output: Uses polymorphism to output the bats precept and enounter message
******************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "bats.h"

using namespace std;

/*********************************************************************
** Function: Bats()
** Description: Default Constructor
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: New Bats object is created
*********************************************************************/

Bats::Bats() {

}

/*********************************************************************
** Function: precept()
** Description: Contains the bat precept
** Parameters: N/A
** Pre-Conditions: Player position is adjacent to the bat 
** Post-Conditions: Outputs bat precent
*********************************************************************/

void Bats::precept() {
	cout << "\nYou hear wings flapping...";
}

/*********************************************************************
** Function: encounter()
** Description: Contains the bats encounter message
** Parameters: N/A
** Pre-Conditions: Player is in the same room as the bat
** Post-Conditions: Outputs bats enounter message
*********************************************************************/

void Bats::encounter() {
	cout << "\nYou encounter bats in the room!\nYou are carried to a random room" << endl; 
}


/*********************************************************************
** Function: event_letter()
** Description: Returns the event letter associated with the event
** Parameters: N/A
** Pre-Conditions: Called when specificing event
** Post-Conditions: Returns bat character
*********************************************************************/

char Bats::event_letter() {
	return 'B'; 
}
