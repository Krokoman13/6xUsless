#include "Switches.h"
#include "Arduino.h"

/*
Project: Usless machine, group 4
Authurs: Chiel de Jong, Bram ten Haken
Last update: 31-01-2019 (Adding comments)
 */


Switch::Switch(int pinfromswitch, int coordinates)		//Defining a non-movable switch
{
	this->inpin = pinfromswitch;
	this->position = coordinates;
	this->movable = false;
}

Switch::Switch(int pinfromswitch, int coordinates, int pintoHB1, int pintoHB2) //Defining a movable switch
{
	this->inpin = pinfromswitch;
	this->position = coordinates;
	this->movable = true;
	this->outpinUp = pintoHB1;
	this->outpinDwn = pintoHB2;
}

bool Switch::get_switchstate()	//Checking if the switch is switched on
{
	return digitalRead(this->inpin);
}

int Switch::get_position()	//Getting the position of the switch 0-1023 (0 = -150 degrees, 1023 = +150 degrees)
{
	return this->position;
}

void Switch::set_up() //Set the solenoid to UP (if switch is movable)
{	
	if (this->movable == true) {				//If the switch is non-movable do nothing
		digitalWrite(this->outpinDwn, false);	//Disable downpin
		digitalWrite(this->outpinUp, true);		//Enable uppin
	}
}

void Switch::set_down() 						//Set the solenoid to DOWN (if switch is movable)
{
	if (this->movable == true) {				//If the switch is non-movable do nothing
		digitalWrite(this->outpinUp, false);	//Disable downpin
		digitalWrite(this->outpinDwn, true);	//Enable uppin
	}
}


