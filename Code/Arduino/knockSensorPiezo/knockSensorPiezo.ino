// these constants won't change:
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 25;  // threshold value to decide when the detected sound is a knock or not


// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int hydrationCounter = 0;

boolean drink = false;
boolean drinkState;
boolean lastDrinkState = false;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int readHydration(){
  sensorReading = analogRead(knockSensor);
  if (sensorReading >= threshold) {
    return true;
  }
  else{
    return false;  
  }
}

void setup() {
  Serial.begin(9600);       // use the serial port
 
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  drink = readHydration();
  if (drink){
    if (drink != lastDrinkState){
      lastDebounceTime = millis();
      Serial.println(lastDebounceTime);
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay){
      Serial.println("hoi");  
      if(drink != drinkState){
        drinkState = drink;
        Serial.println("hoi2");
        if (drinkState){
          hydrationCounter ++;
          Serial.println(hydrationCounter);
        }
      }
    }
    lastDrinkState = drink;
  }
  else{
    drink = false;
    drinkState = drink;
    lastDrinkState = drink;
  }
  
  delay(50); 
  Serial.println(hydrationCounter); 
}
