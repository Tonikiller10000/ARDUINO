double pulse, frequency, capacitance, inductance;

void setup(){
  Serial.begin(115200);
  pinMode(11, INPUT);  //11 is the comparator output
  pinMode(13, OUTPUT); //13 charge the circuit
  Serial.println("Hello!");
  delay(200);
}
void loop(){
  digitalWrite(13, HIGH);
  delay(5);//charge the inductor
  digitalWrite(13,LOW);
  delayMicroseconds(100); 
  pulse = pulseIn(11,HIGH,5000);//returns 0 if timeout
  if(pulse > 0.1){ //if a timeout did not occur and it took a reading:
    

  capacitance = 471.0 / pow(10,9); 
  frequency = 1.0 * pow(10,6)/(2*pulse);
  inductance = 1./(capacitance*frequency*frequency*4.*3.14159*3.14159);
  inductance *= 1 * pow(10,6);


  Serial.print("High for uS:");
  Serial.print( pulse );
  Serial.print("\tfrequency Hz:");
  Serial.print( frequency );
  Serial.print("\tinductance uH:");
  Serial.println( inductance );
  delay(10);

  }
}
