
#define TRIG 2
#define ECHO 3

unsigned long time = millis();

int toggle = 1;

/**********************************************
 * setup() function
 **********************************************/
void setup()
{
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

/**********************************************
 * loop() function
 **********************************************/
void loop()
{
  if(millis()-time > 50)     //Has one second passed?
  {
    toggle = !toggle;          //If so not toggle 
    long duration, distance;
    digitalWrite(TRIG, LOW);  
    delayMicroseconds(2); 
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10); 
    digitalWrite(TRIG, LOW);
    duration = pulseIn(ECHO, HIGH);
    distance = (duration / 2) / 29.1;
    Serial.println(distance);
    time = millis();           //and reset time.
  }
 
  
}
