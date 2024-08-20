#include <Wire.h>

const int LDR_PIN = A0;
const int US_TRIG_PIN = 10;
const int US_ECHO_PIN = 9;
const int THRESHOLD_LDR = 100;

int pinBin = A0;
int buttonState = 0;

int readLDR() {
    int ldrValue = analogRead(LDR_PIN);
    return ldrValue;
}

float readUltrasonicSensor() {
    digitalWrite(US_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(US_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(US_TRIG_PIN, LOW);
    long duration = pulseIn(US_ECHO_PIN, HIGH);
    float distance = (duration * 0.034 / 2);
    return distance;
}

void setup() {
    Wire.begin(8); // Initialize the I2C communication
    Serial.begin(9600); // Initialize the serial communication
    Wire.onRequest(requestEvent);
    pinMode(US_TRIG_PIN, OUTPUT);
    pinMode(US_ECHO_PIN, INPUT);
    attachInterrupt(0, handle, HIGH); 

}

void loop() {
    delay(1000); 
}

void handle(){
  buttonState != buttonState;
}


void requestEvent() {
    if(buttonState == HIGH){
           int ldrValue = readLDR();
    if (ldrValue < THRESHOLD_LDR) {
        float distance = readUltrasonicSensor();
        if (distance < 15) {
            Wire.write(1); // Send 1 to the master Arduino Uno
        }
        else if(distance >= 15 && distance <= 40){
          Wire.write(2);
        }
        else if(distance >= 50 && distance <= 70 ){
           Wire.write(3);
        }
    }

    else if(ldrValue >= THRESHOLD_LDR){
        Wire.write(4);
    }
    }
}
