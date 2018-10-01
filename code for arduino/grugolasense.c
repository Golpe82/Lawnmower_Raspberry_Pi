//grugolasense.c

/*The Grugola
  The Grugola should be a Lawnmower created by
  Frank Lautenschlaeger, Daniel Grunow and
  Simon Golpe Varela.
  It is a end projekt for the "state technician school- Berlin"
  This code is for the sensor part of the robot and was created
  by Simon Golpe Varela on 09/26/2018.
  Last change: 01/10/2018
*/

#include <Arduino.h>
#include "grugolasense.h"

///////////
//DEFINES//
///////////

//for ultrasonic function
#define USTRIGGER 12
#define USECHO 8
#define USECHOVALUE digitalRead(8)//read ultrasonic echo value

//Function for ultrasonic distance measure
double ultrasonic()
{
  double USdistance,anfang,ende,signaltime;

  digitalWrite(USTRIGGER, LOW); //be sure, trigger is low
  delayMicroseconds(2);
  digitalWrite(USTRIGGER, HIGH); //put trigger high
  delayMicroseconds(10); //for 10 us
  digitalWrite(USTRIGGER,LOW); //put trigger low
  anfang=micros();
  
  while(!USECHOVALUE)//wait for rising edge
  {
      anfang=micros();
      delayMicroseconds(5);
  }

  while(USECHOVALUE)//wait for falling edge
  {
      ende=micros();
      delayMicroseconds(5);
  }

  signaltime=ende-anfang;  //calculate the time of the signal
  USdistance=(signaltime/2)*0.03432;  //calculate the distance in cm

  return USdistance;
}


