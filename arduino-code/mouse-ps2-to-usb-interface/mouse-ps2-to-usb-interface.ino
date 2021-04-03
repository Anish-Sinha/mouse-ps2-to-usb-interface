//analog pins
uint8_t clk_analog = A0;
uint8_t data_analog = A5;

//digital pins
uint8_t clock_digital = 8;
uint8_t data_digital = 7;

void setup() {
  // Set up Serial Console
  Serial.begin(9600);

  //set pins 8 and 7 as input to read from clock and data pin respectively
  pinMode( clock_digital, INPUT);
  pinMode( data_digital, INPUT);
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
