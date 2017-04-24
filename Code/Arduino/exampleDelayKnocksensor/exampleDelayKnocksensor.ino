const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 50;

int hydrationCounter = 0;
int sensorReading;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 750;

void setup() {
  Serial.begin(9600);       // use the serial port
 
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorReading = analogRead(knockSensor);
  
  if (sensorReading >= threshold) {
    long pastTime = millis();
  
    if (pastTime > (lastDebounceTime + debounceDelay)){
      hydrationCounter ++;
      Serial.println(hydrationCounter);
      //Serial.println(sensorReading);
    }
    lastDebounceTime = pastTime;
  }
}
