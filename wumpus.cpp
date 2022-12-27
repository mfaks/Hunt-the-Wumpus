/******************************************************
** Program: wumpus.cpp
** Author: Muhammad Faks
** Description: Inhereted polymorphically from event class 
** Input: n/a
** Output: Uses polymorphism to output the wumpus precept and enounter message
******************************************************/

#include <iostream>
#include <string>
#include "wumpus.h"

using namespace std;

/*********************************************************************
** Function: Wumpus()
** Description: Default Constructor
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: New Wumpus object is created
*********************************************************************/

Wumpus::Wumpus() {

}

/*********************************************************************
** Function: precept()
** Description: Contains the wumpus precept
** Parameters: N/A
** Pre-Conditions: Player position is adjacent to the wumpus
** Post-Conditions: Outputs wumpus precent
*********************************************************************/

void Wumpus::precept() {
	cout << "\nYou smell a terrible stench..." << endl;
}

/*********************************************************************
** Function: encounter()
** Description: Contains the wumpus encounter message
** Parameters: N/A
** Pre-Conditions: Player is in the same room as the wumpus
** Post-Conditions: Outputs wumpus enounter message
*********************************************************************/

void Wumpus::encounter() {
	cout << "\nYou walked into the Wumpus's room. The Wumpus wakes up and eat you. You are dead :( " << endl; 
}

/*********************************************************************
** Function: event_letter()
** Description: Returns the event letter associated with the event
** Parameters: N/A
** Pre-Conditions: Called when specificing event 
** Post-Conditions: Returns wumpus character
*********************************************************************/

char Wumpus::event_letter() {
	return 'W'; 
}



