//olivia´s source

#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include "olivia.h"

/////////////
//FUNCTIONS//
/////////////

	//CALL ALL INIT FUNCTIONS (setpinmode,IOs init, Pullup-down resistors)
	//Returns 0(OK) or -1(failed)
	signed char oliviaInit()
	{
		signed char InitCaseState,failNr;
		
		for(InitCaseState=4,failNr=0;InitCaseState>0;InitCaseState--)
		{
			switch(InitCaseState)
			{
				case 0: 
				case 1: if (PUDsInitialise()!=0) failNr=InitCaseState;
						break;
						
				case 2: if (IOsInitialise()!=0) failNr=InitCaseState;
						break;
					
				case 3: if (setPinMode()!=0) failNr=InitCaseState;
						break;
				
				case 4: if (gpioInitialise() < 0) failNr=InitCaseState;//initialise pigpio
						break;
			}	
		}
		
		if(!failNr) printf("\nOlivia´s initialisation sucessfully");
		
		else 
		{
			printf("\nInitialisation case %d failed\n",failNr);
			InitCaseState=-1;
		}
	
		return InitCaseState;
	}

	//SET MODE FUNCTION. Returns 0(OK) or -1(failed)

	signed char setPinMode()
	{
		signed char IOsSetState,failNr;

		//Sets the GPIO mode, typically input or output. 
		for(IOsSetState=9,failNr=0;IOsSetState>0;IOsSetState--)
		{
			switch(IOsSetState)
			{
				case 0:
				case 1: if(gpioSetMode(BTN,PI_INPUT)) failNr=IOsSetState;      
						break; 
			
				case 2: if(gpioSetMode(ENIN,PI_INPUT)) failNr=IOsSetState;     
						break; 
			
				case 3: if(gpioSetMode(ENOUT,PI_OUTPUT)) failNr=IOsSetState;   
						break;
			
				case 4: if(gpioSetMode(M1LFT,PI_OUTPUT)) failNr=IOsSetState;   
						break;
			
				case 5: if(gpioSetMode(M1RGHT,PI_OUTPUT)) failNr=IOsSetState;  
						break; 
			
				case 6: if(gpioSetMode(M2LFT,PI_OUTPUT)) failNr=IOsSetState;
						break;
			
				case 7: if(gpioSetMode(M2RGHT,PI_OUTPUT)) failNr=IOsSetState;
						break;
			
				case 8: if(gpioSetMode(TRIGGER,PI_OUTPUT)) failNr=IOsSetState;
						break; 
			
				case 9: if(gpioSetMode(ECHO,PI_INPUT)) failNr=IOsSetState;	
						break;
			}
		}	
		
		if(!failNr) printf("\nGPIOs mode were sucessfully selected\n");
		
		else 
		{
			printf("\nGPIO set mode case %d failed\n",failNr);
			IOsSetState=-1;
		}
	
		return IOsSetState;
	}

	//INITIALISE INPUTS-OUTPUTS. Returns 0(OK) or -1(failed)

	signed char IOsInitialise()
	{
		signed char IOsInitState,failNr;
	
		for(IOsInitState=9,failNr=0;IOsInitState>0;IOsInitState--)
		{
			switch(IOsInitState)
			{
				case 0:
				case 1: if(gpioWrite(BTN,0)) failNr=IOsInitState;
						break;
			
				case 2: if(gpioWrite(ENIN,0)) failNr=IOsInitState;
						break;
					
				case 3: if(gpioWrite(ENOUT,0)) failNr=IOsInitState;
						break;
			
				case 4: if(gpioWrite(M1LFT,0)) failNr=IOsInitState;
						break;
					
				case 5: if(gpioWrite(M1RGHT,0)) failNr=IOsInitState;
						break;
			
				case 6: if(gpioWrite(M2LFT,0)) failNr=IOsInitState;
						break;
					
				case 7: if(gpioWrite(M2RGHT,0)) failNr=IOsInitState;
						break;
			
				case 8: if(gpioWrite(TRIGGER,0)) failNr=IOsInitState;
						break;
					
				case 9: if(gpioWrite(ECHO,0)) failNr=IOsInitState;
						break;
			}			
		}
	
		if(!failNr) printf("\nGPIOs were sucessfully initialisated\n");
		
		else 
		{
			printf("\nGPIO initialise case %d failed\n",failNr);
			IOsInitState=-1;
		}
	
		return IOsInitState;
	
	}

	//INITIALISE PULL UP-PULL DOWN. Returns 0(OK) or -1(failed)

	signed char PUDsInitialise()
	{
		signed char PUDsInitState,failNr;
	
		for(PUDsInitState=2,failNr=0;PUDsInitState>0;PUDsInitState--)
		{
			switch(PUDsInitState)
			{
				case 0:
				case 1: if(gpioSetPullUpDown(ECHO, PI_PUD_OFF)) failNr=PUDsInitState;
						break;
			
				case 2: if(gpioSetPullUpDown(TRIGGER, PI_PUD_OFF)) failNr=PUDsInitState;
						break;
			}			
		}
	
		if(!failNr) printf("\nPUDs were sucessfully initialisated\n");
		
		else 
		{
			printf("\nPUD initialise case %d failed\n",failNr);
			PUDsInitState=-1;
		}
	
		return PUDsInitState;
	
	}
	
/////////////////
//STATE MACHINE//
/////////////////

    state_t state=VORWAERTS;//set initial state
	int zaehler=1;//for time delay
	
	// Table for state machine
	motor_state_t state_table[4] = {
 
	//M1r  M1l   M2r   M2l
	//|     |     |     |   EnIn
	//|     |     |     |    |  EnOut
	//|     |     |     |    |   |	Hindernis
	//|     |     |     |    |   |  |  Wartezeit
	//|     |     |     |    |   |  |  |    naechster Zustand        Name
	//----------------------------------------------------------------------
	{OFF , OFF , OFF , OFF , 1,  0, 0, 0,  VORWAERTS},             // AUS
	{ON  , OFF , OFF , ON  , 0,  1, 1, 1,  RUECKWAERTS},           // VORWAERTS
	{OFF , ON  , ON  , OFF , 0,  1, 0, (3*D_MILLIS),  DREHEN},     // RUECKWAERTS
	{ON  , OFF , OFF , OFF , 0,  1, 0, (5*D_MILLIS),  VORWAERTS}}; // DREHEN
	

unsigned char oliviaFSM()
{
    unsigned char FSMok;

	executeState ();

	if (zaehler>0) zaehler--;
    
    else if ( ((state_table[state].EnIn) && VAL_ENIN ) ||
             ((state_table[state].EnOut) && 
             (state_table[state].Hindernis==0)) )
    {
        
		state = state_table[state].Naechster;
		FSMok=0;
		zaehler = state_table[state].Wartezeit;
		printf("\nFSM state= %d",state);
    }
        
	//obstacle
	//turn if	->	 motors enabled		   and (Button-or-Ultrasonic activated)
    else if (state_table[state].EnOut && VAL_BTN)
    {
		state = RUECKWAERTS;
		FSMok=0;
		zaehler = state_table[state].Wartezeit;
		printf("\nFSM state= %d",state);
	}	
		
	//disable
	else if ((state_table[state].EnOut) && VAL_ENIN)
    {
		state= AUS;
		FSMok=0;
		zaehler = state_table[state].Wartezeit;
		printf("\nFSM state= %d",state);
	}

return FSMok;	
  
}


/*static*/ signed char executeState ()
	{
		signed char executeStateState,failNr;
			
		for(executeStateState=4,failNr=0;executeStateState>0;executeStateState--)
		{
			switch(executeStateState)
			{
				case 0: 
				case 1: if( gpioWrite(M1RGHT,(state_table[state].m1rechts))!=0) failNr=executeStateState;
						break;
						
				case 2: if( gpioWrite(M1LFT,(state_table[state].m1links))!=0) failNr=executeStateState;
						break;

				case 3: if( gpioWrite(M2RGHT,(state_table[state].m2rechts))!=0) failNr=executeStateState;
						break;
						
				case 4: if( gpioWrite(M2LFT,(state_table[state].m2links))!=0) failNr=executeStateState;
						break;
			}
		}  
   
		if(!failNr)/* printf("\nFSM state= %d\n",state)*/;
		
		else 
		{
			printf("\nExecute state case %d failed\n",failNr);
			executeStateState=-1;
		}
	
		return executeStateState;
	}


///////////////////
//MEASURES THREAD//
///////////////////

//unsigned char USfrnt=0;//initialise Ultrasonic switchstate value
//void *pUSfrnt=&USfrnt;//define pointer for transfer switchstate of USsensor
//pMeasure=sensor measure_t;



void *USmeasure(void *pTurn)//define measure thread
{

	
	int *turn_pt=(int*)pTurn;//read value of switchstate as uchar
	*turn_pt=0;
	//double distanceUS=0,startUS,stopUS,timediffUS;
	
	//while(1)
	//{
		//gpioTrigger(TRIGGER,10,1); //send pulse
        //startUS=gpioTick(); 
    
        //while (!VAL_ECHO) 
        //{    
            //startUS=gpioTick(); //wait until Echo rising edge
            //printf("\nhier bleibe ich haengen :/\n");
        //}
    
        //while (VAL_ECHO) stopUS=gpioTick(); //wait until Echo falling edge
    
        //timediffUS=stopUS-startUS; //calculate time difference
        //distanceUS=(timediffUS*343)/20000; //calculate distance
        //printf("\ndistance from obstacle= %.2lf cm\n",distanceUS);
        
        double begin, end, signaltime;
        int timeout;
        double tmval;
while(1){
	printf("ping\n");
	/* send 10 uSeconds burst to start measuring */
	gpioWrite(TRIGGER, 1); /* sets gpio high */
	gpioDelay(10);
	gpioWrite(TRIGGER, 0); /* sets gpio high */
	timeout = 0;
	tmval = gpioTick();
	begin = gpioTick();

	while( !VAL_ECHO )
        {
			//printf("bleibe ich hier hängen?\n");
		begin = gpioTick();
		if( (gpioTick() - tmval) >= 5000000 )
                {
			printf("timeout 1!\n");
			timeout = 1;
			break;
                }
		gpioDelay(5);	/* allow CPU to do other jobs */
        }

        if( !timeout )
        {
		while( VAL_ECHO )
		{
			end = gpioTick();
			if( (gpioTick() - tmval) >= 5000000 )
                	{
				printf("timeout 2!\n");
				timeout = 1;
				break;
                	}
			gpioDelay(5);	/* allow CPU to do other jobs */
		}

        	if( !timeout )
        	{
			signaltime = end - begin;
			//      343 meters/second
			// =  34300 cm/second
			// = 343000 mm/second
			// =    343 mm/msecond
			// diff is in usecond
			// distance in mm = signaltime * 343 / 1000 / 2
			printf("distance is %lf mm\n", signaltime*3403/20000);
			// round trip time / 1000000.0 * 34030
		}
	}
    if ((signaltime*3403/20000)<10.) *turn_pt=1;
        //if (distanceUS<10.) *turn_pt=1;
        //gpioSleep(PI_TIME_RELATIVE, 1, 0);
	}	
	
	
	return NULL;
}
