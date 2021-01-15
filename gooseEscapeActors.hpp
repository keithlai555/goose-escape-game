#ifndef GOOSE_ESCAPE_ACTORS
#define GOOSE_ESCAPE_ACTORS
#include <cmath>
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"

class Actor
{
  private:
    int actorChar;      
    int location_x, location_y;
    int health;

  public:
    Actor()
    {
        actorChar = int('A');
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        health = STARTING_HEALTH;
        put_actor();
    }

    Actor(char initPlayerChar, int x0, int y0, int health0)
    {
        change_char(initPlayerChar);
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        health = health0;
        update_location(x0,y0);
    }
    
    int get_x() const
    {
        return location_x;
    }
    
    int get_y() const
    {
        return location_y;
    }
    
    int get_health() const
    {
    	return health;
	}
    
    string get_location_string() const
    {
        char buffer[80];
        itoa(location_x,buffer,10);
        string formatted_location = "(" + string(buffer) + ",";
        itoa(location_y,buffer,10);
        formatted_location += string(buffer) + ")";
        return formatted_location;
    }
    
    void change_char(char new_actor_char)
    {
        actorChar = min(int('~'),max(int(new_actor_char),int(' ')));
    }

    bool can_move(int delta_x, int delta_y) const
    {
        int new_x = location_x + delta_x;
        int new_y = location_y + delta_y;

        return new_x >= MIN_BOARD_X && new_x <= MAX_BOARD_X
          && new_y >= MIN_BOARD_Y && new_y <= MAX_BOARD_Y;
    }

    void update_location(int delta_x, int delta_y)
    {
        if (can_move(delta_x, delta_y))
        {
            terminal_clear_area(location_x, location_y, 1, 1);
            location_x += delta_x;
            location_y += delta_y;
            put_actor();
        }
    }
    
    void put_actor() const
    {
        terminal_put(location_x, location_y, actorChar);
        terminal_refresh();
    }
    
    // restart the location of actors in top left or bottom right corner of the screen
    void restart_location(string maxOrMin) 
    {
    	if (maxOrMin == "MAX")
    	{
    		terminal_clear_area(location_x, location_y, 1, 1); // erase current location
    		location_x = MAX_BOARD_X; // new x location is right of screen
    		location_y = MAX_BOARD_Y - 1; // new y location is bottom of screen
    		// there is a -1 because the row above the console has invisible walls which 
    		// would interfere with out games so now it is two rows above the console
    		put_actor(); // places the actor in reset position
			terminal_refresh(); // refreshes the screen to show placed actors
		}
		else if (maxOrMin == "MIN")
		{
			terminal_clear_area(location_x, location_y, 1, 1); // erase current location
			location_x = MIN_BOARD_X; // new x location is left of screen
    		location_y = MIN_BOARD_Y; // new y location is top of screen
    		put_actor(); // places the actor in reset position
			terminal_refresh(); // refreshes the screen to show placed actors
		}
	}
	
	// lose health of actors
	void lose_health()
	{
		health = health - 1; // lose health one at a time
	}
	
	// turn health of actor into a string to be printable
	string get_health_string() const
    {
        char value[80];
        itoa(health,value,10);
        string health = string(value);
        return health;
    }
	
};
#endif
