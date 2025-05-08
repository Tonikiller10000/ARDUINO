int weRomPin = A0;   
int oeRomPin = A1;  
int dataPin  = A2;  
int oePin    = A3;
int latchPin = A4;  
int clockPin = A5;   
int RomAddr  = 0;
int RomData  = 0;
int RomDataPins[8]={4,5,6,7,8,9,10,11}; // ROM D7-D0

int CODE_65[64] = {

//set register B pins to output
0xA9, 0xFF,       // lda #$FF
0x8D, 0x02, 0x60, // sta $6002

//OUTPUT to B $55
0xA9, 0x55,       // lda #$55
0x8D, 0x00, 0x60, // sta $6000

//OUTPUT to B $AA
0xA9, 0xAA,       // lda #$AA
0x8D, 0x00, 0x60, // sta $6000

//Reload
0x4C, 0x05, 0x80, // jmp $8005   


0xEA, 0xEA,       // 2x NO OP 
0xEA, 0xEA,       // 2x NO OP 
0xEA, 0xEA,       // 2x NO OP 
0xEA, 0xEA,       // 2x NO OP 
0xEA, 0xEA,       // 2x NO OP 
0xEA, 0xEA,       // 2x NO OP 


// 0x7FFC = 0x00;
// 0x7FFD = 0x80;
};

//Start location: FFFC(low byte)- FFFD(high byte) 









/*vol=analogRead(pa3);
while(Serial.available() == 0){}
myname=Serial.readString();*/




int BaseConverter(int Base1, int Base2, int nr1){
  int nr2=0, p=1;
  if(Base1<Base2)// from Base1 var value to Base10
    while(nr1){
      nr2=nr2 + p *(nr1 % 10);
      nr1/=10;
      p*=Base1;}
  return nr2;}
void SetRomAddr(int nr){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, nr/256); //Shift_Q0 == ROM_A0
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, nr%256); //Shift_Q0 == ROM_A0
  digitalWrite(latchPin, HIGH);}

int ReadRomData(int addr, int mode=1){
  int nr=0;
  digitalWrite(oeRomPin, LOW);
  SetRomAddr(addr);
  for (int i=0;i<8;i++) pinMode(RomDataPins[i], INPUT);   
  delay(50);
  Serial.print("Read(");
  if(mode == 0) Serial.print(addr);
  if(mode == 1) Serial.print(addr,HEX);
  Serial.print("): ");
  for (int i=0;i<8;i++){
    if(digitalRead(RomDataPins[i])){
      nr= 2*nr + 1;
      Serial.print(1);
    }
    else{
      nr= 2*nr + 0;
      Serial.print(0);
    }
  }
  Serial.print("-");
  if(mode == 0) Serial.println(nr);
  if(mode == 1) Serial.println(nr,HEX);
  digitalWrite(oeRomPin, HIGH);
  delay(50);//delay
  return nr;}


void WriteRomData(int nr, int addr,  int mode=1){
  int p = 128, nrc = nr;
  SetRomAddr(addr);
  for (int i=0;i<8;i++) pinMode(RomDataPins[i], OUTPUT);  
  Serial.print("Write(");
  if(mode == 0) Serial.print(addr);
  if(mode == 1) Serial.print(addr,HEX);
  Serial.print("): ");
  for (int i=0;i<8;i++){
      if(nr>=p){
        Serial.print(1);
        digitalWrite(RomDataPins[i], 1);
        nr-=p;
      }
      else{
        Serial.print(0);
        digitalWrite(RomDataPins[i], 0);}
    p/=2;
  }
  Serial.print("-");
  if(mode == 0) Serial.println(nrc);
  if(mode == 1) Serial.println(nrc,HEX);
  digitalWrite(weRomPin, LOW);
  delay(80);
  digitalWrite(weRomPin, HIGH);
  delay(20);//delay
  }







void setup() {
  pinMode(latchPin,  OUTPUT);
  pinMode(clockPin,  OUTPUT);
  pinMode(dataPin,   OUTPUT);
  pinMode(oePin,     OUTPUT);
  pinMode(weRomPin,  OUTPUT);
  pinMode(oeRomPin,  OUTPUT);

  digitalWrite(weRomPin, HIGH);
  digitalWrite(oeRomPin, HIGH);
  digitalWrite(latchPin, LOW);
  digitalWrite(oePin,    LOW);
  Serial.begin(9600);

  Serial.println("\nBegin...");



  // Program CODE
  for (int i=0;i<30;i++)
    WriteRomData(CODE_65[i],i);

  //Beging program from 0x8000
  WriteRomData(0x00,0x7FFC);
  WriteRomData(0x80,0x7FFD);

  //Read some addresses
  for(int i=0;i<32;i++)
    ReadRomData(i);
  for(int i=0x7FFF-8;i<0x7FFF;i++)
    ReadRomData(i); 


  pinMode(2,   OUTPUT);
}

void loop() 
{
  digitalWrite(2, LOW);
  delay(400);
  digitalWrite(2, HIGH);
  delay(600);

}

























