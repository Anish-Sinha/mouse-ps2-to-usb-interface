//pins
uint8_t clk = A0;
uint8_t data = A5;
uint8_t ledPin = 4;

//values only drop below this value when clicked
int bottomThreshold = 977; //determined through trial and error

//values only rise above this value when not clicked
int upperThreshold = 995; //determined through trial and error

void setup() {
  // set up Serial console
  Serial.begin(9600);

  //pin 8 as output - light LED
  pinMode( ledPin, OUTPUT );  
}

void loop() {

  //using values from Data pin
  int dataVoltage = analogRead( data );

  
  if( dataVoltage > upperThreshold ){
    Serial.println( dataVoltage );
    //Serial.println( " - " );
    digitalWrite( ledPin, LOW );
  }

  if( dataVoltage < bottomThreshold ){
    Serial.println( "We clicked bois" );
    digitalWrite( ledPin, HIGH );
  }

}
