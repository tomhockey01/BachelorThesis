

// constants won't change. Used here to set a pin number :
const int ledPin =  LED_BUILTIN;// the number of the LED pin

// Variables will change :
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
// const long interval = 5000;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
}

int timer(int time){
  const long interval = time;
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    return "DONE";
  }
}

void loop() {
  char test = timer(5000);
  Serial.println (millis());
  Serial.println(test);
}
