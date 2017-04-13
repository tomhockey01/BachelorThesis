const int buttonPin = 2; 

int buttonState = 0;
int lastButtonState = 0;

const int chipSelect = 4;

#include <SPI.h>
#include <SD.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

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
    
  pinMode(buttonPin, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  String dataString = "";
  
  buttonState = digitalRead(buttonPin);
  if(buttonState != lastButtonState){
    if (buttonState == HIGH){
      Serial.println("CLICK");
      dataString += "Click, ";
    }
  lastButtonState = buttonState;
  }

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
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

