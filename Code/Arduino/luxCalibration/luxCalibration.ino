#define light A1

//Lux
double Light (int RawADC0){
  double Vout=RawADC0*0.0048828125;
  int lux=500/(10*((5-Vout)/Vout));//use this equation if the LDR is in the upper part of the divider
  //int lux=(2500/Vout-500)/10;
  return lux;
}

void setup() {
  Serial.begin(115200);
}
void loop() {
  Serial.println(int(Light(analogRead(light))));
 
  Serial.println(analogRead(light));

  Serial.println("------------");
  
  delay(1000);
}
