/*
 * Example showing how to send position commands to AX-12A
 */

#include "Arduino.h"
#include "AX12A.h"
#include "Switches.h"

#define DirectionPin 	(10)
#define BaudRate  		(1000000ul)

void Rest(int spd) 
{
  ax12a.moveSpeed(4u, 800, spd);
  ax12a.moveSpeed(3u, 1000, spd);
  ax12a.moveSpeed(2u, 335, spd);
}

void Flip1(int spd) 
{
  ax12a.moveSpeed(4u, 353, spd);
  ax12a.moveSpeed(3u, 815, spd*2);
  ax12a.moveSpeed(2u, 680, spd);
}

void Infrontswitch(int spd)
{
  ax12a.moveSpeed(4u, 283, spd*3);
  ax12a.moveSpeed(3u, 919, spd);
  ax12a.moveSpeed(2u, 640, spd);
}

void GenerickFlip(int spd)
{
  Infrontswitch(spd);
  delay(1500);
  Flip1(spd);
  delay(250);
  Infrontswitch(spd);
  delay(500);
}

void ViperFlip(int spd)
{
  delay(500);
  Rest(spd*2);
  delay(1500);
  Infrontswitch(spd*2);
  delay(200);
  Flip1(spd);
  delay(250);
  Infrontswitch(spd);
  delay(500);
}

void SlowFlip(int spd)
{
  Infrontswitch(spd);
  delay(1500);
  Flip1(spd/3);
  delay(500);
  Infrontswitch(spd/3);
  delay(500);
}

void setup()
{
  ax12a.begin(BaudRate, DirectionPin, &Serial);
}

void loop()
{  
 enum UslessState {Initialize, Idle, /*Allswitch,*/ Switch1, Switch2, Switch3, Switch4, Switch5, Switch6}; 
 UslessState currentState = Initialize;

 int spd = 300;
 int r;
 Switch S1(2, 1023);
 Switch S2(3, 818);
 Switch S3(4, 613);
 Switch S4(5, 409, 8, 9);
 Switch S5(6, 205);
 Switch S6(7, 0, 10, 11);

 while (true){
  switch (currentState) 
  {
    case Initialize:
      S1.set_up();
      S2.set_up();
      S3.set_up();
      S4.set_up();
      S5.set_up();
      S6.set_up();
      
      delay(1000);
      currentState = Idle;
    break;
    
    case Idle:
      if(S1.get_switchstate() == true)      currentState = Switch1;
      else if(S2.get_switchstate() == true) currentState = Switch2;
      else if(S3.get_switchstate() == true) currentState = Switch3;
      else if(S4.get_switchstate() == true) currentState = Switch4;
      else if(S5.get_switchstate() == true) currentState = Switch5;
      else if(S6.get_switchstate() == true) currentState = Switch6;
      else 
      {
        ax12a.moveSpeed(1u, 512, spd);
        Rest(spd/3);
        delay(100);
      }
    break;

    case Switch1:
      ax12a.moveSpeed(1u, S1.get_position(), spd);
      r = random(1-4);
      if(r == 1) SlowFlip(spd);
      else if(r ==2) ViperFlip(spd);
      else GenerickFlip(spd);
      
      currentState = Idle;
    break;

    case Switch2:
      ax12a.moveSpeed(1u, S2.get_position(), spd);
      r = random(1-4);
      if(r == 1) SlowFlip(spd);
      else if(r ==2) ViperFlip(spd);
      else GenerickFlip(spd);
      
      currentState = Idle;
    break;

    case Switch3:
      ax12a.moveSpeed(1u, S3.get_position(), spd);
      r = random(1-4);
      if(r == 1) SlowFlip(spd);
      else if(r ==2) ViperFlip(spd);
      else GenerickFlip(spd);
      
      currentState = Idle;
    break;

    case Switch4:
      ax12a.moveSpeed(1u, S4.get_position(), spd);
      r = random(1-4);
      if(r == 1) SlowFlip(spd);
      else if(r ==2) ViperFlip(spd);
      else GenerickFlip(spd);
      
      currentState = Idle;
    break;

    case Switch5:
      ax12a.moveSpeed(1u, S5.get_position(), spd);
      r = random(1-4);
      if(r == 1) SlowFlip(spd);
      else if(r ==2) ViperFlip(spd);
      else GenerickFlip(spd);
              
      currentState = Idle;
    break;

    case Switch6:
      ax12a.moveSpeed(1u, S6.get_position(), spd);
      r = random(1-4);
      if(r == 1) SlowFlip(spd);
      else if(r ==2) ViperFlip(spd);
      else GenerickFlip(spd);
      
      currentState = Idle;
    break;
  }
 }
}
