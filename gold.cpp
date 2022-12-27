/******************************************************
** Program: gold.cpp
** Author: Muhammad Faks
** Description: Inhereted polymorphically from event class
** Input: n/a
** Output: Uses polymorphism to output the gold precept and enounter message
******************************************************/

#include <iostream>
#include <string>

#include "gold.h"

using namespace std;

/*********************************************************************
** Function: Gold()
** Description: Default Constructor
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: New Gold object is created
*********************************************************************/

Gold::Gold() {

}

/*********************************************************************
** Function: precept()
** Description: Contains the gold precept
** Parameters: N/A
** Pre-Conditions: Player position is adjacent to the gold
** Post-Conditions: Outputs gold precent
*********************************************************************/

void Gold::precept() {
	cout << "\nYou see a glimmer nearby..." << endl;	
}

/*********************************************************************
** Function: encounter()
** Description: Contains the gold encounter message
** Parameters: N/A
** Pre-Conditions: Player is in the same room as the gold
** Post-Conditions: Outputs gold enounter message
*********************************************************************/

void Gold::encounter() {
	cout << "\nCongratulations you have found the gold!" << endl;
}

/*********************************************************************
** Function: event_letter()
** Description: Returns the event letter associated with the event
** Parameters: N/A
** Pre-Conditions: Called when specificing event
** Post-Conditions: Returns gold character
*********************************************************************/

char Gold::event_letter() {
	return 'G'; 
}
