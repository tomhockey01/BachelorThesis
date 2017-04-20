#include "Timer.h"

#define PIR_OUT1 A1

#define trigPin 2
#define echoPin 3

boolean profPresent = false;

const int wall = 100;

int counter = 0;

int pirState1;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 500;

Timer t;                                              //instantiate the timer object
const unsigned long period1 = 10000;                  // 10 seconds

int readPir(int input) {
  int pirState = analogRead(input);
  return pirState;
}

int readDistance(){
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.println(distance);
  if (distance < wall){
      return true;
  }
  else if(distance >= wall){
    return false;
  }
}

int personCounter(){
  profPresent = readDistance();

  while(profPresent){
    //Serial.println("in while");
    
    pirState1 = readPir(PIR_OUT1);
    if((pirState1 > 600) || (pirState1 < 400)) {
      long pastTime = millis();
      if (pastTime > (lastDebounceTime + debounceDelay)){
        counter ++ ;
      }
      lastDebounceTime = pastTime;
    }
    break;
  }

  //Serial.println(counter);
}

int getPeople(){
  int amountPeople = counter;
  Serial.print("The number of people now is: ");
  Serial.println(amountPeople);
}

void setup() {
  // put your setup code here, to run once: 
  Serial.begin (9600);
  
  pinMode(PIR_OUT1, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  t.every(period1, getPeople);
}

void loop() {
  // put your main code here, to run repeatedly:
  personCounter();
  t.update();
  delay(50);
  
}
