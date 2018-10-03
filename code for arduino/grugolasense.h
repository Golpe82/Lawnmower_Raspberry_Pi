//grugolasense.h

/*The Grugola
  The Grugola should be a Lawnmower created by
  Frank Lautenschlaeger, Daniel Grunow and
  Simon Golpe Varela.
  It is a end projekt for the "state technician school- Berlin"
  This code is for the sensor part of the robot and was created
  by Simon Golpe Varela on 09/26/2018.
  Last change: 09/26/2018
*/

#ifndef __grugolasense_h
#define __grugolasense_h

#include <Arduino.h>

//+++++Tell your board, which sourcecode comes from a .c file;
        #ifdef __cplusplus
        extern "C"{
        #endif

        extern double ultrasonic();//function for ultrasonic measure

        #ifdef __cplusplus
        }
        #endif
//+++++End of the sourcecode from a .c file

#endif
