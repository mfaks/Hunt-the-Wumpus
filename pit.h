/******************************************************
** Program: pit.h
** Author: Muhammad Faks
** Description: Inhereted polymorphically from event class
** Input: n/a
** Output: Uses polymorphism to output the pit precept and enounter message
******************************************************/

#ifndef PIT_H
#define PIT_H

#include <iostream>
#include <string>
#include "event.h"

using namespace std;

class Pit : public Event { //inhereted from event class 
	protected:
	
	public:
		Pit(); //default constructor
		void precept(); //precept function
		void encounter(); //encounter function
		char event_letter(); //designates event letter 
};

#endif
