#include "Timer.h"
#include <dht.h>;
#include <SPI.h>
#include <SD.h>

#define trigPin 5
#define echoPin 6

#define trigPin2 2
#define echoPin2 3

#define PIEZO A0 

#define ldrPin A2

#define DHT11_PIN 8

boolean profPresent = false;

const int wall = 50;
const int door = 150;
const int chipSelect = 4;

int counter = 0;
int lightCounter = 1;
int tempCounter = 1;
int humCounter = 1;

float averageLight;
float lightTotal = 0.0;
float averageTemp;
float tempTotal = 0.0;
float averageHum;
float humTotal = 0.0;

int hydrationCounter = 0;
int sensorReading;
const int threshold = 100;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 500;
unsigned long debounceDelayKnock = 500;

unsigned long personTime = millis();

Timer t;                                              //instantiate the timer object
dht DHT;                                              //instantiate the sensor object
const unsigned long period1 = 10000;                  // 15 min seconds

int totalNumberOfPeople = 0;
int realPeople = 0;
int totalNumberOfDrinks = 0;
int realDrinks = 0;

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
      //Serial.println("YES");
      long pastTimeProf = millis();
      if (pastTimeProf > (lastDebounceTime + debounceDelay)){
        //Serial.println("NO");  
        counter ++ ;
      }
      lastDebounceTime = pastTimeProf;
    }
    break;
  }
}

int getPeople(){
  realPeople = counter; // dividing by 2 is not necessary anymore since this is done in the total number of ppl function;
  Serial.print("The number of people now is: ");
  Serial.println(realPeople);
  return realPeople;
}

int countHydration(){
  sensorReading = analogRead(PIEZO);
  //Serial.println(sensorReading);
  
  if (sensorReading >= threshold) {
    long pastTime = millis();
//    Serial.println("DRINK");
  
    if (pastTime > (lastDebounceTime + debounceDelayKnock)){
      hydrationCounter ++;
      Serial.println("NODRINK");
    }
    lastDebounceTime = pastTime;
  }
  return hydrationCounter;
}

int getDrinks(){
  realDrinks = (hydrationCounter);
  //hydrationCounter = 0;
  Serial.print("Number of drinks is: ");
  Serial.println(realDrinks);
  return realDrinks;
}

float getTemp(){
  int chk = DHT.read11(DHT11_PIN);
  float temp = DHT.temperature;
  
  Serial.print("The temperature now is: ");
  Serial.println(temp);
  return temp;
}
float getHum(){
  float hum = DHT.humidity;
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("The humidity now is: ");
  Serial.println(hum);
  return hum;
}

float getLight(){
  float total = 0;
  for (int i=0; i<101; i++){
    int currentRead = analogRead(ldrPin); 
    total = total + currentRead;
  }
  float averageRead = (total/100);
  Serial.print("The average light of now is: ");
  Serial.println(averageRead);
  return averageRead;
}

char getValues(){
  int numberOfPeople = getPeople();
  totalNumberOfPeople += (numberOfPeople/2);

  Serial.print("The total people you've seen today is: ");
  Serial.println(totalNumberOfPeople);

  int numberOfDrinks = getDrinks();
  totalNumberOfDrinks += numberOfDrinks;

  Serial.print("The total drinks you've had today is: ");
  Serial.println(totalNumberOfDrinks);

  float light = getLight();
  lightTotal += light;
  averageLight = lightTotal / lightCounter;
  lightCounter += 1;
  Serial.print("The light you've had today is: ");
  Serial.println(averageLight);

  float temp = getTemp();
  tempTotal += temp;
  averageTemp = tempTotal / tempCounter;
  tempCounter += 1;
  Serial.print("The temperature you've had today is: ");
  Serial.println(averageTemp);
  
  float hum = getHum();
  humTotal += hum;
  averageHum = humTotal / humCounter;
  humCounter += 1;
  Serial.print("The humididty you've had today is: ");
  Serial.println(averageHum);

  Serial.println("-------------------------------------------");
  
  writeValues(realDrinks, light, temp, hum, numberOfPeople, totalNumberOfDrinks, averageLight,averageTemp,averageHum,totalNumberOfPeople );

  numberOfPeople = 0;
  realPeople = 0;
  counter = 0;

  numberOfDrinks = 0;
  realDrinks = 0;
  hydrationCounter = 0;
  
}

char writeValues(int drinksNow, float lightNow, float temperatureNow,float humidityNow,  int peopleNow,  int drinksTotal,float temperatureTotal, float lightTotal, float humidityTotal,   int peopleTotal){
  String dataString = "";
  dataString += drinksNow;
  dataString += ",";
  dataString += "S";
  dataString += ",";
  dataString += "F";
  dataString += ",";
  dataString += lightNow;
  dataString += ",";
  dataString += temperatureNow;
  dataString += ",";
  dataString += humidityNow;
  dataString += ",";
  dataString += peopleNow;
  dataString += ",";
  dataString += "W";
  dataString += ",";
  dataString += drinksTotal;
  dataString += ",";
  dataString += "ST";
  dataString += ",";
  dataString += "FT";
  dataString += ",";
  dataString += lightTotal;
  dataString += ",";
  dataString += temperatureTotal;
  dataString += ",";
  dataString += humidityTotal;
  dataString += ",";
  dataString += peopleTotal;
  dataString += ",";
  dataString += "WT";

  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  
}

void setup() {
  // put your setup code here, to run once: 
  Serial.begin (9600);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(PIEZO, INPUT);

  pinMode(ldrPin, INPUT);

  t.every(period1, getValues);
//  t.every(period1, getPeople);
//  t.every(period1, getDrinks);
//  t.every(period1, getTemp);
//  t.every(period1, getHum);
//  t.every(period1, getLight);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()-personTime > 50)     //Has one second passed?
  {
    personCounter();
    personTime = millis();
  }
  countHydration();
  t.update();
}
