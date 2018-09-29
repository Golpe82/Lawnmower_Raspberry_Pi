//grugolasense.c

/*The Grugola
  The Grugola should be a Lawnmower created by
  Frank Lautenschlaeger, Daniel Grunow and
  Simon Golpe Varela.
  It is a end projekt for the "state technician school- Berlin"
  This code is for the sensor part of the robot and was created
  by Simon Golpe Varela on 09/26/2018.
  Last change: 09/26/2018
*/

#include <Arduino.h>
#include <stdio.h>
#include "grugolasense.h"


int blinky()
{
  int blinkstate;
  blinkstate=digitalRead(LED_BUILTIN);
  digitalWrite(LED_BUILTIN, LOW);   
  delay(1000);                      
  digitalWrite(LED_BUILTIN, HIGH);

  return blinkstate;
}

