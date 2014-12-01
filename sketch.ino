/*
  Jack Doan, Terry Ford, and Dishron
 
 Reads an analog input pin, maps the result to a range from 0 to 1024
 and uses the result to graph the variations in voltage, and toggle an
 LED to indicate if IR light has been recieved.
 
 The circuit:
 * P1_0 is connected between a IR photodiode and a 3300 ohm pullup.
 
 */

const int analogInPin = P1_0;  // Analog input pin
const int greenLED = P1_6;
const long baud = 115200;
const int sensitivity = 75; // integer from 0-1024, where 0 is 0 volts across the pullup, and 1024 3.3 volts

int sensorValue = 0;  
int counter = 0;
int lightStatus = 0;

void setup() {
  Serial.begin(baud);
  pinMode(greenLED, OUTPUT);
  digitalWrite(greenLED, 0); 
}

void loop() {
  sensorValue = analogRead(analogInPin);   
  
  if (sensorValue >= 75) {
    delay(20); //debounce it a little
    if (sensorValue >= 75) {
      if (lightStatus == 0) {
        digitalWrite(greenLED, 1);
        lightStatus = 1;
      }
      else {
        digitalWrite(greenLED, 0);
        lightStatus = 0;
      }
    }
  }         

  // print the results to the serial monitor if it is significant:
  if (sensorValue >= 10) {
    counter = sensorValue / 5;
    while (counter != 0) {
      Serial.print("#");
      counter--;
    }
    Serial.println("");
    Serial.println(sensorValue);
  }

  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  delay(10);                     
}
