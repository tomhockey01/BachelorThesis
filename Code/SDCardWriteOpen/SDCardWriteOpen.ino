#include <SPI.h>
#include <SD.h>

File myFile;

boolean a = false;

const int buttonPin = 2; 

int buttonState = 0;
int lastButtonState = 0;

void setup() {
  // Open serial communications and wait for port to open:
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

  pinMode(buttonPin, INPUT);
}


void loop() {
  // nothing happens after setup
  String dataString = "";
  buttonState = digitalRead(buttonPin);
  if(buttonState != lastButtonState){
    if (buttonState == HIGH){
      dataString.concat("Click, ");
      a = true;
      Serial.println(dataString);
    }
  lastButtonState = buttonState;
  
  }
  
  while(a){
    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
      myFile.println(dataString);
      // close the file:
      myFile.close();
      Serial.println("done.");
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
    }
    a = false;
  }
}
