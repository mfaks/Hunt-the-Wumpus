/******************************************************
** Program: gold.h
** Author: Muhammad Faks
** Description: Inhereted polymorphically from event class
** Input: n/a
** Output: Uses polymorphism to output the gold precept and enounter message
******************************************************/

#ifndef GOLD_H
#define GOLD_H

#include <iostream>
#include <string>

#include "event.h"

using namespace std;

class Gold : public Event { //inhereted from event class 
	protected:

	public:
		Gold(); //default constructor
		void precept(); //precept function
		void encounter(); //encouter function
		char event_letter(); //designates event_letter
};

#endif
