#define enA 3
#define in1 4
#define in2 2

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
    analogWrite(enA, 255); 
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(1000);
    analogWrite(enA, 255); 
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(1000);
    analogWrite(enA, 255); 
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(1000);
    analogWrite(enA, 255); 
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    delay(1000);




}