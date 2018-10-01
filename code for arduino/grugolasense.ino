//grugolasense.ino

/*The Grugola
  The Grugola should be a Lawnmower created by
  Frank Lautenschlaeger, Daniel Grunow and
  Simon Golpe Varela.
  It is a end projekt for the "state technician school- Berlin"
  This code is for the sensor part of the robot and was created
  by Simon Golpe Varela on 09/26/2018.
  Last change: 01/10/2018
*/

#include "grugolasense.h"

bool turn= false;
double USdistance=0;

void setup() {
Serial.begin(9600);
pinMode(12, OUTPUT);//Trigger
pinMode(8, INPUT); //echo 

}

void loop() {

  Serial.print("US distance to obstacle: ");
  USdistance=Serial.print(ultrasonic()); //call the function of ultrasonic measure
  Serial.println(" cm");
  if( ultrasonic()<(4.00)) turn=true; //if the distance to obstacle is less as 4 cm, mower must turn
  else turn=false;
  Serial.println("should i turn?");
  Serial.println(turn);
  delay(50);
}
