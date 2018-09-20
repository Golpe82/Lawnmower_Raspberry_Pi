#define OFF 0
	#define ON 1

	//define PIN number
	#define M1LFT 16//motor 1 left. otput pin
	#define M1RGHT 20//motor 1 right. output pin
	#define M2LFT 25//motor 2 left. output pin
	#define M2RGHT 8//motor 2 right. output pin
	#define BTN 12 //button. input pin for obstacle detection
	#define ENIN 21//enable. input pin for  simulation with a second button
	#define ENOUT 7//enable. output pin to enable in of ic l293d
	#define ECHO 18//Ultrasonic data
	#define TRIGGER 23//Ultrasonic trigger

	//define read values
	#define VAL_ENIN gpioRead(ENIN)//read enable input
	#define VAL_BTN gpioRead(BTN)//read button
	#define VAL_ECHO gpioRead(ECHO)//read Ultrasonic data

	//some programming help...
	#define D_MILLIS 1000

//GENERAL FUNCTIONS
	extern signed char oliviaInit();
	extern signed char setPinMode(); //set IOs Mode
	extern signed char IOsInitialise(); //initialise IOs
	extern signed char PUDsInitialise(); //handle PUll Up-down resistors
	
//STATEMACHINE
		//possible states
	typedef enum { AUS=0, VORWAERTS, RUECKWAERTS, DREHEN} state_t;
	
	//parameter of each statemachine state
	typedef struct 
	{
		int m1rechts;
		int m1links;
		int m2rechts;
		int m2links;
		int EnIn;
		int EnOut;
		int Hindernis;
		int Wartezeit;
		int Naechster;
	} motor_state_t;
	
	extern state_t state;
	extern unsigned char oliviaFSM(); 
	extern signed char executeState();	
	
//measure thread

//typedef struct//definition of structure for new Datatype "measure_t"
//{

 // void *pUSfrnt;
 
//}SENSOR;

//extern SENSOR *pSensor;//declaration of pointer to struct "measure_t"
//extern sensor_t sensor;//variable for sensor choice

//extern unsigned char USfrnt;//define variable for switch 'cause Ultrasonic sensor(0 or 1)
//extern void *pUSswitch;//declare pointer for transfer switchstate of USsensor
extern void *USmeasure(void *pTurn);//declare USmeasure thread



#endif
