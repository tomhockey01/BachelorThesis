#define trigPin1 2
#define echoPin1 3


const int doorpost = 25;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
 
}

void loop() {
  long duration1, distance1, duration2, distance2;
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 / 2) / 29.1;

  


 Serial.println(distance1);


  
  if (distance1 < doorpost) {
      Serial.print("switch");
      delay(1500);
    }

    
  delay(500);
}
