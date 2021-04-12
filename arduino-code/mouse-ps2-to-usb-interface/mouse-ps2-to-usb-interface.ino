//analog pins
uint8_t clk_analog = A0;
uint8_t data_analog = A5;

//digital pins
uint8_t clk_digital_pin = 3;
uint8_t data_digital_pin = 2;

volatile int testClock = 0;
volatile int testData = 0;

volatile int bitCounter = 0;
volatile uint8_t mouseOutput = 0;

volatile bool command = false;

void setup() {
  // Set up Serial Console
  Serial.begin(115200);

  pinMode( clk_digital_pin, OUTPUT );
  pinMode( data_digital_pin, OUTPUT );

  /*send starting code to mouse here*/
  //pull the clock low to let mouse know host is sending instruction
  digitalWrite( clk_digital_pin, LOW );
  testClock++;
  command = true;
  delayMicroseconds( 100 );

  //release the clock and send start bit on data line
  pinMode( clk_digital_pin, INPUT );
  digitalWrite( data_digital_pin, LOW ); //start bit
  
  //send reset command - 0xFF
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
  //read in device ID - 0xAA

  //set data pin (7) as input to read from data pin
  pinMode( data_digital_pin, INPUT);

  //setting up clock to cause interrupts
  attachInterrupt( digitalPinToInterrupt( clk_digital_pin), readMouse, FALLING );
  //attachInterrupt( digitalPinToInterrupt( data_digital_pin), readData, FALLING );
}

void loop() {
  /*
  if((testClock == 12) || (testClock == 23) ){
    Serial.println( "Clock" );
  }
  */
  //if( bitCounter >= 8 ){
  //  Serial.println( mouseOutput, HEX );
  //}
  //Serial.println( testData );
  delay( 100 );
}

void readMouse() {
  //testClock++;
  
  //if((testClock == 12) || (testClock == 30) ){
  //  Serial.println( testClock );
  //}

  if( (bitCounter < 8) && (testClock > 0) ){
    mouseOutput = mouseOutput | ( digitalRead( data_digital_pin ) << bitCounter );
    bitCounter++;
  }
  if( (bitCounter > 0) && (bitCounter % 8 == 0) ){
    sendPacket( mouseOutput );
    bitCounter++;
  }
}

//
/* transfers mouse packet and resets all bit counters to read next transaction
 * input - the mouse packet bytes
 * output - 
 */
void sendPacket( uint8_t mousePacket ){
  Serial.println( mousePacket, HEX );
}

void readData() {
  testData++;
}
