//programa EMISOR SENCILLO 2 APC220 de canal de Youtube
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.write(1);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  Serial.write(0);
  delay(1000);
}
