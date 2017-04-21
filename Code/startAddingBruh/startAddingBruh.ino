#include "Timer.h"

#define trigPin 2
#define echoPin 3

#define trigPin2 6
#define echoPin2 5

#define PIEZO A0 

boolean profPresent = false;

const int wall = 100;
const int door = 100;

int counter = 0;

int hydrationCounter = 0;
int sensorReading;
const int threshold = 25;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 500;
unsigned long debounceDelayKnock = 750;

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
  Serial.println(realPeople);
  return realPeople;
}

int countHydration(){
  sensorReading = analogRead(PIEZO);
  
  if (sensorReading >= threshold) {
    long pastTime = millis();
  
    if (pastTime > (lastDebounceTime + debounceDelayKnock)){
      hydrationCounter ++;
    }
    lastDebounceTime = pastTime;
  }
  return hydrationCounter;
}

int getDrinks(){
  int realDrinks = hydrationCounter / 2;
  Serial.print("Number of drinks is: ");
  Serial.println(realDrinks);
  return realDrinks;
}


void setup() {
  // put your setup code here, to run once: 
  Serial.begin (9600);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(PIEZO, INPUT);

  t.every(period1, getPeople);
  t.every(period1, getDrinks);
}

void loop() {
  // put your main code here, to run repeatedly:
  personCounter();
  countHydration();
  t.update();
  delay(50);
  
}
