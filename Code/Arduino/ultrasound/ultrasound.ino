#define trigPin1 2
#define echoPin1 3

#define trigPin2 12
#define echoPin2 13

const int doorpost = 100;

long duration, distance, sound1, sound2;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

}

  int dualSound(int trigPin, int echoPin){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;
    return distance;
  }

void loop() {
  sound1 = dualSound(trigPin1, echoPin1);

  //sound1 = distance;
  sound2 = dualSound(trigPin2, echoPin2);

  //sound2 = distance;

  Serial.println(sound1);
  Serial.println(sound2);
  Serial.println("__________");

  delay(50);

}





//  if (distance1 < doorpost) {
//      Serial.print("switch");
//      delay(1500);
//    }




