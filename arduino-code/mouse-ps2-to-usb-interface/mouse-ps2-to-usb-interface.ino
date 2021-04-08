//analog pins
uint8_t clk_analog = A0;
uint8_t data_analog = A5;

//digital pins
uint8_t clk_digital_pin = 3;
uint8_t data_digital_pin = 2;

volatile int testclock = 0;
int testdata = 0;

void setup() {
  // Set up Serial Console
  Serial.begin(115200);

  pinMode( clk_digital_pin, OUTPUT );
  pinMode( data_digital_pin, OUTPUT );

  /*send starting code to mouse here*/
  //pull the clock low to let mouse know host is sending instruction
  digitalWrite( clk_digital_pin, LOW );
  delayMicroseconds( 100 );

  //release the clock and send start bit on data line
  pinMode( clk_digital_pin, INPUT );
  digitalWrite( data_digital_pin, LOW ); //start bit
  

  //send enable reporting data bits to mouse - 0xFA
  /*if( digitalRead( !clk_digital_pin ) ){ //if the clock has gone low, start message
    // 0xFA
    for( int i = 0; i < 8; i++ ){
      digitalWrite( data_digital_pin, HIGH );
      delayMicroseconds( 
    }

    // Parity Bit

    // Stop Bit

    // Acknowledge Bit
  } */

  /* end of starting code to mouse */

  //set data pin (7) as input to read from data pin
  pinMode( data_digital_pin, INPUT);

  //setting up clock to cause interrupts
  attachInterrupt( digitalPinToInterrupt( clk_digital_pin), readMouse, FALLING );

  attachInterrupt( digitalPinToInterrupt( data_digital_pin), readData, FALLING );
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

  //int clockValue = digitalRead(clk_digital_pin);
  //int dataValue = digitalRead(data_digital_pin);
  /*
  if(digitalRead(clk_digital_pin) == 0){
    //Serial.println( "Clock went down" );
    testclock++;
  }

  if(digitalRead(data_digital_pin) == 0){
    //Serial.print( "Data went down" );
    testdata++;
  }

  if((testclock == 12) || (testclock == 23) ){
    Serial.println( "Clock" );
  }
  */
  //delay microseconds
  Serial.println( testdata );
  delay( 100 );
}

void readMouse() {
  testclock++;
  
  //if((testclock == 12) || (testclock == 30) ){
  //  Serial.println( testclock );
  //}
}

void readData() {
  testdata++;
}


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
