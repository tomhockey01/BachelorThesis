#define PIEZO A0 
#include "Timer.h"


int hydrationCounter = 0;
int sensorReading;
const int threshold = 100;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelayKnock = 500;

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
    Serial.println(sensorReading);
    long pastTime = millis();
  
    if (pastTime > (lastDebounceTime + debounceDelayKnock)){
      hydrationCounter ++;
      Serial.println("noDrink");
    }
    lastDebounceTime = pastTime;
  }
  return hydrationCounter;
}

int getDrinks(){
  int realDrinks = (hydrationCounter);
//  hydrationCounter = 0;
  Serial.println(realDrinks);
  return realDrinks;
}

void loop() {
  countHydration();
  t.update();
  
}
