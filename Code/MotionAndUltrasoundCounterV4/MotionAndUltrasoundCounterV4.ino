#include "Timer.h"

#define trigPin 2
#define echoPin 3

#define trigPin2 9
#define echoPin2 8

boolean profPresent = false;

const int wall = 100;
const int door = 100;

int counter = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 500;

Timer t;                                              //instantiate the timer object
const unsigned long period1 = 10000;                  // 10 seconds

int readDistance(int pin1, int pin2){
  long duration, distance;
  digitalWrite(pin1, LOW);  
  delayMicroseconds(2); 
  digitalWrite(pin1, HIGH);
  
  delayMicroseconds(10); 
  digitalWrite(pin1, LOW);
  duration = pulseIn(pin2, HIGH);
  distance = (duration / 2) / 29.1;
  //Serial.println(distance);
  if (distance < wall){
      return true;
  }
  else if(distance >= wall){
    return false;
  }
}

int personCounter(){
  profPresent = readDistance(trigPin, echoPin);

  while(profPresent){
    //Serial.println("in while");
    
    boolean personIn = readDistance(trigPin2, echoPin2);
    if(personIn) {
      long pastTime = millis();
      if (pastTime > (lastDebounceTime + debounceDelay)){
        counter ++ ;
      }
      lastDebounceTime = pastTime;
    }
    break;
  }
}

int getPeople(){
  int realPeople = counter / 2;
  Serial.print("The number of people now is: ");
  Serial.println(amountPeople);
  return realPeople;
}

void setup() {
  // put your setup code here, to run once: 
  Serial.begin (9600);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
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
