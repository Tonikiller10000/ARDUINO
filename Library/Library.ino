int ShiftLatch = 8, ShiftClk = 12, ShiftData = 11, ShiftDelay=200, ShiftOE=9;

void ShiftAH(int ShiftData, int ShiftClk, int ShiftLatch, int Data){
    digitalWrite(ShiftLatch, LOW);
    shiftOut(ShiftData, ShiftClk, MSBFIRST, Data);//MSBFIRST(A->H = 0->255)
    digitalWrite(ShiftLatch, HIGH);}
void ShiftHA(int ShiftData, int ShiftClk, int ShiftLatch, int Data){
    digitalWrite(ShiftLatch, LOW);
    shiftOut(ShiftData, ShiftClk, LSBFIRST, Data);//MSBFIRST(A->H = 0->255)
    digitalWrite(ShiftLatch, HIGH);}


    
void EEPROM1_READ(int ADDR){//11 ADRESE
    digitalWrite(ShiftOE, HIGH); 
    ShiftAH(ShiftData, ShiftClk, ShiftLatch, ADDR/256 );
    ShiftAH(ShiftData, ShiftClk, ShiftLatch, ADDR%256 );
    digitalWrite(ShiftOE, LOW);
    delay(ShiftDelay);
  
  
  }


void setup() {
  pinMode(ShiftLatch, OUTPUT);
  pinMode(ShiftClk, OUTPUT);
  pinMode(ShiftData, OUTPUT);
  pinMode(ShiftOE, OUTPUT);}

  
void loop() {
  
for (int nr = 0; nr < 19246; nr+=1) {
EEPROM1_READ(9500);

}


}



 
/*vol=analogRead(pa3);
Serial.println(vol); 
digitalWrite(p13,HIGH);
while(Serial.available() == 0){}
myname=Serial.readString();
Serial.println(myname);*/
