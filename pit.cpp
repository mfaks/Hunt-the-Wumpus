/******************************************************
** Program: pit.cpp
** Author: Muhammad Faks
** Description: Inhereted polymorphically from event class
** Input: n/a
** Output: Uses polymorphism to output the pit precept and enounter message
******************************************************/

#include <iostream>
#include <string>
#include "pit.h"

using namespace std;

/*********************************************************************
** Function: Pit()
** Description: Default Constructor
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: New Pit object is created
*********************************************************************/

Pit::Pit() {
	
}

/*********************************************************************
** Function: precept()
** Description: Contains the pit precept
** Parameters: N/A
** Pre-Conditions: Player position is adjacent to the pit
** Post-Conditions: Outputs pit precent
*********************************************************************/

void Pit::precept() {
	cout << "\nYou feel a cool breeze..." << endl; 
}

/*********************************************************************
** Function: encounter()
** Description: Contains the pit encounter message
** Parameters: N/A
** Pre-Conditions: Player is in the same room as the pit
** Post-Conditions: Outputs pit enounter message
*********************************************************************/

void Pit::encounter() {
	cout << "\nUh oh! You fell into a pit and died :( " << endl; 
}

/*********************************************************************
** Function: event_letter()
** Description: Returns the event letter associated with the event
** Parameters: N/A
** Pre-Conditions: Called when specificing event
** Post-Conditions: Returns pit character
*********************************************************************/

char Pit::event_letter() {
	return 'P'; 
}
