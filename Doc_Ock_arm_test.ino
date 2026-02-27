#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Joystick pins
const int joyX = A0; 
//const int joyY = A1; 

// Servo channels on PCA9685
const int servo1Channel = 0;
//const int servo2Channel = 1;

// Servo pulse length limits
#define SERVOMIN  150  // Minimum pulse length (0 degrees)
#define SERVOMAX  600  // Maximum pulse length (180 degrees)

// Current servo positions (track where servos are now)
int currentServo1Angle = 0;  
//int currentServo2Angle = 90;

// Speed control (how many degrees to move per loop)
const int servoSpeed = 1;  // Lower = slower, higher = faster

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); 
  delay(10);
  pwm.setPWM(servo1Channel, 0, 0);

  int xValue = analogRead(joyX); 
  currentServo1Angle = map(xValue, 0, 1023, 0, 180); 

void loop() {
  // Read joystick values (0-1023)
  int xValue = analogRead(joyX);
  //int yValue = analogRead(joyY);
  
  // Map joystick values to target servo angles (0-180 degrees)
  int targetServo1Angle = map(xValue, 0, 1023, 0, 180);
 // int targetServo2Angle = map(yValue, 0, 1023, 0, 180);
  
  // Move servo 1 toward target position
  if (currentServo1Angle < targetServo1Angle) {
    currentServo1Angle += servoSpeed;  
    if (currentServo1Angle > targetServo1Angle) {
      currentServo1Angle = targetServo1Angle;  
    }
  } 
  else if (currentServo1Angle > targetServo1Angle && targetServo1Angle < 60) { 
                                                           
    currentServo1Angle -= servoSpeed; 
    if (currentServo1Angle < targetServo1Angle) {
     currentServo1Angle = targetServo1Angle; 
    }
  }
  
  // Move servo 2 toward target position
  /*if (currentServo2Angle < targetServo2Angle) {
    currentServo2Angle += servoSpeed;
    if (currentServo2Angle > targetServo2Angle) {
      currentServo2Angle = targetServo2Angle;
    }
  } else if (currentServo2Angle > targetServo2Angle) {
    currentServo2Angle -= servoSpeed;
    if (currentServo2Angle < targetServo2Angle) {
      currentServo2Angle = targetServo2Angle;
    }
  }*/
  
  // Convert angles to pulse lengths and update servos
  int servo1Pulse = map(currentServo1Angle, 0, 180, SERVOMIN, SERVOMAX);
 // int servo2Pulse = map(currentServo2Angle, 0, 180, SERVOMIN, SERVOMAX);
  
  pwm.setPWM(servo1Channel, 0, servo1Pulse);
 // pwm.setPWM(servo2Channel, 0, servo2Pulse);
  
  delay(15);
  
  Serial.print("Target1: \n"); Serial.print(targetServo1Angle);
  Serial.print(" | Current1: \n"); Serial.print(currentServo1Angle);

  //Serial.print(" | Target2: "); Serial.print(targetServo2Angle);
  //Serial.print(" | Current2: "); Serial.println(currentServo2Angle);
}
