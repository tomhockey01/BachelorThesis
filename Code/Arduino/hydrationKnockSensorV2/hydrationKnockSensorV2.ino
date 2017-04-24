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

int countHydration(){
  sensorReading = analogRead(PIEZO);
  
  if (sensorReading >= threshold) {
    long pastTime = millis();
  
    if (pastTime > (lastDebounceTime + debounceDelay)){
      hydrationCounter ++;
    }
    lastDebounceTime = pastTime;
  }
  return hydrationCounter;
}

void loop() {
  Serial.println(countHydration());
}
