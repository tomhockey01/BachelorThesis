#define PIR 3

int counter = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 75;


void setup() {
  Serial.begin(9600);
  pinMode(PIR, INPUT);  

}

void loop() {
  int pir_output = digitalRead(PIR);
  //Serial.println(pir_output);
  if (pir_output = 1){
    long pastTime = millis();
    //Serial.print("hoi" );

    if (pastTime > (lastDebounceTime + debounceDelay)){
      counter ++;
      Serial.println(counter);
      Serial.println("hooiiiiii" );
    }
    lastDebounceTime = pastTime;
  }
delay(50);
}


