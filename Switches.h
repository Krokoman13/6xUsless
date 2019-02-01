#pragma once

class Switch			
{
	int inpin;						//=The pin connected to the switch
	int position;					//=The position of the switch (0 = -150 degrees, 1023 = +150 degrees)
	
	bool movable;					//=True when switch is movable by an solenoid

	//Movable switches
	int outpinUp;					//=The pin connected to H-Bridge
	int outpinDwn;					//=The other pin connected to H-Bridge

public:
	Switch(int, int);				//Defining a non-movable switch
	Switch(int, int, int, int);			//Defining a movable switch
	bool get_switchstate();				//Checking if the switch is switched on
	int get_position();				//Getting the position of the switch 0-1023 (0 = -150 degrees, 1023 = +150 degrees)
	void set_up();					//Set the solenoid to UP (if switch is movable)
	void set_down();				//Set the solenoid to DOWN (if switch is movable)
};
