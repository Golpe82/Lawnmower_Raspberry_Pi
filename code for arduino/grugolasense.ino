//grugolasense.ino

/*The Grugola
  The Grugola should be a Lawnmower created by
  Frank Lautenschlaeger, Daniel Grunow and
  Simon Golpe Varela.
  It is a end projekt for the "state technician school- Berlin"
  This code is for the sensor part of the robot and was created
  by Simon Golpe Varela on 09/26/2018.
  Last change: 09/26/2018
*/

#include "grugolasense.h"

void setup() {
Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT); 

}

void loop() {
  if(blinky()!=0) Serial.print("blinky failed\n");
  delay(2000);
}
