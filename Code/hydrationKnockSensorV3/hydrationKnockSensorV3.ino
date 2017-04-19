#define PIEZO A0 
#include "Timer.h"


int hydrationCounter = 0;
int sensorReading;
const int threshold = 75;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 750;

Timer t;                                              //instantiate the timer object
const unsigned long period1 = 10000;                  // 10 seconds

void setup() {
  Serial.begin(9600);       // use the serial port
  pinMode(PIEZO, INPUT);
  t.every(period1, getDrinks);
 
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

int getDrinks(){
  int realDrinks = hydrationCounter / 2;
  Serial.println(realDrinks);
  return hydrationCounter;
  
}

void loop() {
  countHydration();
  t.update();
}
