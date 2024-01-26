#include <Arduino.h>
#define SERIAL_BAUDRATE 9600
#define PROBE A0
#define INPUT_VOLTAGE 5 
#define MAX_ANALOG_READ 1023
#define NC_ANALOG_READ_THRESHOLD 1022

/**************************************************
 * Auxiliary functions
**************************************************/

float getVoltage( int analogReading ){
  return (analogReading * INPUT_VOLTAGE) / (float) MAX_ANALOG_READ;
}

/**************************************************
 * Main functions
**************************************************/

void setup() {
  Serial.begin( SERIAL_BAUDRATE );
  pinMode( PROBE, INPUT_PULLUP );
}

void loop() {

  int reading = analogRead(PROBE);
  if ( reading >= NC_ANALOG_READ_THRESHOLD ) {
    Serial.println( "NC / Nothing connected" );
  } else {
    Serial.print("V:");
    Serial.println( getVoltage(reading) );
  }  
  delay(2000);
}
