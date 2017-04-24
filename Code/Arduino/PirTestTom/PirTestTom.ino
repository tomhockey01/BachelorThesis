#define PIR_OUT1 A1
#define PIR_OUT2 A2



int pirState1;
int pirState2;
int counter = 1;

boolean movement1 = false;
boolean oldMovement1;
boolean movement2 = false;
boolean oldMovement2;

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

  if ((pirState1 > 600) || (pirState1 < 400)) {
    movement1 = true;
  }
  else{
    movement1 = false;
    oldMovement1 = movement1;
  }

  if ((pirState2 > 600) || (pirState2 < 400)) {
    movement2 = true;  
  }
  else{
    movement2 = false;
    oldMovement2 = movement2;
  }
  
  if (movement1 != oldMovement1) {
      if (movement2) {
        counter ++;
      }
      oldMovement1 = movement1;
    }


  if (movement2 != oldMovement2) {
      if (movement1) {
        counter --;
      }
      oldMovement2 = movement2;
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



