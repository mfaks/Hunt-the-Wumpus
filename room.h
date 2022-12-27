
/******************************************************
** Program: room.h
** Author: Muhammad Faks
** Description: Header file for room class
** Input: Accepts room dimensions and event information
** Output: Constructs rooms and manages events in the rooms 
******************************************************/

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include "event.h"

using namespace std;

class Room {

	protected:
		Event* event; //for the event in a specific room  
		int rows, columns; //rows and columns of the board 
		bool event_exists; //checking if an event exists in a room 		

	public:
		Room(); //default constructor
		Room(int, int); //nondefault constructor 

		int get_rows(); //rows accessor 
		int get_columns(); //columns accessor
		
		Event* get_event(); //event accessor
		bool get_event_check(); //event_exists accessor
		void set_event(Event*); //event mutator
		bool replace_event(bool); //replace event mutator

		~Room(); //room destructor 
};

#endif
