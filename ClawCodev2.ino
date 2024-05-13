#include <Servo.h>


Servo claw;

// Define stepper motor connections:
#define dirPinX 5
#define dirPinY 6
#define dirPinZ 7
#define stepPinX 2
#define stepPinY 3
#define stepPinZ 4
#define enablePin 8

// Define the button pins
#define button 13
#define button2 12
#define button3 11
#define button4 10

// Define joystick pins
#define joyPinY A1
#define joyPinX A0

// Define joystick thresholds
#define UP_THRESHOLD 400
#define DOWN_THRESHOLD 800
#define LEFT_THRESHOLD 400
#define RIGHT_THRESHOLD 800

// Declare some constants
const int CLAW_SPEED = 30; //Number of milliseconds between updating claw angle
const int MOVE_SPEED = 300; //Lower is faster
const int LOWER_SPEED = 700; //Lower is faster
  
// Declate variables
int clawUpdate = 0;
int clawAngle = 35;

void setup() {
  // Declare pins as output:
  pinMode(stepPinX, OUTPUT);
  pinMode(stepPinY, OUTPUT);
  pinMode(stepPinZ, OUTPUT);
  pinMode(dirPinX, OUTPUT);
  pinMode(dirPinY, OUTPUT);
  pinMode(dirPinZ, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  // Attach the claw
  claw.attach(9);
  claw.write(clawAngle);
  
  // Declare pins as input
  pinMode(button, INPUT);
  pinMode(button2, INPUT);

  // Set the enable pin to HIGH to ensure steppers are off during startup
  // Then set enable pin back to low to ensure steppers are on once booted
  digitalWrite(enablePin, HIGH);
  delay(100);
  digitalWrite(enablePin, LOW);
  
  
}

void loop() {
 
    if(digitalRead(button3) == HIGH){
      clawAngle++;
      clawUpdate = millis() + CLAW_SPEED;
      clawAngle = constrain(clawAngle, 35, 100);
      claw.write(clawAngle);
      delay(CLAW_SPEED);
    }else if (digitalRead(button4) == HIGH){
      clawAngle--;
      clawUpdate = millis() + CLAW_SPEED;
      clawAngle = constrain(clawAngle, 35, 100);
      claw.write(clawAngle);
      delay(CLAW_SPEED);
    }
    
    //Prepare to make stepper motor steps if ANY input is detected
    if (analogRead(joyPinY) < UP_THRESHOLD || analogRead(joyPinY) > DOWN_THRESHOLD || analogRead(joyPinX) < LEFT_THRESHOLD || analogRead(joyPinX) > RIGHT_THRESHOLD || digitalRead(button) == HIGH || digitalRead(button2) == HIGH){
      
    if (analogRead(joyPinY) < UP_THRESHOLD){ 
      digitalWrite(dirPinY, HIGH); 
      digitalWrite(stepPinY, HIGH);
    }
    else if (analogRead(joyPinY) > DOWN_THRESHOLD){
      digitalWrite(dirPinY, LOW);
      digitalWrite(stepPinY, HIGH);
    }
    if (analogRead(joyPinX) < LEFT_THRESHOLD){
      digitalWrite(dirPinX, HIGH);
      digitalWrite(stepPinX, HIGH);

    }
    else if (analogRead(joyPinX) > RIGHT_THRESHOLD){
      digitalWrite(dirPinX, LOW);
      digitalWrite(stepPinX, HIGH);
    }
    if (digitalRead(button) == HIGH){
      delayMicroseconds(LOWER_SPEED);
      digitalWrite(dirPinZ, HIGH);
      digitalWrite(stepPinZ, HIGH);
      delayMicroseconds(LOWER_SPEED);
    }
    else if (digitalRead(button2) == HIGH){
      delayMicroseconds(LOWER_SPEED);
      digitalWrite(dirPinZ, LOW);
      digitalWrite(stepPinZ, HIGH);
      delayMicroseconds(LOWER_SPEED);
    }
    
    //Make sure all the stepper motors step at the same time and speed. 
    delayMicroseconds(MOVE_SPEED);
    digitalWrite(stepPinX, LOW);
    digitalWrite(stepPinY, LOW);
    digitalWrite(stepPinZ, LOW);
    delayMicroseconds(MOVE_SPEED);
    }
 }
