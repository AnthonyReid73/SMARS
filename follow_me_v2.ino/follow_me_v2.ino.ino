/*
 * Updated by Anthony Reid 18/01/2025
 * Code now uses Adafruit Motor (V1!) Library, and HW-130 motor control board

 * Original Follow me code by Kevin McAleer 23 September 2020
 * Updated 26 September 2020 - delay is shorter
 * Updated 04 October 2020 - added the beep and definitions for official and fundomoto motorshields 
 */

#include <AFMotor.h>

// Uncomment exactly one of the defines below to select the correct board
#define OFFICIAL_ARDUINO_SHIELD // I'm using a clone, but this will do.
//#define FUNDUMOTO_SHIELD

#ifdef OFFICIAL_ARDUINO_SHIELD
  #define MOTORSHIELD "Official Arduino"
#endif

#ifdef FUNDUMOTO_SHIELD
  #define buzzer 4
  #define MOTORSHIELD "Fundumoto"
#endif

// Pin definitions for Ultrasonic Sensor
const int TRIGGER_PIN = A2;
const int ECHO_PIN    = A3;

// Delay between ultrasonic pings, in milliseconds
const unsigned long SENSOR_DELAY_MS = 1000;

// Time for motors to run, in milliseconds
const unsigned long MOTOR_RUN_MS = 1000;

// Create a new object for each motor (ports on the Adafruit shield)
AF_DCMotor M1(1);
AF_DCMotor M2(2);

// Function to measure the distance via ultrasonic sensor
float measureDistance() {
  // Trigger the sensor
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIGGER_PIN, LOW);
  
  // Read the echo
  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Convert echo time to distance (in cm)
  float distance = (duration / 2.0) / 29.0;
  
  // Optional delay before next measurement
  delay(SENSOR_DELAY_MS);
  
  return distance;
}

#ifdef FUNDUMOTO_SHIELD
void beep(float distance) {
  // The closer the distance, the longer the beep.
  // Avoid dividing by zero or negative distances.
  if (distance <= 0) distance = 1; 
  
  unsigned long beepTime = (unsigned long)(MOTOR_RUN_MS / (distance * 2.0));
  
  digitalWrite(buzzer, HIGH);
  delay(beepTime);
  digitalWrite(buzzer, LOW);
}
#else
// Empty beep function when no buzzer is defined.
void beep(float distance) {
  // no-op
}
#endif

// Move robot forward for a fixed duration
void forward() {
  Serial.println("Forwards");
  
  M1.setSpeed(255);
  M2.setSpeed(255);

  M1.run(FORWARD);
  M2.run(FORWARD);

  delay(MOTOR_RUN_MS);

  // Stop
  M1.setSpeed(0);
  M2.setSpeed(0);
}

// Move robot backward for a fixed duration
void backward() {
  Serial.println("Backwards");

  M1.setSpeed(255);
  M2.setSpeed(255);

  M1.run(BACKWARD);
  M2.run(BACKWARD);

  delay(MOTOR_RUN_MS);

  // Stop
  M1.setSpeed(0);
  M2.setSpeed(0);
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  #ifdef FUNDUMOTO_SHIELD
    pinMode(buzzer, OUTPUT);
    // Simple test beep at startup
    beep(10);
  #endif

  Serial.println("SMARS Robot - Follow Me code");
  Serial.print("Motorshield type: ");
  Serial.println(MOTORSHIELD);
}

void loop() {
  // Check distance
  float distance = measureDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 5) {
    // If less than 5cm, move backward
    backward();
  } 
  else if (distance > 10) {
    // If more than 10cm, move forward
    forward();
  } 
  else {
    // Otherwise, do nothing (stay still)
    Serial.println("Stay still");
  }

  // Beep in proportion to distance
  beep(distance);
}
