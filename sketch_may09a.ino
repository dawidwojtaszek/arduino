#include <AFMotor.h>

AF_DCMotor motor(2,MOTOR12_8KHZ );

const int sensorPin = A5;       
volatile int encoderValue = 0;  
int lastSensorState = LOW;      
unsigned long debounceDelay = 1; 
unsigned long lastDebounceTime = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT_PULLUP);
  motor.setSpeed(200);
}

void loop() {
  int sensorState = digitalRead(sensorPin);

  if (Serial.available() > 0) {
 
    target = Serial.parseInt();
  
    while (Serial.available() > 0) {
      char c = Serial.read();
    }
  }

  encoderHandler(sensorState, target);

  Serial.println(encoderValue);

  if (target != encoderValue) {
    if (target > encoderValue) {
      Serial.println("right");
       motor.setSpeed(200);
      motor.run(FORWARD);
    } else {
      Serial.println("left");
       motor.setSpeed(200);
      motor.run(BACKWARD);
    }
  } else {
    Serial.println("stop");
    motor.run(RELEASE);
  }
}

void encoderHandler(int sensorState, int target) {
  unsigned long currentMillis = millis();

  if (sensorState != lastSensorState) {

    if (currentMillis - lastDebounceTime > debounceDelay) {

      if (sensorState == HIGH) {
        if (target > encoderValue) {
          encoderValue++;
          Serial.println(encoderValue);
        } else {
          if (target != encoderValue) {
            encoderValue--;
            Serial.println(encoderValue);
          }
        }
      }
      lastDebounceTime = currentMillis;
    }
    lastSensorState = sensorState;
  }
}
