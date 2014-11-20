/*
  Analog input, analog output, serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground
 
 */

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = GREEN_LED; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the sensor
int outputValue = 0;        // value output to the PWM (analog out)
int counter = 0;
int wavey = 0;
int wibble = 5;
void setup() {
  Serial.begin(115200);
  pinMode(P2_2, OUTPUT);
  digitalWrite(P2_2, 0); 
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);           
  analogWrite(P2_2, wavey);
  // print the results to the serial monitor:
  counter = sensorValue / 5;
  wavey = wavey + wibble;
  if (wavey == 0 || wavey == 255) {
    wibble = -wibble ; 
  }    

  while (counter != 0) {
    Serial.print("#");
    counter--;
  }
  Serial.println(" ");

  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(10);                     
}
