#include <dht.h>;
#include <Timer.h>;

dht DHT;

#define DHT11_PIN 8

Timer t;                                              //instantiate the timer object
const unsigned long period1 = 1000;                  // 10 seconds

void setup(){
  Serial.begin(9600);

  t.every(period1, getTemp);
  t.every(period1, getHum);
}

void loop()
{
  t.update();
}

float getTemp(){
  int chk = DHT.read11(DHT11_PIN);
  float temp = DHT.temperature;
  
  Serial.print("The temp is: ");
  Serial.println(temp);
  return temp;
}
float getHum(){
  float hum = DHT.humidity;
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("The humidity is: ");
  Serial.println(hum);
  return hum;
}
