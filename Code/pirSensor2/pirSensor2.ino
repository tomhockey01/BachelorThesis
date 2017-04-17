#define PIR_OUT1 A1
#define PIR_OUT2 A2



int pirState1;
int pirState2;
boolean movement = false;
boolean oldMovement;

void setup() {
 Serial.begin(9600);
 
 pinMode(PIR_OUT1, INPUT);
 pinMode(PIR_OUT2, INPUT);
}



void loop() {
  pirState1 = analogRead(PIR_OUT1);
  //pirState2 = analogRead(PIR_OUT2);

  Serial.println(pirState1);

//  if((pirState1 < 600) && (pirState1 > 400)) {
//    Serial.println("no movement");
//    movement = false;
//    oldMovement = movement;
//  }
//  else{
//    movement = true;
//    if(movement != oldMovement){
//      Serial.println("movement");
//    }
//    oldMovement = movement;
//  }
  
delay(1000);
}



