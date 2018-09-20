//olivia´s main

#include <stdio.h>
#include <pigpio.h>
#include "olivia.h"


//Main function
int main (int argc, char *argv[])
{
	int turn=0;
	pthread_t *pUSmeasure;
	int lastState = -1;
	
	if(oliviaInit()!=0) return (-1);//initialise olivia
	pUSmeasure=gpioStartThread(USmeasure,&turn);//initialise measure thread
	//printf("\nmust i turn?= %d\n",turn);
	while (1)
	{
		//if(oliviaFSM()!=0) return (-1);// initialise state machine. im olivia.h und olivia.c enthalten
		if( lastState != turn )
		{
			lastState = turn;
			printf("\nmust i turn?= %d",turn);
		}
        
        gpioDelay(2*D_MILLIS);
	
	}
	
	gpioStopThread(pUSmeasure);//stop measure thread
	gpioTerminate(); 

return 0;
}
