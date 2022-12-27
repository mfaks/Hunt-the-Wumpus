/******************************************************
** Program: game.cpp
** Author: Muhammad Faks
** Description: Implementation file for game class containing variable initializations and function prototpyes
** Input: Grid size, direction to move, direction to fire an arrow, prompt to continue playing the same game after death
** Output: Instructions, dynamically updating game grid, precepts, encounters, outcomes for moving, outcomes for firing an arrow
******************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "game.h"

using namespace std;

/*********************************************************************
** Function: Game()
** Description: Default Constructor
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: New game is created
*********************************************************************/

Game::Game() {
	rows = 0, columns = 0;
	num_arrows = 3; //sets number of arrows to 3
	player_initial_x, player_initial_y, player_position_x, player_position_y = 0; //sets starting position at zero
	wumpus_x, wumpus_y = 0; //sets starting positition at zero
	direction_to_move = ' '; 
	debug_mode = false; 
	game_over = false; 
	wump_status = true; //sets the status of the wumpus to true representing its alive 
	gold_obtained = false; //set the status of the gold to not yet obtained 
}

/*********************************************************************
** Function: instructions()
** Description: Outputs instructions at the begining of the game
** Parameters: N/A
** Pre-Conditions: The game has begun
** Post-Conditions: The game can continue 
*********************************************************************/

void Game::instructions() {
	
	cout << "\nHello and welcome to Hunt the Wumpus!" << endl;
	cout << "\nYou can ONLY escape once you: \n1) Fire an arrow that slays the wumpus \n2) Obtain the gold chest hidden within the cave \n3) Return to your starting position" << endl;
	cout << "\nHowever: \n1) If you manage to fall into a pit on your jounrney, you will meet your demise \n2) If you stumble into the room of a sleeping Wumpus, you will meet your demise \n3) If you walk into a room of bats, you will be transported into a random room" << endl;
	cout << "\nGood luck! Loading Game..." << endl;

}

/*********************************************************************
** Function: ask_dimensions()
** Description: Prompts the user to input the dimensions of the grid 
** Parameters: N/A
** Pre-Conditions: The game is running
** Post-Conditions: The game can continue 
*********************************************************************/

void Game::ask_dimensions() {

	string dim_str;
	cout << "\nWhat are the dimensions you want your square grid to have? For example enter 4 if you want a 4x4 grid (enter an integer no less than 4): ";
	cin >> dim_str;
	string_to_int(dim_str, rows);
	dimensions_error_check(dim_str, rows); //checks if less than 4
	columns = rows; //rows and columns must be equal since the grid is a square

}

/*********************************************************************
** Function: dimensions_error_check()
** Description: Reprompts the user for correct dimensions of the room if they do not enter and integer or a size less than 4
** Parameters: string str, int &size
** Pre-Conditions: The user entered an invalid input
** Post-Conditions: Reprompts until valid input is entered
*********************************************************************/

void Game::dimensions_error_check(string str, int& size) {

	while (is_int(str) == false || size < 4) {
		cout << "\nInvalid input. Eneter an integer no less than 4: ";
		cin >> str;
		string_to_int(str, size);
	}

}

/*********************************************************************
** Function: ask_debug_mode()
** Description: Prompts the user if they wanter enter debug mode
** Parameters: N/A
** Pre-Conditions: Dimensions have been set 
** Post-Conditions: Game continues to run 
*********************************************************************/

void Game::ask_debug_mode() {
	
	string choice;
	int choice_value = 0; 

	cout << "\nWould you like to play this round in cheat mode? Enter a '0' for no or '1' for yes: ";
	cin >> choice;
	string_to_int(choice, choice_value);
	debug_mode_error(choice, choice_value); //error handles bad input
	
	if (choice_value == 0) { //sets debug_mode to false if the user does not want a cheat view
		debug_mode = false;
	}

	else { //sets debug_mode to true if the user wishes to enter cheat view
		debug_mode = true;
	}
}

/*********************************************************************
** Function: debug_mode_error
** Description: Checks for a valid input for debug mode choice
** Parameters: string choice, int& choice_value
** Pre-Conditions: User entered an invalid input
** Post-Conditions: Prompts until user eneters a valid input 
*********************************************************************/

void Game::debug_mode_error(string choice, int& choice_value) {
	
	while (is_int(choice) == false && choice_value != 0 && choice_value  != 1) { //if a non-integer value or integer value that is not 0 or 1 is entered
		cout << "\nInvalid input. Enter a '0' to NOT play in cheat mode or a '1' to play in cheat mode: ";
		cin >> choice;
		string_to_int(choice, choice_value);
		cout << choice_value;
	}
}

/*********************************************************************
** Function: random_position()
** Description: Determines a random coordinant in the cave
** Parameters: N/A
** Pre-Conditions: Cave has rooms with valid dimensions
** Post-Conditions: returns a random position for a room in the grid 
*********************************************************************/

int Game::random_position() {

	int random = rand() % rows; //works for columns too since rows and columns are equal 
	return random;  //can be used for both x and y coordinants

}

/*********************************************************************
** Function: create_rooms()
** Description: Creates a 2D vector of rooms
** Parameters: N/A
** Pre-Conditions: Valid input for rows/columns exists
** Post-Conditions: Rooms are created for the cave
*********************************************************************/

void Game::create_rooms() {

	for (int i = 0; i < rows; i++) {
		vector<Room> row_vec; //temporary vector to store rows 
		for (int j = 0; j < columns; j++) { 
			row_vec.push_back(Room(i, j)); //calls non_default constructor in room class to add an coordinate at that row 
		}
		room.push_back(row_vec);//adds each vector storing the rows to the 2d vector based on the dimensions  
	} 
}

/*********************************************************************
** Function: specific_room()
** Description: Identiies a specific room at a specific coordinant
** Parameters: int r, int c 
** Pre-Conditions: Rooms have been created 
** Post-Conditions: Returns the room pointer at that specifc coordinante 
*********************************************************************/

Room* Game::specific_room(int r, int c) {
	
	Room* this_room = &room.at(r).at(c); //sets a temporary room pointer to the address of a specifc room
	return this_room; //returns temporary pointer

}

/*********************************************************************
** Function: populate_rooms()
** Description: Populates the rooms with the events and their positions 
** Parameters: N/A
** Pre-Conditions: Rooms have been created
** Post-Conditions: Events are stored in different rooms 
*********************************************************************/

void Game::populate_rooms() {

	int random_row = random_position(); //temp variable to store random row coordinant 
	int random_column = random_position(); //temp variable to store random column coordinant 
	
	wumpus_x = random_position(); //assings the wumpus position to a random location in the grid
	wumpus_y = random_position(); //assings the wumpus position to a random location in the grid

	player_position_x = player_initial_x = random_position(); //sets the escape room row position at the starting position
	player_position_y = player_initial_y = random_position(); //sets the escape room column position at the starting position 

	Event* new_wumpus = new Wumpus(); //creates a new Wumpus object 
	this_event.push_back(new_wumpus); //adds wumpus to the end of the vector storing events; easy to delete when restarting the game  
	room.at(wumpus_x).at(wumpus_y).set_event(new_wumpus); //sets the location of the new wumpus to a room; event now exists in room
	this_room.push_back(specific_room(wumpus_x, wumpus_y)); //assings wumpus position to a specifc room within the temp vector of rooms; easy to delete once restarting game 
	
	Event* new_gold = new Gold(); //creates a new Gold object 
	this_event.push_back(new_gold); //adds gold to the end of the vector storing the events; easy to delete when restarting the game  
	double_event_check(random_row, random_column); //reassings the position of the event if there is a already one at that position 
	room.at(random_row).at(random_column).set_event(new_gold); //sets the locaton of the new gold to a room; event now exists in room 
	this_room.push_back(specific_room(random_row, random_column)); //assings the gold position to a specific room within the temp vector of rooms; easy to delete once restarting game   
	
	populate_bats(random_row, random_column); 
	populate_pits(random_row, random_column); 

}

/*********************************************************************
** Function: populate_bats
** Description: Populates both bats events in the game 
** Parameters: int random_row, int random_column
** Pre-Conditions: Rooms exists 
** Post-Conditions: Bat objects are initialized in previous empty rooms 
*********************************************************************/

void Game::populate_bats(int random_row, int random_column) {
	
	Event* first_bats = new Bats(); //creates a new bats object 
	this_event.push_back(first_bats); //adds the bat to the end of the temp vector storing events; easy to delete once restarting the game 
	double_event_check(random_row, random_column); //reassings the position of the event if there is a already one at that position 
	room.at(random_row).at(random_column).set_event(first_bats); //sets the location of the bats to a room; event now exists in the room 
	this_room.push_back(specific_room(random_row, random_column)); //assings the bats position to a specific room within the temp vector of rooms; easy to delete once restarting game 
	
	Event* second_bats = new Bats(); //creates a new bats objects
	this_event.push_back(second_bats); //adds the bat to the end of the temp vector storing events; easy to delete once restarting the game 
	double_event_check(random_row, random_column); //reassings the position of the event if there is a already one at that position 
	room.at(random_row).at(random_column).set_event(second_bats); //sets the location of the bats to a room; event now exists in the room
	this_room.push_back(specific_room(random_row, random_column)); //assings the bats position to a specific room within the temp vector of rooms; easy to delete once restarting game 
	
}

/*********************************************************************
** Function: populate_pits
** Description: Populates both pits events in the game
** Parameters: int random_row, int random_column
** Pre-Conditions: Rooms exists
** Post-Conditions: Pit objects are initialized in previous empty rooms
*********************************************************************/

void Game::populate_pits(int random_row, int random_column) {
	
	Event* first_pit = new Pit();
	this_event.push_back(first_pit);
	double_event_check(random_row, random_column); //reassings the position of the event if there is a already one at that position 
	room.at(random_row).at(random_column).set_event(first_pit); 
	this_room.push_back(specific_room(random_row, random_column));

	Event* second_pit = new Pit();
	this_event.push_back(second_pit); //reassings the position of the event if there is a already one at that position 
	double_event_check(random_row, random_column);
	room.at(random_row).at(random_column).set_event(second_pit);
	this_room.push_back(specific_room(random_row, random_column));
}


/*********************************************************************
** Function: double_event_check()
** Description: Checks if an event exists in a specific room 
** Parameters: int &r, int &c
** Pre-Conditions: Event object already exists in a room
** Post-Conditions: New event object will be placed in an empty room 
*********************************************************************/

void Game::double_event_check(int& r, int& c) {

	while (room.at(r).at(c).get_event_check() == true) {
		r = random_position(); //assigns new row
		c = random_position(); //aasigns new column
	}
}

/*********************************************************************
** Function: print_rooms()
** Description: Prints the gameboard throughout the game 
** Parameters: None 
** Pre-Conditions: Player and events have been placed in 
** Post-Conditions: Displayes the game board accurately 
*********************************************************************/

void Game::print_rooms() {

	if (game_over == false) {
		int dimensions = rows;
		print_part1(); //prints player and escape room positions 
		for (int i = 0; i < dimensions; i++) {
			for (int r = 0; r < rows; r++) { 
				cout << "+-----";
			}
			cout << "+" << endl;
			for (int k = 0; k < 3; k++) { //seperates the room into 3 layers
				for (int j = 0; j < columns; j++) {
					print_part2(k, i, j); 
				}
				cout << "|" << endl;
			}
		}
		for (int r = 0; r < rows; r++) { //bottom of the grind
			cout << "+-----"; 
		}
		cout << "+" << endl;
	}
}

/*********************************************************************
** Function: print_part1()
** Description: Prints out the escape room and current player position
** Parameters: N/A
** Pre-Conditions: Player and escape room positions have been assinged
** Post-Conditions: Outputs the positions correctly 
*********************************************************************/

void Game::print_part1() {
	cout << endl;
	cout << "Your escape room position is row: " << player_initial_x + 1 << " column: " << player_initial_y + 1 << endl; //location of escape room 
	cout << "You current position is row: " << player_position_x + 1 << " column: " << player_position_y + 1 << endl << endl; //curent player location 
}

/*********************************************************************
** Function: print_part2()
** Description: Prints the position of the player and events
** Parameters: int k, int i, int j
** Pre-Conditions: Game board is being built
** Post-Conditions: Player and event are displayed correctly
*********************************************************************/

void Game::print_part2(int k, int i, int j) {
	
	if (k == 1 && i == player_position_x && j == player_position_y) { //each room has been divided into 3 sections, outputs the player position in the middle section 
		cout << "|  X  ";
	}

	else if (debug_mode == true && k == 2 && room.at(i).at(j).get_event_check() == true) { //events are places in the lower section of the room 
		cout << "|  " << room.at(i).at(j).get_event()->event_letter() << "  ";
	}

	else  //will display empty rooms 
		cout << "|     ";

}

/*********************************************************************
** Function: prompt()
** Description: Prompts the user if they want to move or fire an arrow 
** Parameters: N/A
** Pre-Conditions: Player and events have been established 
** Post-Conditions: Player can move or fire an arrow 
*********************************************************************/

void Game::prompt() {

	string move_or_fire; 
	int choice_value = -1; 

	if (game_over == false) { //runs while the game is not over 
		check_event(); //checks if player spawns in an event 
		if (game_over == false) { //runs while the game is not over 
			check_precept(); //checks for precept at position 
			cout << "\n\nYour current number of arrows is " << num_arrows << ". \nWould you like to move or fire an arrow ? \nEnter a '0' to move or '1' to fire an arrow : ";
			cin >> move_or_fire;
			string_to_int(move_or_fire, choice_value); 
			prompt_error_handling(move_or_fire, choice_value); 

			if (choice_value == 0) { //runs if player wishes to move
				cout << "\nEnter: 'w' to move north, 'a' to move west, 'd' to move east, 's' to move south: ";
				cin >> direction_to_move;
				move_player(direction_to_move); //runs if player chooses to move north or west
				move_player2(direction_to_move); //runs if player chooses to moev east or south 
				print_rooms();
			}

			else if (choice_value == 1) { //runs if player wishes to fire an arrow 
				fire_arrow();
				print_rooms(); 
			}
		}
	}
}

/*********************************************************************
** Function: prompt_error_handling()
** Description: Error handles the choice to move or fire an arrow
** Parameters: string move_or_fire, int &choice_value
** Pre-Conditions: Player enters an invalid input
** Post-Conditions: Runs until valid input is entered
*********************************************************************/

void Game::prompt_error_handling(string move_or_fire, int& choice_value) {

	while (is_int(move_or_fire) == false && choice_value != 0 && choice_value != 1) { //error handling for invalid input
		cout << "\n\nInvalid input! Your current number of arrows is " << num_arrows << ". \nWould you like to move or fire an arrow ? \nEnter a '0' to move or '1' to fire an arrow :";
		cin >> move_or_fire;
		string_to_int(move_or_fire, choice_value);
	}
}

/*********************************************************************
** Function: check_bounds()
** Description: Checks if the player attempts to move out of bounds
** Parameters: int x_cord, int y_cord
** Pre-Conditions: Player attempts to move
** Post-Conditions: Does not allow the player to move if they are heading out of bounds
*********************************************************************/

bool Game::check_bounds(int x_cord, int y_cord) {

	if (x_cord > rows - 1 || x_cord < 0 || y_cord > columns - 1 || y_cord < 0) {
		return false; //prevents the player from moving if they wish to go out of bounds 
	}

	else
		return true;
}

/*********************************************************************
** Function: move_player()
** Description: Moves the player north or west
** Parameters: char direction_to_move 
** Pre-Conditions: Player wishes to move north or west
** Post-Conditions: Adjust player position, sets new position, checks if they are at the escape room to win the game, checks encounters, checks precepts 
*********************************************************************/

void Game::move_player(char direction_to_move) {

	if (direction_to_move == 'w' && check_bounds(player_position_x-1, player_position_y) == true) { //moves north and within the bounds of the cave
		player_position_x--; //adjust position by one 
		(room.at(player_position_x).at(player_position_y)); //sets the new position of the player at the room 
		victory(); //checks if the player meets the conditions to escape if they move to the escape room 
		check_event(); //checks for encounter 
		check_precept(); //checks for precept 
	}

	if (direction_to_move == 'a' && check_bounds(player_position_x, player_position_y-1) == true) { //moves west and within the bounds of the cave 
		player_position_y--; //adjust position by one 
		(room.at(player_position_x).at(player_position_y)); //sets the new position of the player at the room 
		victory(); //checks if the player meets the conditions to escape if they move to the escape room 
		check_event(); //checks for encounter 
		check_precept(); //checks for precept 
	} 
}

/*********************************************************************
** Function: move_player2()
** Description: Moves the player east or south 
** Parameters: char direction_to_move
** Pre-Conditions: Player wishes to move east or south 
** Post-Conditions: Adjust player position, sets new position, checks if they are at the escape room to win the game, checks encounters, checks precepts 
*********************************************************************/

void Game::move_player2(char direction_to_move) {
	
	if (direction_to_move == 'd' && check_bounds(player_position_x, player_position_y + 1) == true) { //moves east and within the bounds of the cave 
		player_position_y++; //adjust position by one 
		(room.at(player_position_x).at(player_position_y)); //sets the new position of the player at the room 
		victory(); //checks if the player meets the conditions to escape if they move to the escape room 
		check_event(); //checks for encounter 
		check_precept(); //checks for precept
	}

	if (direction_to_move == 's' && check_bounds(player_position_x + 1, player_position_y) == true) { //moves south and within the bounds of the cave 
		player_position_x++; //adjust position by one 
		(room.at(player_position_x).at(player_position_y)); //sets the new position of the player at the room 
		victory(); //checks if the player meets the conditions to escape if they move to the escape room 
		check_event(); //checks for encounter 
		check_precept(); //checks for precept 
	}
}

/*********************************************************************
** Function: fire_arrow()
** Description: Simulates the turn if player fires an arrow
** Parameters: N/A
** Pre-Conditions: Player fires an arrow
** Post-Conditions: Simulates the turn 
*********************************************************************/

void Game::fire_arrow() {
	
	char fire_direction; 
	if (game_over == false) { //runs while game is not over 
		
		if (num_arrows > 0) { //if player has arrows left 
			num_arrows--; //subtracts one from the current number of arrows 
			cout << "\nYou have chosen to fire an arrow! You now have " << num_arrows << " remaining." << endl;
			cout << "Which direction would you like to fire the arrow? \nEnter: 'w' to fire north, 'a' to fire west, 'd' to fire east, 's' to fire south: ";
			cin >> fire_direction;
			arrow_direction(fire_direction); //simulates turn based on the direction to the fire the arrow
		}

		else { //if player does not have any more arrows 
			cout << "\nUh oh, it looks like you do not have any more arrows to fire :(" << endl;
		}
	}
}


void Game::arrow_direction(char fire_direction) {
	
	int arrowx = player_position_x; //assings arrow row to the current player row
	int arrowy = player_position_y; //assinds arrow column to the current player column

	cout << "\nNow firing arrow --->" << endl << endl; 
	if (fire_direction == 'w' && wump_status == true) { //fires north
		for (int i = 1; i < 4; i++) { //fire accross 1, 2, and 3 places in that direction 
			if (arrowx - i >= 0) { //checks if arrow stays in bounds 
				if (room.at(arrowx - i).at(arrowy).get_event_check() == true && room.at(arrowx - i).at(arrowy).get_event()->event_letter() == 'W') { //checks if arrow hits the wumpus 
					cout << "Arrow #" << i << " successfully slayed the Wumpus!" << endl;
					wump_status = false; //wumpus is slayed
					break; //stops firing arrows
				}
				else
					cout << "Arrow #" << i << " missed the Wumpus :(" << endl;
			}
			else
				cout << "Arrow #" << i << " went out of bounds :(" << endl;
		}
		if (wump_status == true) //runs if wumpus remains alive
			woke_the_wumpus();
	}
	
	arrow_west(fire_direction, arrowx, arrowy); //simulates turn to fire west
	arrow_east(fire_direction, arrowx, arrowy); //simulates turn to fire east
	arrow_south(fire_direction, arrowx, arrowy); //simluates turn to fire south
}

/*********************************************************************
** Function: arrow_west
** Description: Simulates the turn if player fires an arrow west
** Parameters: char fire_direction, int arrowx, int arrowy
** Pre-Conditions: Player fires an arrow west
** Post-Conditions: simulates the turn
*********************************************************************/

void Game::arrow_west(char fire_direction, int arrowx, int arrowy) {

	if (fire_direction == 'a' && wump_status == true) { //fires west
		for (int i = 1; i < 4; i++) { //fire accross 1, 2, and 3 places in that direction 
			if (arrowy - i >= 0) { //checks if arrow stays in bounds 
				if (room.at(arrowx).at(arrowy - i).get_event_check() == true && room.at(arrowx).at(arrowy - i).get_event()->event_letter() == 'W') { //checks if arrow hits the wumpus
					cout << "Arrow #" << i << " successfully slayed the Wumpus!" << endl;
					wump_status = false; //wumpus is slayed
					break; //stops firing arrrows 
				}
				else
					cout << "Arrow #" << i << " missed the Wumpus :(" << endl;
			}
			else
				cout << "Arrow #" << i << " went out of bounds :(" << endl;
		}
		if (wump_status == true)
			woke_the_wumpus(); //runs if wumpus remains alove 
	}

}

/*********************************************************************
** Function: arrow_east
** Description: Simulates the turn if player fires an arrow east
** Parameters: char fire_direction, int arrowx, int arrowy
** Pre-Conditions: Player fires an arrow east
** Post-Conditions: simulates the turn
*********************************************************************/

void Game::arrow_east(char fire_direction, int arrowx, int arrowy) {

	if (fire_direction == 'd' && wump_status == true) { //fires east
		for (int i = 1; i < 4; i++) { //fire accross 1, 2, and 3 places in that direction 
			if (arrowy + i < columns) { //checks if the arrow remains in bounds 
				if (room.at(arrowx).at(arrowy + i).get_event_check() == true && room.at(arrowx).at(arrowy + i).get_event()->event_letter() == 'W') { //checks if arrow hits the wumpus
					cout << "Arrow #" << i << " successfully slayed the Wumpus!" << endl;
					wump_status = false; //wumpus now slayed
					break; //stops firing arrowas 
				}
				else
					cout << "Arrow #" << i << " missed the Wumpus :(" << endl;
			}
			else
				cout << "Arrow #" << i << " went out of bounds :(" << endl;
		}
		if (wump_status == true)
			woke_the_wumpus(); //runs if wumpus remains alive 
	}
}

/*********************************************************************
** Function: arrow_south 
** Description: Simulates the turn if player fires an arrow south
** Parameters: char fire_direction, int arrowx, int arrowy
** Pre-Conditions: Player fires an arrow south
** Post-Conditions: simulates the turn
*********************************************************************/

void Game::arrow_south(char fire_direction, int arrowx, int arrowy) {

	if (fire_direction == 's' && wump_status == true) { //fires south 
		for (int i = 1; i < 4; i++) { //fire accross 1, 2, and 3 places in that direction 
			if (arrowx + i < rows) { //checks if the arrow is fired in bounds 
				if (room.at(arrowx + i).at(arrowy).get_event_check() == true && room.at(arrowx + i).at(arrowy).get_event()->event_letter() == 'W') { //checks if arrow hits the wumpus 
					cout << "\nYou have successfully slayed the Wumpus!" << endl; 
					wump_status = false; //wumpus now slayed
					break; //stops firing arrows 
				}
				else
					cout << "Arrow #" << i << " missed the Wumpus :(" << endl;
			}
			else
				cout << "Arrow #" << i << " went out of bounds :(" << endl;
		}
		if (wump_status == true)
			woke_the_wumpus(); //runs if wumpus remains alive 
	}
}

/*********************************************************************
** Function: check_precept()
** Description: Checks for precepts 
** Parameters: N/A
** Pre-Conditions: Player is adjacent to an event
** Post-Conditions: Precept message is displayed
*********************************************************************/

void Game::check_precept() {
	
	if (check_bounds(player_position_x+1,player_position_y) == true && room.at(player_position_x+1).at(player_position_y).get_event_check() == true) { //checks for precept one position to the south 
		room.at(player_position_x+1).at(player_position_y).get_event()->precept();
	}

	if (check_bounds(player_position_x - 1, player_position_y) == true && room.at(player_position_x-1).at(player_position_y).get_event_check() == true) { //checks for precept one position to the north 
		room.at(player_position_x - 1).at(player_position_y).get_event()->precept();
	}

	if (check_bounds(player_position_x, player_position_y+1) == true && room.at(player_position_x).at(player_position_y+1).get_event_check() == true) { //checks precept for one position to the east
		room.at(player_position_x).at(player_position_y+1).get_event()->precept();
	}
	
	if (check_bounds(player_position_x, player_position_y-1) == true && room.at(player_position_x).at(player_position_y-1).get_event_check() == true) { //checks precept for one position to the west
		room.at(player_position_x).at(player_position_y-1).get_event()->precept();
	}
}

/*********************************************************************
** Function: check_event()
** Description: Checks for an encounter for an event 
** Parameters: N/A
** Pre-Conditions: Player encounters an event (wumpus or bats)
** Post-Conditions: Encounter message displayed and corresponding actions completed 
*********************************************************************/

void Game::check_event() {

	if (room.at(player_position_x).at(player_position_y).get_event_check() == true && room.at(player_position_x).at(player_position_y).get_event()->event_letter() == 'W') { //encounters wumpus
	
		if (wump_status == true) { //if the wumpus is alive
			room.at(player_position_x).at(player_position_y).get_event()->encounter(); 
			print_rooms(); //prints room of you and the wumpus 
			game_over = true; //ends the game automatically 
		}

		else { //if the wumpus is dead 
			cout << "\nYou come back to admire your work after vanquishing the wumpus." << endl; 
		}
	}

	if (room.at(player_position_x).at(player_position_y).get_event_check() == true && room.at(player_position_x).at(player_position_y).get_event()->event_letter() == 'B') { //encounters bats
		room.at(player_position_x).at(player_position_y).get_event()->encounter();
		player_position_x = random_position(); //assigns random row
		player_position_y = random_position(); //assings random columns
		print_rooms(); 
		check_event(); //recursion to check if the bats move you to another event room 
	}
	check_event2(); //encounter functions for pits and gold 
}

/*********************************************************************
** Function: check_event2()
** Description: Runs encounter functions if player is in the same room as the pit or gold 
** Parameters: N/A
** Pre-Conditions: Player is in the same room as the pit or gold 
** Post-Conditions: Player falls into the pit and the game ends or the player obtains the gold 
*********************************************************************/

void Game::check_event2() {
	
	if (room.at(player_position_x).at(player_position_y).get_event_check() == true && room.at(player_position_x).at(player_position_y).get_event()->event_letter() == 'P') { //encounters pits 
		room.at(player_position_x).at(player_position_y).get_event()->encounter();
		print_rooms(); //prints the position of the player in the pit
		game_over = true; //automatically ends the game 

	}

	if (room.at(player_position_x).at(player_position_y).get_event_check() == true && room.at(player_position_x).at(player_position_y).get_event()->event_letter() == 'G') { //encounters gold 

		if (gold_obtained == false) { //runs if the player has not yet obtained the gold
			room.at(player_position_x).at(player_position_y).get_event()->encounter();
			gold_obtained = true;
			victory();
		}
		else //runs if the player comes into the same room as gold after they loot the chest 
			cout << "\nYou come back to admire your work after looting the gold from the chest." << endl;
	}
}

/*********************************************************************
** Function: woke_the_wumpus()
** Description: 75% probability the wumpus moves if arrow misses 
** Parameters: N/A
** Pre-Conditions: Arrow does not slay the wumpus 
** Post-Conditions: 75% chance wumpus moves  
*********************************************************************/

void Game::woke_the_wumpus() {

	int chance_of_woke = (rand() % 4) + 1; //generates random number between 1 and 4
	if (chance_of_woke != 4) { //1, 2, and 3 represent a 75% probabilty of the wumpus waking up 
		cout << "\nThe wumpus heard your arrow and woke up! It moved to a different room. " << endl; 
		Event* newer_wumpus; //decalares a new wumpus object
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (room.at(i).at(j).get_event_check() == true && room.at(i).at(j).get_event()->event_letter() == 'W') { //finds the old wumpus
					newer_wumpus = specific_room(i,j)->get_event(); //accesses the wumpus event to create a new wumpus
					specific_room(i,j)->set_event(NULL); //deletes what the room the old wumpus is pointing 
					specific_room(i,j)->replace_event(false); //sets that there is no event in the room
				}
			}
		}
		wumpus_x = random_position(); 
		wumpus_y = random_position();
		double_event_check(wumpus_x, wumpus_y); //double checks for event in the space to prevent 2 events in one square. 
		room.at(wumpus_x).at(wumpus_y).set_event(newer_wumpus); //places object at random position in the grid
	}
}

/*********************************************************************
** Function: victory()
** Description: Outputs a victory message and ends the game 
** Parameters: N/A
** Pre-Conditions: Player has obtained gold, slayed wumpus, and is at the escape room position
** Post-Conditions: Victory message and current game ends 
*********************************************************************/

void Game::victory() {

	if (gold_obtained = true && wump_status == false && player_position_x == player_initial_x && player_position_y == player_initial_y) {
		cout << "\nCongratulations! You have emerged from the cave victorious!" << endl;
		print_rooms(); 
		game_over = true; 
	}
}

/*********************************************************************
** Function: play_game()
** Description: Simulates the game player
** Parameters: N/A
** Pre-Conditions: Rooms and events have been intiialized 
** Post-Conditions: Game is simulates 
*********************************************************************/

void Game::play_game() {

	game_over = false; 
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (room.at(i).at(j).get_event() != NULL) { //looks through the vector to delete old memory before starting a new game 
				specific_room(i, j)->set_event(NULL); //deletes what the room is pointing 
				specific_room(i, j)->replace_event(false); //sets that there is no event in the room
			}
		}
	}

	instructions(); 
	ask_dimensions();
	ask_debug_mode();
	create_rooms(); 
	populate_rooms();
	print_rooms(); 

	while (game_over == false) { //runs until the game is over 
		prompt();
		same_settings(); 
	}
}

/*********************************************************************
** Function: same_settings()
** Description: Prompts the user for choice to refresh the game 
** Parameters: N/A
** Pre-Conditions: Runs once game ends 
** Post-Conditions: Simulates a soft or hard restart 
*********************************************************************/

void Game::same_settings() {

	string answer;
	int answer_value = -1; 

	if (game_over == true) { //runs if game is over 
	
		cout << "\n\nThank you for playing today! Would you like to restart the game with the events in the same position?" << endl; //soft refresh
		cout << "Enter a '0' for no or '1' for yes: "; 
		cin >> answer; 
		string_to_int(answer, answer_value);
		same_settings_error(answer, answer_value); 
		
		if (answer_value == 1) { //player choses a soft refresh 
			cout << "\nNow reloading game with same settings....." << endl; 
			free_memory(); //frees old memory and populates new 
			game_over = false; //sets game conditions back to the origional 
			gold_obtained = false; //player no longer has gold 
			wump_status = true; //wumpus is now alive
			num_arrows = 3; //player has 3 arrows 
			player_position_x = player_initial_x; //player starts at escape room row
			player_position_y = player_initial_y; //player start at escape room columns
			print_rooms();
		}

		else if (answer_value == 0)
			cout << "\nThank you for your response. Next question..." << endl; //propmts user if they want a hard restart in the main function  
	}

}

/*********************************************************************
** Function: free_memory()
** Description: Frees the events if the user wishes to refresh the game 
** Parameters: N/A
** Pre-Conditions: Player wishes to refresh the game with events in the same positions
** Post-Conditions: Old events are deleted and new events are assinged to the old positions 
*********************************************************************/

void Game::free_memory() {

	for (int i = 0; i < this_event.size(); i++) { //deletes the event pointers stored in temporary vector 
		if (this_event[i] != NULL) { //checks in case of double free
			delete this_event[i];
			this_event[i] = NULL;
		}
	}
	this_event.clear();  //clears the contents of the temporary pointer vector 
	
	Event* new_wumpus = new Wumpus();
	this_event.push_back(new_wumpus);
	this_room.at(0)->set_event(new_wumpus); //assings the new wumpus object at its initial position in the vector 
	repopulate_on_restart(); //repopulates the rest of the events at the same positions
}

/*********************************************************************
** Function: repopulate_on_restart()
** Description: Assings new event objects at same positions if game refreshes
** Parameters: N/A
** Pre-Conditions: Player wishes to refresh the game with events in same positions
** Post-Conditions: New event objects are declared
*********************************************************************/

void Game::repopulate_on_restart() {
	
	Event* new_gold = new Gold(); 
	this_event.push_back(new_gold);
	this_room.at(1)->set_event(new_gold); //assigns the new gold object at its initial position in the vector 

	Event* first_bats = new Bats();
	this_event.push_back(first_bats);
	this_room.at(2)->set_event(first_bats); //assigns the first bats object at its initial position in the vector

	Event* second_bats = new Bats();
	this_event.push_back(second_bats);
	this_room.at(3)->set_event(second_bats); //assigns the second bats object at its initial position in the vector

	Event* first_pit = new Pit();
	this_event.push_back(first_pit);
	this_room.at(4)->set_event(first_pit); //assigns the first pit object at its initial position in the vector

	Event* second_pit = new Pit();
	this_event.push_back(second_pit);
	this_room.at(5)->set_event(second_pit); //assigns the second pit object at its initial position in the vector
}

/*********************************************************************
** Function: same_settings_error_()
** Description: Error handles the choice to refresh or restart the game
** Parameters: string answer, int &answer_value
** Pre-Conditions: Player enters an invalid input
** Post-Conditions: Runs until valid input is entered
*********************************************************************/

void Game::same_settings_error(string answer, int& answer_value) {

	while (is_int(answer) == false && answer_value != 0 && answer_value != 1) { //error handling for invalid input
		cout << "\nInvalid input! Would you like to restart the game with the events in the same position? \nEnter a '0' for no or '1' for yes:";
		cin >> answer;
		string_to_int(answer, answer_value);
	}

}

/*********************************************************************
** Function: is_int()
** Description: Checks if a string input is an integer
** Parameters: string str
** Pre-Conditions: Input is a string 
** Post-Conditions: Returns if the string is an integer
*********************************************************************/

bool Game::is_int(string str) {

	for (int n = 0; n < str.length(); n++) {
		if (str[0] == '-' && str.length() > 1)
			continue;
		else if (!(str[n] >= '0' && str[n] <= '9'))  //checks the characters are not from 0 to 9
			return false;
	}

	return true;
}

/*********************************************************************
** Function: string_to_int()
** Description: Converts a string to its integer value 
** Parameters: String str, int& value
** Pre-Conditions: Accepts string input 
** Post-Conditions: Stores it into integer parameter
*********************************************************************/

void Game::string_to_int(string str, int& value) {

	value = 0;
	for (int i = 0; i < str.length(); i++) {

		if (str[i] == '-') {
			i++;
		}

		int val = (int)(str[i] - '0');
		value = value * 10 + val; //math to store the value if a positive string into value 
	}

	if (str[0] == '-') {
		value = value * -1; //storing the negative integer in value if a "-" is detected
	}

}
