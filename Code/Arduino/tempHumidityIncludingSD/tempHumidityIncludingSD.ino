#include <dht.h>
#include <SD.h> //Load SD card library
#include <SPI.h>

dht DHT;

#define DHT11_PIN 8

const int chipSelect = 4;
File tempData;

void setup(){
  Serial.begin(9600);
  SD.begin(4);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  tempData = SD.open("tempData.txt", FILE_WRITE);
  if (tempData){
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);
    delay(1000);

    tempData.print(DHT.temperature);
    tempData.print(",");
    tempData.println(DHT.humidity);
    tempData.close();
  }
}

