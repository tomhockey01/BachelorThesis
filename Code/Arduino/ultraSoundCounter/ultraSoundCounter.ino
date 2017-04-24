#define TRIG 2
#define ECHO 3

const int door = 100;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 250;

int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(TRIG, LOW);  
  delayMicroseconds(2); 
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) / 29.1;
  //Serial.println(distance);
  if (distance < door){
    long pastTime = millis();

    if (pastTime > (lastDebounceTime + debounceDelay)){
      counter ++;
      Serial.println(counter);
    }
    lastDebounceTime = pastTime;
  }
  

  delay(50);
}
