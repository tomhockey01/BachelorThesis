#define PIR_OUT1 A1

#define trigPin 2
#define echoPin 3

const int wall = 200;

int counter = 0;

int pirState1;
boolean buttonState;
boolean lastButtonState = false;

boolean movement = false;

boolean profPresent = false;
boolean oldProfPresent = false;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 500;

int readPir(int input) {
  int pirState = analogRead(input);
  return pirState;
}

int readDistance(){
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.println(distance);
  if (distance < wall){
      return true;
  }
  else if(distance >= wall){
    return false;
  }
}

void setup() {
  // put your setup code here, to run once: 
  Serial.begin (9600);
  pinMode(PIR_OUT1, INPUT);
 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  profPresent = readDistance();

  while(profPresent){
    Serial.println("in while");
    
    pirState1 = readPir(PIR_OUT1);
    if((pirState1 > 600) || (pirState1 < 400)) {
      movement = true;
      if (movement != lastButtonState){
        lastDebounceTime = millis();
      }
      if ((millis() - lastDebounceTime) > debounceDelay){  
        if (movement != buttonState){
          buttonState = movement;
          if (buttonState){
            counter ++;
            //buttonState = false;
          }
        }
      }
      lastButtonState = movement;
    }
    else{
      movement = false;
      buttonState = movement;
      lastButtonState = movement;
    }
    break;
  }

  Serial.println(counter);
  
  delay(50);
}
