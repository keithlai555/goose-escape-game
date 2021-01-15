#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

extern Console out;
	
// print game world function
void printGameWorld(int x_location_on_board, int y_location_on_board, int character)
{
	terminal_put(x_location_on_board, y_location_on_board, character);
}

// print the game board function
void printGameBoard(int gameBoard[MAX_BOARD_Y][MAX_BOARD_X], int row, int column, int constant) 
{
	gameBoard[row][column] = constant;
}

// check if goose captured player function
bool captured(Actor const & player, Actor const & monster)
{
    return (player.get_x() == monster.get_x() 
         && player.get_y() == monster.get_y());
}

// battle to fight off goose if weapon in hand function
void fight(Actor & monster, Actor & player, int gameBoard[MAX_BOARD_Y][MAX_BOARD_X])
{
    out.writeLine("Press f to fight off the goose!"); // give user instructions to fight
    int key = terminal_read(); // read next key entered
    if (key == TK_F)
    {
    	player.restart_location("MIN"); // call restart location to reset player at top left
    	monster.restart_location("MAX"); // call restart location to reset monster at bottom right
    	monster.lose_health(); // monster loses a health since user pressed f
    	if (monster.get_health() == 1) // if goose has been defeated 3 times
		{
    		spawnWinner(gameBoard); // spawn winning location
    		out.writeLine("The goose has one health left!");
    		out.writeLine("Get to the W to escape the final goose!");
		}
    	else
		{
    		spawnWeapon(gameBoard); // spawn new weapon location to fight goose again
    		out.writeLine("The goose has lost a health and is at " + monster.get_health_string() + " health.");
		}
	}
}

// spawn random winner function
void spawnWinner(int gameBoard[MAX_BOARD_Y][MAX_BOARD_X])
{
	srand(time(0)); // initialize random number generator with current time
	int x_location = rand() % (MAX_BOARD_X/TWO) + MAX_BOARD_X/THREE; // random x location near left middle of screen
	int y_location = rand() % (MAX_BOARD_Y/TWO) + MAX_BOARD_Y/THREE; // random y location near top middle of screen
	printGameWorld(x_location, y_location, WIN_CHAR); // print game world with winner character
	printGameBoard(gameBoard, y_location, x_location, WINNER); // print game board with winner location
}

// picked up weapon function
bool pickedUpWeapon(Actor const & player, int gameBoard[MAX_BOARD_Y][MAX_BOARD_X], bool hasWeapon)
{
	if (gameBoard[player.get_y()][player.get_x()] == WEAPON) 
	{
		out.writeLine("You have the weapon. You can fight the goose."); // output when picked up weapon
		gameBoard[player.get_y()][player.get_x()] = 0; // original gameboard weapon location is erased 
		// such that player can't pick up the weapon from this location anymore
		return true;
	}
	else if (gameBoard[player.get_y()][player.get_x()] != WEAPON && hasWeapon == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// spawn random weapon location
void spawnWeapon(int gameBoard[MAX_BOARD_Y][MAX_BOARD_X])
{
	srand(time(0));
	int newLocationX = rand() % (MAX_BOARD_X/FOUR) + MAX_BOARD_X/FOUR; // random x location near left middle of screen
	int newLocationY = rand() % (MAX_BOARD_Y/THREE) + MAX_BOARD_Y/TWO; // random y location near top middle of screen
	printGameWorld(newLocationX, newLocationY, WEAPON_CHAR); // print game world with weapon character
	printGameBoard(gameBoard, newLocationY, newLocationX, WEAPON); // print game board with weapon location
}

// move player function
void movePlayer(int key, Actor & player, int gameBoard[MAX_BOARD_Y][MAX_BOARD_X])
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -1;
    else if (key == TK_DOWN)
        yMove = 1;
    else if (key == TK_LEFT)
        xMove = -1;
    else if (key == TK_RIGHT)
        xMove = 1;
        
    if (player.can_move(xMove, yMove) 
      && gameBoard[player.get_y() + yMove][player.get_x() + xMove] != SHALL_NOT_PASS)
        player.update_location(xMove, yMove);
}

// goose chase function
void gooseChase(Actor & monster, Actor & player, int gameBoard[MAX_BOARD_Y][MAX_BOARD_X])
{
	int yMove = 0, xMove = 0;
	if (monster.get_x() > player.get_x() && abs(monster.get_x()-player.get_x()) >= abs(monster.get_y()-player.get_y()))
	{
		xMove = -1;
	}
	else if (monster.get_x() < player.get_x() && abs(monster.get_x()-player.get_x()) >= abs(monster.get_y()-player.get_y()))
	{
		xMove = 1;
	}
	else if (monster.get_y() > player.get_y() && abs(monster.get_y()-player.get_y()) > abs(monster.get_x()-player.get_x()))
	{
		yMove = -1;
	}
	else if (monster.get_y() < player.get_y() && abs(monster.get_y()-player.get_y()) > abs(monster.get_x()-player.get_x()))
	{
		yMove = 1;
	}
	
	int tempXMove = xMove;
	int tempYMove = yMove;
	int tempMonsterYLocation = monster.get_y();
	int tempMonsterXLocation = monster.get_x();
	
	while (gameBoard[tempMonsterYLocation + tempYMove][tempMonsterXLocation + tempXMove] != 0) // this loop calculates walls to jump over
	{
		xMove += tempXMove;
		yMove += tempYMove;
		tempMonsterYLocation += tempYMove;
		tempMonsterXLocation += tempXMove;
	}
	
	
	if (monster.can_move(xMove, yMove))
	{
		monster.update_location(xMove, yMove);
	}
}


