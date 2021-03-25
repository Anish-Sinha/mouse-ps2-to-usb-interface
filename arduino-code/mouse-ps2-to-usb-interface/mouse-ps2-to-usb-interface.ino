uint8_t clk = A0;
uint8_t data = A5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //pin 8 input
  pinMode( 8, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print( analogRead(clk) );
  Serial.print( " " );
  Serial.println( analogRead(data) );
  //Serial.println( digitalRead(8) );

  //wait for analog-to-digital converter to stabilize 
  //since last reading
  //delay(2);
}
