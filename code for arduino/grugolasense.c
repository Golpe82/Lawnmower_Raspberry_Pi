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
#define USTRIGGER 12 //define pin name for trigger
#define USECHO 8  //define pin name for echo
#define USECHOVALUE digitalRead(8)//read ultrasonic echo value


/////////////
//FUNCTIONS//
/////////////

//Function for ultrasonic distance measure
double ultrasonic()
{
  static double distance,anfang,ende,signaltime;
  static unsigned int counter,add;

  for(counter=add=0;counter<10;counter++) //do ten measures...
  {
    digitalWrite(USTRIGGER, LOW); //be sure, trigger is low
    delayMicroseconds(2);
    digitalWrite(USTRIGGER, HIGH); //put trigger high
    delayMicroseconds(10); //for 10 us
    digitalWrite(USTRIGGER,LOW); //put trigger low
  
    while(!USECHOVALUE)//wait for rising edge
    {
        anfang=micros();
    }

    while(USECHOVALUE)//wait for falling edge
    {
        ende=micros();
    }

    signaltime=ende-anfang;  //calculate the time of the signal
    add+=((signaltime/2)*0.03432);  //add measure 0 ´til 9
    delay(50);
  }

  distance=add/counter; //...and then calculate the distance mean value in cm
  return distance; //give the distance to main

}


