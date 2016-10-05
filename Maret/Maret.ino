/*MARET - a small educational robot
 *Concept, design and development: Saurabh Chatterjee, IIST, Dec 2015
 *This robot demonstrates various concepts related to navigation, control systems and robotics
 *
 *Will interface with MATLAB tool over bluetooth serial port. Following modes will be available
 *Mode 0 - Off
 *Mode 1 - PID control using ultrasonic sensor
 *Mode 2 - Braitenberg vehicle concept and potential fields using light sensitive resistor
 *Mode 3 - Line following ( black on white )
 *Mode 4 - Obstacle collision avoidance using IR sensor
 *
*/

//Input output ports defined
//Motor pins
#define M1_pin_PWM 8
#define M1_pin_B 9
#define M1_pin_A 10
#define M2_pin_PWM 11
#define M2_pin_B 12
#define M2_pin_A 13

//IR sensor for collision avoidance
#define IR_pin_1 15
#define IR_pin_2 16
#define IR_pin_3 17
#define IR_pin_4 18
#define IR_pin_5 19

//Ultrasonic sensor
#define trig_pin 6
#define echo_pin 7
#define USONIC_DIV 58.0

//Line following
//Note pin 5 is faulty and the TTL output needs to be reversed
#define LF_pin_1 34
#define LF_pin_2 32
#define LF_pin_3 30
#define LF_pin_4 28
#define LF_pin_5 A3 //Analog pin A3 is used for LF5

//Light sensitive resistors analog pins
#define LDR_pin_right A2
#define LDR_pin_left A1
#define LDR_pin_front A0

//Variables to store the sensor values
//Line following
//White - 0, Black - 1
int lf1 = 0;
int lf2 = 0;
int lf3 = 0;
int lf4 = 0;
int lf5 = 0;

//Light sensitive resistor
//These will have analog values 0-1023
int L_right = 0;
int L_left = 0;
int L_front = 0;

//Collision avoidance
//Obstacle - 1, No Obstacle - 0
//Proximity sensors - IR
int prox1 = 0;
int prox2 = 0;
int prox3 = 0;
int prox4 = 0;
int prox5 = 0;

//Encoders
long encoderLcount = 0;
int encoderLdirection = 1;
long encoderRcount = 0;
int encoderRdirection = 1;
float thetaL = 0;
float thetaR = 0;
float radiansPerCount = 2*PI/60; //Encoder disc has 30 slots

//Dimensions of wheel radius and radius of bot ( ie half of distance between two wheels )
float radius_wheel = 0.026; //in m
float radius_bot = 0.112; //in m, measured from interior of wheel

//Variables to be used in functions for count,etc.
long prevTimeUltrasonic = 0; //Stores the last time when ultrasonic measurement was taken ( in ms )
long prevTimeEnc = 0; //Time for encoder measurements - not used
float prevDistErrorUltrasonic = 0; //Stores the previous error in distance measurement
float errorSumUltrasonic = 0; //Integral error
float dist = 0; //Distance from target
float alpha = 0.8; //For low pass filter

int mode = 0; //Mode determines which algorithm will be used
int count = 0; //for ultrasonic dist printing
//Position - determined by encoders
float pos_x=0;
float pos_y=0;
float pos_phi = 0;
float prev_thetaL = 0;
float prev_thetaR = 0;

void setup()
{
  //Set up all the pins for inputs and output
  pinMode(M2_pin_PWM,OUTPUT);
  pinMode(M2_pin_A,OUTPUT);
  pinMode(M2_pin_B,OUTPUT);
  pinMode(M1_pin_PWM,OUTPUT);
  pinMode(M1_pin_A,OUTPUT);
  pinMode(M1_pin_B,OUTPUT);
  
  pinMode(IR_pin_1,INPUT);
  pinMode(IR_pin_2,INPUT);
  pinMode(IR_pin_3,INPUT);
  pinMode(IR_pin_4,INPUT);
  pinMode(IR_pin_5,INPUT);
  
  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);  
  
  pinMode(LF_pin_1,INPUT);
  pinMode(LF_pin_2,INPUT);
  pinMode(LF_pin_3,INPUT);
  pinMode(LF_pin_4,INPUT);

  attachInterrupt(1,doEncoderR,CHANGE); // pin 3
  attachInterrupt(2,doEncoderL,CHANGE); // pin 21
  
  Serial.begin(115200); //Note that 115200 is reqd to communicate with bluetooth shield  
}

void loop()
{
  
  if(Serial.available())
  {
    mode = Serial.parseInt();
    Serial.print("Mode: ");
    Serial.println(mode);

    //Reset encoders
    
    encoderLcount = 0;
    encoderRcount = 0;    
  }
  
  if( mode == 0)
  {  runMotors(0,0); //Stop
     delay(10);
  }
    
  if( mode == 1)
  {  pidControlDistance(2.0,0.0,0.5,400); //PID control using ultrasonic sensor
     count = count+1;
     if(count>=100)
     {
        Serial.print("Distance: ");
        Serial.print(dist);
        Serial.println(" mm");
        count =0;
     }
  }
    
  if( mode == 2)
    moveTowardsLight();
    
  if( mode == 3)
    lineFollow();
    
  if( mode == 4)
    avoidObstacles();    

  if( mode == 5)
  { encoderLdirection = 1;
    encoderRdirection = 1;
    //runMotors(255,255);
    testenc();
  }
    
}

