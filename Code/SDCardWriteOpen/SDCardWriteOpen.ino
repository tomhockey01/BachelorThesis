#include <SPI.h>
#include <SD.h>

File myFile;

boolean a = true;

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
}


void loop() {
  // nothing happens after setup
  
  while(a){
    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
      myFile.println("DOE HET NOU");
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
