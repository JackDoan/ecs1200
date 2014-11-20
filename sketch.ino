/*
  Jack Doan, Terry Ford, and Dishron
 
 Reads an analog input pin, maps the result to a range from 0 to 1024
 and uses the result to graph the variations in voltage.
 
 The circuit:
 * P1_0 is connected between a photoresistor and a 330 ohm pullup.
 * P2_2 is conntected to an LED to point at the photoresistor
 
 */

const int analogInPin = P1_0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the sensor
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
         
  // change the analog out value:
  analogWrite(P2_2, wavey);

  counter = sensorValue / 5;
  wavey = wavey + wibble;
  if (wavey == 0 || wavey == 255) {
    wibble = -wibble ; 
  }    
  
  // print the results to the serial monitor:
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
