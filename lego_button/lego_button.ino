constexpr int upPin = 2;  // the number of the pushbutton pin
constexpr int downPin = 3;  // the number of the pushbutton pin

void setup() {
  
  // initialize the pushbutton pin as an input:
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

}

void loop() {
  
  if (digitalRead(upPin) == HIGH) {
    Serial.println("VOLUME_UP");
    delay(200);
  }
  
  if (digitalRead(downPin) == HIGH) {
    Serial.println("VOLUME_DOWN");
    delay(200);
  } 
}
