//pins
uint8_t clk = A0;
uint8_t data = A5;
uint8_t led = 4;

//boolean to detect click
bool isClicked = false;


//values only drop below this value when clicked
int bottomThreshold = 977; //determined through trial and error

//values only rise above this value when not clicked
int upperThreshold = 993; //determined through trial and error

void setup() {
  // set up Serial console
  Serial.begin(9600);

  //pin 8 as output - light LED
  pinMode( led, OUTPUT);  
}

void loop() {

  //using values from Data pin
  int dataVoltage = analogRead( data );

  
  if( dataVoltage > upperThreshold ){
    Serial.println( dataVoltage );
  }

  if( dataVoltage < bottomThreshold ){
    Serial.println( "We clicked bois" );
  }

}
