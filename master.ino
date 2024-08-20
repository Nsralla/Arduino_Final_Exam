#include <Wire.h>

int ledPin1 = 8; 
int ledPin2 = 9; 
unsigned long previousMillis = 0;
unsigned long interval = 1500; 

int intervalCounter = 0; 
bool led1State = HIGH; 
bool led2State = LOW; 

void setup() {
  Wire.begin(); // Initialize the I2C communication as Master
  Serial.begin(9600); // Initialize serial communication
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}


void loop() {
  Wire.beginTransmission(8); 
  Wire.requestFrom(8, 1); 
  
  if (Wire.available()) { // Check if data is available to read
    int receivedNumber = Wire.read(); // Read the number received from the slave
    
    if (receivedNumber == 1) { // Check if received number is 1
      digitalWrite(ledPin1, HIGH); // Turn on the first LED
      digitalWrite(ledPin2, HIGH); // Turn on the second LED
    }

     else if(receivedNumber == 2)
    {
       unsigned long currentMillis = millis(); // Get the current time
       if (currentMillis - previousMillis >= interval) { // Check if it's time to change the LED state
         previousMillis = currentMillis; // Save the last time the LED state was changed
         digitalWrite(ledPin1, !digitalRead(ledPin1)); // Toggle the LED state
       }
       if(currentMillis - previousMillis >= 3000){
          previousMillis = currentMillis; // Save the last time the LED state was changed
         digitalWrite(ledPin2,!digitalRead(ledPin2) );
       }
    }
    if (receivedNumber == 3) {
    if (intervalCounter % 2 == 0) {
        if (led1State) {
            // Turn off LED1 and turn on LED2
                led1State = LOW;
                led2State = HIGH;
                digitalWrite(ledPin1,  led1State); // Turn on the first LED
                digitalWrite(ledPin2, led2State); // Turn on the second LED

            } else {
                // Turn on LED1 and turn off LED2
                led1State = HIGH;
                led2State = LOW;
                digitalWrite(ledPin1,  led1State); // Turn on the first LED
                digitalWrite(ledPin2, led2State); // Turn on the second LED
            }
        }
        intervalCounter++; 
    }

    if(receivedNumber == 4){
      
      digitalWrite(ledPin1, LOW); // Turn on the first LED
      digitalWrite(ledPin2, LOW); // Turn on the second LED
      noInterrupts();
      TCCR1B &= ~(1 << CS10); // Clear CS10 bit
      TCCR1B &= ~(1 << CS11); // Clear CS11 bit
      TCCR1B |= (1 << CS12);  // Set CS12 bit to 1

      // Enable Timer1 overflow interrupt
      TIMSK1 |= (1 << TOIE1);
      interrupts();

    }
    delay(1000); 
  }
}


ISR(TIMER1_OVF_vect) 
{
  TCNT1 = 0; // preload timer
  digitalWrite(13, digitalRead(13) ^ 1);
}
