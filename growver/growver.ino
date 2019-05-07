/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->  http://www.adafruit.com/products/1438
*/


//////////////////
// UTILITY VARS //
//////////////////

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <SimpleKalmanFilter.h>
#define MOTOR_PIN 4
const long SERIAL_REFRESH_TIME = 10;
long refresh_time;



/////////////////
// SENSOR VARS //
/////////////////

#define LDR1 A0
#define LDR2 A1
#define LDR3 A2
#define LDR4 A3

SimpleKalmanFilter simpleKalmanFilter1(2, 2, 0.01);
SimpleKalmanFilter simpleKalmanFilter2(2, 2, 0.01);
SimpleKalmanFilter simpleKalmanFilter3(2, 2, 0.01);
SimpleKalmanFilter simpleKalmanFilter4(2, 2, 0.01);

int goodLightThreshold = 80; //Out of 100

////////////////
// MOTOR VARS //
////////////////
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

enum state {
  FWD,
  LEFT,
  RIGHT,
  OFF
};

state current_direction = OFF;
state prev_direction = OFF;
int spd = 0;
int max_spd = 255;

/////////////////
// TIMING VARS //
/////////////////

long checkpoint = 0;
int interval = 7000;

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

void setup() {
  //sleepydog setup
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Show we're awake

  setupMotor();
  
} 

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

void loop() {

  handleDistance();
  
  int values[4];
  getAnalogValues(values);
  
  //printAnalogValues(values[0], values[1], values[2], values[3]);
  
  checkStates();

  handleMotor(values[0], values[1], values[2], values[3]);

}



void checkStates(){
  if(current_direction != prev_direction){
      spd = 0;
      prev_direction = current_direction;
  }
}
