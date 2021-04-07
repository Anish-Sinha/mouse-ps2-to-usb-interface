//analog pins
uint8_t clk_analog = A0;
uint8_t data_analog = A5;

//digital pins
uint8_t clk_digital_pin = 8;
uint8_t data_digital_pin = 7;

void setup() {
  // Set up Serial Console
  Serial.begin(115200);

  pinMode( clk_digital_pin, OUTPUT );
  pinMode( data_digital_pin, OUTPUT );

  /*send starting code to mouse here*/
  //pull the clock low to let mouse know host is sending instruction
  digitalWrite( clk_digital_pin, HIGH );
  delayMicroseconds( 100 );

  //release the clock and send start bit on data line
  pinMode( clk_digital_pin, INPUT );
  digitalWrite( data_digital_pin, LOW );
  

  //send enable reporting data bits to mouse - 0xFA
  if( digitalRead( !clk_digital_pin ) ){ //if the clock has gone low, start message
    // Start bit

    // 0xFA

    // Parity Bit

    // Stop Bit

    // Acknowledge Bit
  }

  /* end of starting code to mouse */









  //set pins 8 and 7 as input to read from clock and data pin respectively
  //pinMode( clk_digital_pin, INPUT);
  pinMode( data_digital_pin, INPUT);

  /* Test */
  //changing analog Read prescalar from 128 to 64
//  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2)); // clear prescaler bits
  //Ahhhh why doesn't this work??!
  // uncomment as required
  
//  ADCSRA |= bit (ADPS0);                               //   2  
//  ADCSRA |= bit (ADPS1);                               //   4  
//  ADCSRA |= bit (ADPS0) | bit (ADPS1);                 //   8  
//  ADCSRA |= bit (ADPS2);                               //  16 
//  ADCSRA |= bit (ADPS0) | bit (ADPS2);                 //  32 
//  ADCSRA |= bit (ADPS1) | bit (ADPS2);                 //  64 
//  ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   // 128

  /* Test */
}

void loop() {
  //print out: analog clock voltage + " " + analog data voltage
  //Serial.print( analogRead(clk_analog) );
  //Serial.print( " " );
  //Serial.println( analogRead(data_analog) );
  //wait for analog-to-digital converter to stabilize 
  //since last reading
  //delay(2);

  //print out: digialt clock voltage + " " + digital data voltage
  //Serial.print( digitalRead(clk_digital_pin) );
  //Serial.print( " " );
  //Serial.println( digitalRead(data_digital_pin) );
  
  /* Test */

  int clockValue = digitalRead(clk_digital_pin);
  int dataValue = digitalRead(data_digital_pin);

  if(clockValue == 0){
    Serial.println( "Clock went down" );
  }

  if(dataValue == 0){
    Serial.print( "Data went down" );
  }

  //delay microseconds
}
