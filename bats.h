/******************************************************
** Program: bats.h
** Author: Muhammad Faks
** Description: Inhereted polymorphically from event class
** Input: n/a
** Output: Uses polymorphism to output the bats precept and enounter message
******************************************************/

#ifndef BATS_H
#define BATS_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "event.h"

using namespace std;

class Bats : public Event { //inhereted from event class 
	protected:

	public:
		Bats(); //default constructor
		void precept(); //precept function 
		void encounter(); //encounter function 
		char event_letter(); //designates event letter 
};


#endif
