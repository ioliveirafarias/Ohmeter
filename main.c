#include <Arduino.h>

/**********************************
 Globals and constants
**********************************/

#define MS_INTERVAL 500
#define MS_DEBOUNCE_INTERVAL (MS_INTERVAL/5)

#define SENSOR_PIN PB0
#define RELAY_PIN PB2

bool relay_value = LOW;

/**********************************
 Auxiliary functions
**********************************/

bool checkForAClap( int timeLimit_ms ){

  int waiting_start = millis();
  while ( timeLimit_ms > (int)(millis()-waiting_start) ) {
    if ( digitalRead( SENSOR_PIN )) {      
      return true;
    }
  }
  return false;
}

/**********************************
 Main functions
**********************************/

void setup(){
  
  //pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite( RELAY_PIN, relay_value );
}

void loop(){

  delay(MS_INTERVAL*2);

  while( ! digitalRead( SENSOR_PIN ) ){}                            // Awaits for a start clap                           

  delay( MS_DEBOUNCE_INTERVAL );                                    // Check for silence between claps
  if( checkForAClap( MS_INTERVAL - MS_DEBOUNCE_INTERVAL ) ){        
    return;
  }

  if( ! checkForAClap( MS_INTERVAL * 3 ) ){                             // Check for a second clap
    return;
  }

  digitalWrite( RELAY_PIN, relay_value^=1 );                        // Toggle the relay state    
}
