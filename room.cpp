
/******************************************************
** Program: room.cpp
** Author: Muhammad Faks
** Description: Implementaion file for room class
** Input: Accepts room dimensions and event information
** Output: Constructs rooms and manages events in the rooms
******************************************************/

#include <iostream>
#include <string>
#include "room.h"

using namespace std;

/*********************************************************************
** Function: Room()
** Description: Default Constructor
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: New room object is created
*********************************************************************/

Room::Room() {
	event = NULL;
	rows = 0, columns = 0;
	event_exists = false; 
}

/*********************************************************************
** Function: Room()
** Description: Non Default Constructor
** Parameters: int r, int c
** Pre-Conditions: Parameters are inputted
** Post-Conditions: New cave object is created based on the dimension of rooms
*********************************************************************/

Room::Room(int r, int c) {
	rows = r, columns = c; 
	event = NULL;
	event_exists = false; 
}

/*********************************************************************
** Function: get_rows()
** Description: Gets size of rows
** Parameters: N/A
** Pre-Conditions: Rows exists
** Post-Conditions: Returns size of rows
*********************************************************************/

int Room::get_rows() {
	return rows;
}

/*********************************************************************
** Function: get_columns()
** Description: Gets size of columns
** Parameters: N/A
** Pre-Conditions: Columns exists
** Post-Conditions: Returns size of columns
*********************************************************************/

int Room::get_columns() {
	return columns;
}

/*********************************************************************
** Function: get_event()
** Description: Gets event object
** Parameters: N/A
** Pre-Conditions: Event object exists
** Post-Conditions: Returns event object
*********************************************************************/

Event* Room::get_event() {
	return event;
}

/*********************************************************************
** Function: get_event_check()
** Description: Gets the status on if an event exists in the room
** Parameters: N/A
** Pre-Conditions: Event exists in the room
** Post-Conditions: Returns event in the room
*********************************************************************/

bool Room::get_event_check() {
	return event_exists;
}

/*********************************************************************
** Function: set_event()
** Description: Sets an event in an empty room
** Parameters: N/A
** Pre-Conditions: Event must exist and room must be empty
** Post-Conditions: Sets event in the room
*********************************************************************/

void Room::set_event(Event* e) {
	event = e;
	event_exists = true; 
}

/*********************************************************************
** Function: replace_event()
** Description: Clears the status of the event in an old room to create a new event
** Parameters: N/A
** Pre-Conditions: Old event and new event exist
** Post-Conditions: Sets the status of the new event to the old event
*********************************************************************/

bool Room::replace_event(bool new_event) {
	event_exists = new_event; 
}

/*********************************************************************
** Function: ~Room()
** Description: Destructor *BIG 3*
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: The room objects are deleted if they are allocating heap
*********************************************************************/

Room::~Room() {
	if (event != NULL) {
		delete event;
		event = NULL;
	}
}
