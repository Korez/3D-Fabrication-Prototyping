const int switchPin = 2;    // switch input
const int motor1Pin = 9;    // H-bridge motor leg 1
const int motor2Pin = 10;   // H-bridge motor leg 2
const int ledPin1 = 11;     // variable for front led 1
const int ledPin2 = 12;     // variable for front led 2
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 30;  // threshold value to decide when knocked
int sensorReading = 0;      // variable to store the value read from the sensor pin
int switchReading = LOW;    // variable to store the value read from the sensor pin
int state1 = LOW;           // variables used to store the last status of the motor
int state2 = LOW;           // variables used to store the last status of the motor

void setup() {
  pinMode(switchPin, INPUT);   // set the switch as an input
  pinMode(ledPin1, OUTPUT);    // declare the ledPins as OUTPUT
  pinMode(ledPin2, OUTPUT);    // declare the ledPins as OUTPUT
  pinMode(motor1Pin, OUTPUT);  // set motor pins as outputs
  pinMode(motor2Pin, OUTPUT);  // set motor pins as outputs
  Serial.begin(9600);          // use the serial port
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);
  switchReading = digitalRead(switchPin);

  // if switch turned on
  if (switchReading == HIGH) {
    // Turn front LEDs on
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);

    // if motor off
    if ((state1 == LOW && state2 == LOW) || (state1 == HIGH && state2 == LOW)) {
      // if the sensor reading is greater than the threshold forward
      if (sensorReading >= threshold) {
        // toggle the status
        state1 = LOW;
        state2 = HIGH;
        // set states to legs of the H-bridge
        digitalWrite(motor1Pin, state1);
        digitalWrite(motor2Pin, state2);
     }
   }

    // if going forward
    else if (state1 == LOW && state2 == HIGH) {
      // if the sensor reading is greater than the threshold reverse
      if (sensorReading >= threshold) {
       // toggle the status
       state1 = HIGH;
       state2 = LOW;
       // set states to legs of the H-bridge
       digitalWrite(motor1Pin, state1);
       digitalWrite(motor2Pin, state2);
      
      }
    }   
  }

  // if switch turned off
  else {
    // Turn front LEDs off
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    // toggle the status
    state1 = LOW;
    state2 = LOW;
    // set states to legs of the H-bridge
    digitalWrite(motor1Pin, state1);
    digitalWrite(motor2Pin, state2);
  }

  delay(100);  // delay to avoid overloading the serial port buffer

}
