#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "event.h"
#include "room.h"
#include "wumpus.h"
#include "bats.h"
#include "gold.h"
#include "pit.h"

using namespace std;

class Game {

	protected:
		vector<vector<Room>> room; //2D vector of Rooms 
		vector<Event*> this_event; //to track event in order to delete it when restarting the game
		vector<Room*> this_room; //tracking the room in order to delete it when restarting the game 

		int rows, columns; //stores the number of rows and columns
		bool debug_mode, game_over, wump_status, gold_obtained; //values to determine conditional state of the game 

		int player_initial_x, player_initial_y; //player starting position (where they will have to escape)
		int player_position_x, player_position_y; //player position as they move throughout the board
		int wumpus_x, wumpus_y; //wumpus position that changes if woken up

		int num_arrows; //counts the number of arrows
		char direction_to_move; //input for direction to move

	public: 
		Game(); //Default game constructor 

		void instructions(); //outputs the instructions at the bengining of a new gamee
		void ask_dimensions(); //prompts for dimensions of the board
		void dimensions_error_check(string, int&); //error handling if dimensions are less than 4
		
		void ask_debug_mode(); //prompt for debug move
		void debug_mode_error(string, int&); //error handling for debug mode selection

		int random_position(); //returns a random room in the game
		void create_rooms(); //initializes the 2d vector of rooms
		Room* specific_room(int, int); //identifies a specific room to store events

		void populate_rooms(); //populates the rooms with events (wumpus and gold)
		void populate_bats(int, int); //populates the rooms with bats
		void populate_pits(int, int); //populates the rooms with pits
		void double_event_check(int&, int&); //prevents two events from remaining in the same position  

		void print_rooms(); //prints the rooms in the cave
		void print_part1(); //prints the position of the player and escape room
		void print_part2(int, int, int); //prints the location of the player and events 

		void prompt(); //prompts user if they wish to move or fire an arrow
		void prompt_error_handling(string, int&); //error handling for choice to move or fire an arrow
		bool check_bounds(int, int); //checks the bounds of the player so they do not attempt to move out of bounds 

		void move_player(char); //moves the player based on the direction they wish to go (north and west)
		void move_player2(char); //moves the player based on the direction they wish to go (east and south)

		void fire_arrow(); //simulates the turn if the player chooses to fire an arrow 
		void arrow_direction(char); //simulates the choice to fire an arrow in specific direction (includes north)
		void arrow_west(char, int, int); //simulates firing an arrow west
		void arrow_east(char, int, int); //simulates firing an arrow east
		void arrow_south(char, int, int); //simulates firing an arrow south
		void woke_the_wumpus(); //simulates the event of an arrow missing and waking up the wumpus

		void check_precept(); //checks for precepts 
		void check_event(); //checks for events to output appropriate encounter message and react accordingly 
		void check_event2(); 

		void victory(); //ends the game if the player obtains the gold, slays the wumpus, and is at their starting position
		void play_game(); //simulates the game play
		void same_settings(); //prompts user if they want to play again with the events in the same position
		void free_memory(); //deletes the event vectors storing a specific event and sets them to null
		void repopulate_on_restart(); //populates the same event vectors that were freed with new events in the same positions
		void same_settings_error(string, int&); //error handling if user does not enter a valid input to restart with same settings

		bool is_int(string); //checks if string input is an integer for error handling
		void string_to_int(string, int&); //coverts string input to integer for error handling and conditional statements
};

#endif 
