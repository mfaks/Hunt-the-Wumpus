/******************************************************
** Program: event.h
** Author: Muhammad Faks
** Date: 11/19/2022
** Description: This is the abtrasct class that contains purely virutal functions
** Input: Reads the precepts and enouncters of each event
** Output: Outputs uses polymorphism to output the correct precepts and enounters
******************************************************/

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>

using namespace std;

class Event {  
	protected:
	
	public:
		Event(); //empty constructor since the class is purely abstract
		virtual void precept() = 0; //precept message will be determined at run time
		virtual void encounter() = 0; //encounter message will be determined at runtime 
		virtual char event_letter() = 0; //event_letter used to designate the type of event
};

#endif
