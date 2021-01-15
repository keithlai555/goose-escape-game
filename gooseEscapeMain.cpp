#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

//set up the console.   Don't modify this line!
Console out;

int main()
{
	//Set up the window.  Don't edit these two lines
    terminal_open();
  	terminal_set(SETUP_MESSAGE);
	
	// initialize random number generator with time
    srand(time(0)); 
    // spawn player at a random location near top left of screen
	Actor player(PLAYER_CHAR, rand() % (MAX_BOARD_X / THREE), rand() % (MAX_BOARD_Y / THREE), 
				 PLAYER_HEALTH);  
				 
	// spawn monster at a random location near bottom right of screen
	Actor monster(MONSTER_CHAR, rand() % (MAX_BOARD_X / FOUR) + (TWO * MAX_BOARD_X / THREE), 
				  rand() % (MAX_BOARD_Y / FOUR) + (TWO * MAX_BOARD_Y / THREE), MONSTER_HEALTH);
			
    // array to hold gameBoard map
    int gameBoard[MAX_BOARD_Y][MAX_BOARD_X] = {0};
  	
	// creation of walls
	for (int row = START_WALL_COLUMN; row <= END_WALL_COLUMN; row++)
	{
		printGameWorld(row, END_WALL_ROW, WALL_CHAR);
		printGameBoard(gameBoard, END_WALL_ROW, row, SHALL_NOT_PASS);
	}
	for (int col = START_WALL_ROW; col < END_WALL_ROW; col++)
	{
		printGameWorld(END_WALL_COLUMN, col, WALL_CHAR);
		printGameBoard(gameBoard, col, END_WALL_COLUMN, SHALL_NOT_PASS);
	}
	
	for (int walls = 1; walls <= NUM_WALLS; walls++)
    {
        int xLocation = 0;
        int yLocation = 0;
        xLocation = rand() % MAX_BOARD_X;
        yLocation = rand() % MAX_BOARD_Y;
        printGameWorld(xLocation, yLocation, WALL_CHAR);
        printGameBoard(gameBoard,yLocation, xLocation, SHALL_NOT_PASS);
    }
	
	// call function to spawn initial weapon
	spawnWeapon(gameBoard);
  	

	// printing the instructions
    out.writeLine("Escape the Goose! " + monster.get_location_string());
	out.writeLine("Use arrow keys to move and if the goose hits you without a weapon, you lose!");
	out.writeLine("Get to the 'S' location to acquire a weapon and win by fighting");
	out.writeLine("the goose 3 times properly with a weapon and then getting to the winning zone.");

    int keyEntered = TK_A;  // can be any valid value that is not ESCAPE or CLOSE
    bool hasWeapon = false;
    
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE && !captured(player,monster) && gameBoard[player.get_y()][player.get_x()] != WINNER)
	{
	    // get player key press
	    keyEntered = terminal_read();
	    
        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
            // move the player
    	    movePlayer(keyEntered,player, gameBoard);
			
            // call the goose's chase function
            gooseChase(monster, player, gameBoard);
            
            // if player overlaps with 'S', then they obtain a weapon and hasWeapon turns true
			hasWeapon = pickedUpWeapon(player, gameBoard, hasWeapon);

			// if player has weapon and overlaps goose, they call fight function
			if (captured(player, monster) && hasWeapon)
			{
				fight(monster, player, gameBoard);
				hasWeapon = false;
			}
        }
  	}

    if (keyEntered != TK_CLOSE)
    {
      	//once we're out of the loop, the game is over
        out.writeLine("Game has ended");
    
        // output reason for end of game
		if (gameBoard[player.get_y()][player.get_x()] == WINNER)
		{
			out.writeLine("You won!");
		}
		else if (captured(player, monster))
		{
			out.writeLine("The goose got you!");
		}
		else
		{
			out.writeLine("You have exited the program.");
		}
    	// Wait until user closes the window
        while (terminal_read() != TK_CLOSE);
    }

	//game is done, close it  
    terminal_close();
}
