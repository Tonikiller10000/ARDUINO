void setup() {
  Serial.begin(9600);
  Serial.println("Clock SYS begin:");
}

void loop() { 
  while (Serial.available() == 0) {}     
  String Pulses = Serial.readString();  
  //teststr.trim();                        // remove any \r \n whitespace at the end of the String
  Serial.println(Pulses);
  int pulses=0;
for  (int i=0;i<Pulses.length();i++)
{
if(Pulses[i] ==49 )
  pulses=pulses*10 +i-48;
else 
  break;
}  
Serial.println(pulses);
}