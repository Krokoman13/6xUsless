#pragma once

class Switch
{
	//Normal switches
	int inpin;
	int position;
	
	bool movable;		//=True when switch is movable

	//Movable switches
	int outpinUp;
	int outpinDwn;

public:
	Switch(int, int);
	Switch(int, int, int, int);
	bool get_switchstate();
	int get_position();
	void set_up();
	void set_down();
};
