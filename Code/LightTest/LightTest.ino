#include <TinkerKit.h>
#include <SPI.h>
#include <SD.h>

TKLightSensor ldr(I0);

File myFile;

void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  
  Serial.println("initialization done.");

  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile){
    Serial.println("Ready for data!");
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

float getLight(){
  float total = 0;
  for (int i=0; i<1001; i++){
    int currentRead = ldr.read(); 
    total = total + currentRead;
  }
  float averageRead = (total/1000);
  return averageRead;
}

void loop() {
  // put your main code here, to run repeatedly:
  int average = getLight();
  Serial.println("The average is: ");
  Serial.println(average);
  
  if(myFile){
    if(average < 500){
      Serial.println("LOW LIGHT!");
      myFile.println("LOW LIGHT!");
    }
  }
  else {
    Serial.println("SD card not correctly initialized");
  }
  
  
  delay(1000);
}
