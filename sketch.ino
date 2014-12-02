/*
  Jack Doan, Terry Ford, and Dishron
 
 Reads an analog input pin, maps the result to a range from 0 to 1024
 and uses the result to graph the variations in voltage, and toggle an
 LED to indicate if IR light has been recieved.
 
 The circuit:
 * P1_0 is connected between a IR photodiode and a 3300 ohm pullup.
 
 */

const int infraLED = P1_0;
const int analogInPin = P1_4;  // Analog input pin
const long baud = 115200;
const int sensitivity = 75; // integer from 0-1024, where 0 is 0 volts across the pullup, and 1024 3.3 volts

volatile bool infraState = 0;
int sensorValue = 0;  
int counter = 0;
int lightStatus = 0;

void infraOnOff();

void setup() {
  Serial.begin(baud);
  pinMode(infraLED, OUTPUT);
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, 0);
  attachInterrupt(PUSH2, infraOnOff, FALLING); 
}

void loop() {
  sensorValue = analogRead(analogInPin);   
  
  if (sensorValue >= 75) {
    delay(20); //debounce it a little
    if (sensorValue >= 75) {
      if (lightStatus == 0) {
        digitalWrite(GREEN_LED, 1);
        lightStatus = 1;
      }
      else {
        digitalWrite(GREEN_LED, 0);
        lightStatus = 0;
      }
    }
  }         

  // print the results to the serial monitor if it is significant:
  /*  DEBUG
  if (sensorValue >= 10) {
    counter = sensorValue / 5;
    while (counter != 0) {
      Serial.print("#");
      counter--;
    }
    
    Serial.print(" - ");
    Serial.print(sensorValue);
    Serial.println("");
  }
  */
  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  delay(10);                     
}

void infraOnOff() {
  infraState = !infraState;
  digitalWrite(infraLED, infraState);
}
  
