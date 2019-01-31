/*
Project: Usless machine, group 4
Authurs: Chiel de Jong, Bram ten Haken
Last update: 31-01-2019 (Adding solenoid movement, refining ViperFlip, adding comments)
 */

#include "Arduino.h"
#include "AX12A.h"      //Source: https://github.com/ThingType/AX-12A-servo-library
#include "Switches.h"   //This adds the "Switch" class (For more info read "Switches.h")

#define DirectionPin 	(10)
#define BaudRate  		(1000000ul)

void Rest(int spd) //Retracted rest position
{
  ax12a.moveSpeed(4u, 800, spd);
  ax12a.moveSpeed(3u, 1000, spd);
  ax12a.moveSpeed(2u, 335, spd);
}

void Flip1(int spd) //When this function is called after "Infrontswitch" the switch will be flipped
{
  ax12a.moveSpeed(4u, 353, spd);
  ax12a.moveSpeed(3u, 800, spd*2);
  ax12a.moveSpeed(2u, 680, spd/1.5);
}

void Infrontswitch(int spd) //The full arm moves close to the nearest switch
{
  ax12a.moveSpeed(4u, 283, spd*3);
  ax12a.moveSpeed(3u, 919, spd);
  ax12a.moveSpeed(2u, 640, spd);
}

void GenerickFlip(int spd)  //Flip the switch in front of the arm
{
  Infrontswitch(spd);
  delay(1500);
  Flip1(spd);
  delay(250);
  Infrontswitch(spd);
  delay(500);
}

void ViperFlip(int spd) //Retract whole arm,than extend fast and flip switch.
{
  delay(500);
  Rest(spd*2);
  delay(1000);
  ax12a.moveSpeed(4u, 512, spd*6);
  delay(100);
  ax12a.moveSpeed(4u, 288, spd*6);
  ax12a.moveSpeed(3u, 919, spd*4);
  ax12a.moveSpeed(2u, 620, spd*2);
  delay(300);
  ax12a.moveSpeed(2u, 640, spd*2);
  delay(25);
  Flip1(spd);
  delay(250);
  Infrontswitch(spd);
  delay(700);
}

void SlowFlip(int spd)  //Slowely and carefully flip the switch
{
  Infrontswitch(spd);
  delay(1500);
  Flip1(spd/4);
  delay(500);
  Infrontswitch(spd/4);
  delay(500);
}

void setup()
{
  ax12a.begin(BaudRate, DirectionPin, &Serial);   //Initializing the ax12a class
}

void loop()
{  
 enum UslessState {Initialize, Idle, /*Allswitch,*/ Switch1, Switch2, Switch3, Switch4, Switch5, Switch6};  //The state machine subsists of these states
 UslessState currentState = Initialize;   //Start with the "Initialize" state
 
 int spd = 300;  //This is the global speed variable, this can be lowered to a minimum of 0, if this is increased problems might occur
 int r;          //Random value interger
 int i = 0;      //Idle timer
 
 Switch S1(2, 1023);          //Setting all values for all switches, in this case only S4 and S6 are movable with an solenoid
 Switch S2(3, 818);
 Switch S3(4, 613);
 Switch S4(5, 409, 10, 11);
 Switch S5(6, 205);
 Switch S6(7, 0, 8, 9);

 while (true){
  switch (currentState) 
  {
    case Initialize:        //In this state the program makes sure all solenoids are extended and the arm is set to its rest position
      S1.set_up();
      S2.set_up();
      S3.set_up();
      S4.set_up();
      S5.set_up();
      S6.set_up();
      Rest(spd/4);
      delay(1000);
      currentState = Idle;  //Goto the "Idle" state
    break;
    
    case Idle:
      if     (S1.get_switchstate() == true) currentState = Switch1;   //If a switch is detected to be switched on, go to the case for that switch
      else if(S2.get_switchstate() == true) currentState = Switch2;
      else if(S3.get_switchstate() == true) currentState = Switch3;
      else if(S4.get_switchstate() == true) currentState = Switch4;
      else if(S5.get_switchstate() == true) currentState = Switch5;
      else if(S6.get_switchstate() == true) currentState = Switch6;
      else
      {
        ax12a.moveSpeed(1u, 512, spd/3);                              //If none of the switches are switched on slowely return to rest position whilst checking all switches every 100ms
        Rest(spd/3);
        i++;
        if(i > 20) {                                                  //If the "Idle" state has been active for 2 seconds, extend all solenoids
          S1.set_up();
          S2.set_up();
          S3.set_up();
          S4.set_up();
          S5.set_up();
          S6.set_up();
        }
        delay(100);
      }
    break;

    case Switch1:                                     //Switch case: "Switch1" is called upon when switch 1 is detected to be on
      ax12a.moveSpeed(1u, S1.get_position(), spd);    //Move towards this switch
      r = random(1-4);                                //Generate a random number (1, 2 or 3)                  
      if(r == 1) SlowFlip(spd);                       //If the random number = 1 perform "SlowFlip"
      else if(r == 2) ViperFlip(spd);                 //If the random number = 2 perform "ViperFlip"
      else GenerickFlip(spd);                         //If the random number is diffrent perform "GenerickFlip"

      i = 0;                      //Set idle timer to 0
      r = random(1-4);            //Generate random number (1, 2 or 3)   
      if(r == 2) S1.set_down();   //At a random chance of 1:3 retract solenoid for this switch
      
      currentState = Idle;        //Return to the "Idle" state
    break;

    case Switch2:                                     //Switch case: "Switch2" is called upon when switch 2 is detected to be on (For now this state is identical to all other switch states for referance see case: "Switch1")
      ax12a.moveSpeed(1u, S2.get_position(), spd);    
      r = random(1-4);
      if(r == 1) SlowFlip(spd);
      else if(r == 2) ViperFlip(spd);
      else GenerickFlip(spd);
      
      i = 0;
      r = random(1-4);
      if(r == 2) S2.set_down();
 
      currentState = Idle;
    break;

    case Switch3:                                     //Switch case: "Switch3" is called upon when switch 2 is detected to be on (For now this state is identical to all other switch states for referance see case: "Switch1")
      ax12a.moveSpeed(1u, S3.get_position(), spd);
      r = 2;//random(1-4);
      if(r == 1) SlowFlip(spd);
      else if(r == 2) ViperFlip(spd); 
      else GenerickFlip(spd);
      
      i = 0;
      r = random(1-4);
      if(r == 2) S3.set_down();
 
      currentState = Idle;
    break;

    case Switch4:                                     //Switch case: "Switch4" is called upon when switch 2 is detected to be on (For now this state is identical to all other switch states for referance see case: "Switch1")
      ax12a.moveSpeed(1u, S4.get_position(), spd);
      r = random(1-4);
      if(r == 1) SlowFlip(spd);
      else if(r == 2) ViperFlip(spd);
      else GenerickFlip(spd);
      
      i = 0;
      r = random(1-4);
      if(r == 2) S4.set_down();
 
      currentState = Idle;
    break;

    case Switch5:                                     //Switch case: "Switch5" is called upon when switch 2 is detected to be on (For now this state is identical to all other switch states for referance see case: "Switch1")
      ax12a.moveSpeed(1u, S5.get_position(), spd);
      r = random(1-4);
      if(r == 1) SlowFlip(spd);
      else if(r == 2) ViperFlip(spd);
      else GenerickFlip(spd);
              
      i = 0;
      r = random(1-4);
      if(r == 2) S5.set_down();
 
      currentState = Idle;
    break;

    case Switch6:                                     //Switch case: "Switch6" is called upon when switch 2 is detected to be on (For now this state is identical to all other switch states for referance see case: "Switch1")
      ax12a.moveSpeed(1u, S6.get_position(), spd);
      r = random(1-4);
      if(r == 1) SlowFlip(spd);
      else if(r == 2) ViperFlip(spd);
      else GenerickFlip(spd);

      
      i = 0;
      r = random(1-4);
      if(r == 2) S6.set_down();
 
      currentState = Idle;
    break;
  }
 }
}
