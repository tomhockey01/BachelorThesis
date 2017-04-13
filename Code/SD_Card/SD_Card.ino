const int buttonPin = 2; 

int buttonState = 0;
int lastButtonState = 0;


#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
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
    
  pinMode(buttonPin, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  buttonState = digitalRead(buttonPin);

  if (myFile){
    // if the file opened okay, write to it:
    if(buttonState != lastButtonState){
      if (buttonState == HIGH){
        Serial.println("CLICK");
        myFile.println("CLICK");
      }
    lastButtonState = buttonState;
    }
  }
  else {
    Serial.println("SD card not correctly initialized");
  }

} 

