#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"

// constants for game world features
const int EMPTY = 0;
const int SHALL_NOT_PASS = 1;
const int WINNER = 2;
const int WEAPON = 3;

// display characters
const int WIN_CHAR = int('W');
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('o');
const int WEAPON_CHAR = int('S');

// print game world function prototype
void printGameWorld(int x_location_on_board, int y_location_on_board, int character);

// print the game board function prototype
void printGameBoard(int gameBoard[MAX_BOARD_Y][MAX_BOARD_X], int row, int column, int constant);

// captured function prototype
bool captured(Actor const & player, Actor const & monster);

// picked up weapon function prototype
bool pickedUpWeapon(Actor const & player, int gameBoard[MAX_BOARD_Y][MAX_BOARD_X], bool hasWeapon);

// fight function prototype
void fight(Actor & monster, Actor & player, int gameBoard[MAX_BOARD_Y][MAX_BOARD_X]);

// spawn weapon function prototype
void spawnWeapon(int gameBoard[MAX_BOARD_Y][MAX_BOARD_X]);

// spawn winner function prototype
void spawnWinner(int gameBoard[MAX_BOARD_Y][MAX_BOARD_X]);

// move player function prototype
void movePlayer(int key, Actor & player, int gameBoard[MAX_BOARD_Y][MAX_BOARD_X]);

// goose chase function prototype
void gooseChase(Actor & monster, Actor & player, int gameBoard[MAX_BOARD_Y][MAX_BOARD_X]);

// update map function prototype
void updateMap(int gameBoard[MAX_BOARD_Y][MAX_BOARD_X], int value, int character, int x_location, int y_location);

#endif
