/******************************************************
** Program: wumpus.h
** Author: Muhammad Faks
** Date: 11/19/2022
** Description: Inhereted polymorphically from event class
** Input: n/a
** Output: Uses polymorphism to output the wumpus precept and enounter message
******************************************************/

#ifndef WUMPUS_H
#define WUMPUS_H

#include <iostream>
#include <string>

#include "event.h"

using namespace std;

class Wumpus : public Event {
	protected:
	
	public:
		Wumpus(); //default constructor
		void precept(); //precept function
		void encounter(); //encouter function
		char event_letter(); //designating event letter function 

};

#endif
