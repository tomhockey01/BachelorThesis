#define PIR_OUT 3 

int pirState = 0;
int lastPirState = 0;

void setup(void)
{
  int i = 40;
  Serial.begin(9600);
  delay(100);
  Serial.println("SimplyTronics PIR Sensor(ST-00031/ST-000081)");
  Serial.println("===========================================");
  Serial.println("Please wait 40 seconds the PIR Sensor to warm up...");
  while(i-- > 0)
  {
    Serial.print(i);
    Serial.println("  seconds left");
    delay(1000);
  } 
 Serial.println("Start detect the state of PIR Sensor."); 
  pinMode(PIR_OUT, INPUT);
}

int pir_output = 0;
void loop(void){
   pirState = digitalRead(PIR_OUT);

   if(pirState != lastPirState){
    if(pirState == HIGH){
      Serial.println("switch");
    }
    lastPirState = pirState;
   }
  
   delay(200);
}
