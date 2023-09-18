void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  if(analogRead(A0) || analogRead(A1) || analogRead(A2) || analogRead(A3) || analogRead(A4) || analogRead(A5))
      Serial.println("da");
  else 
      Serial.println("nu");
}
