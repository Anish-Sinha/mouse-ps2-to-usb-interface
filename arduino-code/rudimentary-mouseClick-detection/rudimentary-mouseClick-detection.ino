//pins
uint8_t clk = A0;
uint8_t data = A5;
uint8_t ledPin = 4;

//boolean for click status
boolean isClicked = false;

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

  //when the mouse button is finally release
  if( (dataVoltage > upperThreshold) && (isClicked) ){
    //Serial.println( dataVoltage );
    Serial.println( "Button released bois" );

    //turn off click indicator LED
    digitalWrite( ledPin, LOW );

    //mouse button no longer pressed down
    isClicked = false;
  }

  //when the mouse button was first pressed down
  if( (dataVoltage < bottomThreshold) && (!isClicked) ){
    Serial.println( "We clicked bois" );

    //turn on click indicator LED
    digitalWrite( ledPin, HIGH );

    //mouse button is currently pressed down
    isClicked = true;
  }

}
