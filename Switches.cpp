#include "Switches.h"
#include "Arduino.h"

Switch::Switch(int pinfromswitch, int coordinates)		//Defining a non-movable 
{
	this->inpin = pinfromswitch;
	this->position = coordinates;
	this->movable = false;
}

Switch::Switch(int pinfromswitch, int coordinates, int pintoHB1, int pintoHB2)
{
	this->inpin = pinfromswitch;
	this->position = coordinates;
	this->movable = true;
	this->outpinUp = pintoHB1;
	this->outpinDwn = pintoHB2;
}

bool Switch::get_switchstate()
{
	return digitalRead(this->inpin);
}

int Switch::get_position()
{
	return this->position;
}

void Switch::set_up() {
	if (this->movable == true) {
		digitalWrite(this->outpinDwn, false);
		digitalWrite(this->outpinUp, true);
	}
}

void Switch::set_down() {
	if (this->movable == true) {
		digitalWrite(this->outpinUp, false);
		digitalWrite(this->outpinDwn, true);
	}
}


