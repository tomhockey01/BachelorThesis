#define PIEZO A0 


int hydrationCounter = 0;
int sensorReading;
const int threshold = 100;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 750;

void setup() {
  pinMode(PIEZO, INPUT);
  Serial.begin(9600);       // use the serial port
 
}


void loop() {
  // put your main code here, to run repeatedly:
  sensorReading = analogRead(PIEZO);
  
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
