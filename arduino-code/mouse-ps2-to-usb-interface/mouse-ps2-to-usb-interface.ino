//analog pins
uint8_t clk_analog = A0;
uint8_t data_analog = A5;

//digital pins
uint8_t clock_digital = 8;
uint8_t data_digital = 7;

void setup() {
  // Set up Serial Console
  Serial.begin(115200);

  //set pins 8 and 7 as input to read from clock and data pin respectively
  pinMode( clock_digital, INPUT);
  pinMode( data_digital, INPUT);

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
  Serial.print( analogRead(clk_analog) );
  Serial.print( " " );
  Serial.println( analogRead(data_analog) );
  
  //wait for analog-to-digital converter to stabilize 
  //since last reading
  //delay(2);
}
