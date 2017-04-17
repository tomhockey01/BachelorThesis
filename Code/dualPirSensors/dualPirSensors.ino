#define PIR_OUT1 A1
#define PIR_OUT2 A2



int pirState1;
int pirState2;
int counter = 1;

boolean movement = false;
boolean oldMovement;

void setup() {
 Serial.begin(9600);
 
 pinMode(PIR_OUT1, INPUT);
 pinMode(PIR_OUT2, INPUT);
}

int readPir(int input) {
  int pirState = analogRead(input);
  return pirState;
}


void loop() {
  pirState1 = readPir(PIR_OUT1);
  pirState2 = readPir(PIR_OUT2);

  if((pirState1 > 600) || (pirState1 < 400)) {
    movement = true;
    if (movement != oldMovement){
      if ((pirState2 > 600) || (pirState2 < 400)) {
        counter ++; 
      }
    oldMovement = movement;
    }
  }
  else{
    movement = false;
    oldMovement = movement;
  }
  
  if((pirState2 > 600) || (pirState2 < 400)) {
    movement = true;
    if (movement != oldMovement){
      if ((pirState1 > 600) || (pirState1 < 400)) {
        counter --;
      }
    oldMovement = movement;
    }
  }
  else{
    movement = false;
    oldMovement = movement;
  }
Serial.println(pirState1);
Serial.println("----------");
Serial.println(pirState2);
Serial.println("----------");
Serial.println(counter);
Serial.println("----------");
Serial.println("----------");

  
delay(500);
}



