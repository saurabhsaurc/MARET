//This file will contain all the functions for reading sensors

//This function returns ultrasonic distance in mm
long ultrasonicMeasurement()
{
	long duration = 0;
	
	// Measure: Put up Trigger...
	digitalWrite(trig_pin, HIGH);
	// ... wait for 11 µs ...
	delayMicroseconds(11);
	// ... put the trigger down ...
	digitalWrite(trig_pin, LOW);
	// ... and wait for the echo ...
	duration = pulseIn(echo_pin, HIGH);
	return (long) (((float) duration / USONIC_DIV) * 10.0);
}

//This function will read line following sensor and store the values into global variables
//White - 0, Black - 1
void readLineSensor()
{
    lf1 = digitalRead(LF_pin_1);
    lf2 = digitalRead(LF_pin_2);
    lf3 = digitalRead(LF_pin_3);
    lf4 = digitalRead(LF_pin_4);
    
    //Hack to tap directly into IR sensor
    //We find that black corresponds to about 100 and white to 375  - but this needs to be tuned according to circumstances
    lf5 = analogRead(LF_pin_5); 
    
    if(lf5 > 300)
      lf5 = 0;
    else
      lf5 = 1;    
}

//This function will read the light sensitive resistors (analog input ) and store in global variable
//Low value - less light, high value - more light
void getLightSensors()
{
    L_left = analogRead(LDR_pin_left);
    L_right = analogRead(LDR_pin_right);
    L_front = analogRead(LDR_pin_front);
}

//This function will read collision avoidance IR sensors
//Obstacle - 1, No Obstacle - 0
void getObstacleSensors()
{
    prox1 = digitalRead(IR_pin_1);
    prox2 = digitalRead(IR_pin_2);
    prox3 = digitalRead(IR_pin_3);
    prox4 = digitalRead(IR_pin_4);
    prox5 = digitalRead(IR_pin_5);
}

void doEncoderL()
{
   encoderLcount = encoderLcount + encoderLdirection;
   thetaL = encoderLcount*radiansPerCount;
}

void doEncoderR()
{
   encoderRcount = encoderRcount + encoderRdirection;
   thetaR = encoderRcount*radiansPerCount;
}

