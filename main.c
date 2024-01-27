#include <Arduino.h>
#define SERIAL_BAUDRATE 9600
#define PROBE A0
#define FIXED_RESISTOR 2200
#define INPUT_VOLTAGE 5
#define MAX_ANALOG_READ 1023

/**************************************************
 * Auxiliary functions
**************************************************/

float getVoltage( int analogReading ){
  return ((float)analogReading / (float) MAX_ANALOG_READ) * INPUT_VOLTAGE;
}

float getResistance( int analogReading ){  
  return ((FIXED_RESISTOR * (MAX_ANALOG_READ/(float)analogReading)) )-FIXED_RESISTOR;
}

/**************************************************
 * Main functions
**************************************************/

void setup() {
  Serial.begin( SERIAL_BAUDRATE );
  pinMode( PROBE, INPUT );
}

void loop() {

  int reading = analogRead(PROBE);
  if ( reading == 0 ) {
    Serial.println( "NC / Nothing connected" );
  } else {
    Serial.print("Analog read:");
    Serial.println( reading );
    Serial.print("V:");
    Serial.println( getVoltage(reading) );
    Serial.print("R:");
    Serial.println( getResistance(reading) );    
  }  
  delay(2000);
}
