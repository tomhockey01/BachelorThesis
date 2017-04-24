#include "Timer.h"

#define ldrPin A2 

Timer t;                                              //instantiate the timer object
const unsigned long period1 = 10000;                  // 10 seconds

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(ldrPin, INPUT);

  t.every(period1, getLight);
}

void loop() {
  // put your main code here, to run repeatedly:
  t.update();
}

float getLight(){
  float total = 0;
  for (int i=0; i<101; i++){
    int currentRead = analogRead(ldrPin); 
    total = total + currentRead;
  }
  float averageRead = (total/100);
  Serial.println(averageRead);
}


