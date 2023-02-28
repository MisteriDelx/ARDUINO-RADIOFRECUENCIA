//Receptor sencillo 2 para APC220
void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()){
    int LED_estado=Serial.read();
    Serial.println(LED_estado);
    
    if (LED_estado==1){
      digitalWrite(LED_BUILTIN,HIGH);
    }
    else {
      digitalWrite(LED_BUILTIN,LOW);
    }
  }
 }
