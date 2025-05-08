int dataPin  = A0;  
int oePin    = A1;//B
int latchPin = A2;  
int clockPin = A3;  
int rstPin   = A4;//B
int weRomPin = 2;   
int oeRomPin = 3;   
int RomAddr  = 0;
int RomData  = 0;
int RomDataPins[8]={4,5,6,7,8,9,10,11}; // ROM D7-D0



long int BaseConverter(int Base1, int Base2, long int nr1){// max base = 10
  long int nr2=0, p=1;
  if(Base1<Base2)
    while(nr1){
      nr2=nr2 + p*(nr1 % 10);
      nr1/=10;
      p*=Base1;}
  return nr2;}

void RomDataDir(int d=0){
  if(d)
    for (int i=0;i<8;i++)
      pinMode(RomDataPins[i], OUTPUT);
  else
    for (int i=0;i<8;i++)
      pinMode(RomDataPins[i], INPUT);  
      
      
      }

long int ReadRomData(){
  long int nr=0;
  for (int i=0;i<8;i++)
    nr= 10*nr + digitalRead(RomDataPins[i]);
  return nr;}

void WriteRomData(int nr){
  int p=128;
  for (int i=0;i<8;i++){
      if(nr>=p){
        digitalWrite(RomDataPins[i], HIGH);
        nr-=p;
      }
      else
        digitalWrite(RomDataPins[i], LOW);
    //digitalWrite(RomDataPins[i], nr>=p ? HIGH : LOW);
    p/=2;
    }}

void SetRomAddr(int nr){
  digitalWrite(oePin, HIGH);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, nr); //Shift_Q0 == ROM_A0
  digitalWrite(latchPin, HIGH);
  digitalWrite(oePin, LOW);
  delay(100);}
void setup() {
  pinMode(latchPin,  OUTPUT);
  pinMode(clockPin,  OUTPUT);
  pinMode(dataPin,   OUTPUT);
  pinMode(oePin,     OUTPUT);
  pinMode(rstPin,    OUTPUT);
  pinMode(weRomPin,  OUTPUT);
  pinMode(oeRomPin,  OUTPUT);

  digitalWrite(weRomPin, HIGH);
  digitalWrite(oeRomPin, HIGH);
  digitalWrite(dataPin,  LOW);
  digitalWrite(latchPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(oePin,    HIGH);
  digitalWrite(rstPin,   HIGH);
  Serial.begin(9600);}




void loop() {

  Serial.println("Writing...");
  RomDataDir(1);
  digitalWrite(oeRomPin, HIGH);
while(RomAddr<64){
  SetRomAddr(RomAddr);
  WriteRomData(RomAddr);
  digitalWrite(weRomPin, LOW);
  delay(10); 
  digitalWrite(weRomPin, HIGH);
  Serial.print("W Addr:");
  Serial.print(RomAddr);
  Serial.print(" data:");
  Serial.print(RomAddr);
  Serial.println(";");
  RomAddr++;
}

  SetRomAddr(14);
  WriteRomData(26);
  digitalWrite(weRomPin, LOW);
  delay(10); 
  digitalWrite(weRomPin, HIGH);
  Serial.println("W Addr:14 data:26;");


Serial.println("Reading...");
RomDataDir(0);
digitalWrite(oeRomPin, LOW);
RomAddr =0;
while(RomAddr<64){
  SetRomAddr(RomAddr);
  Serial.print("R Addr:");
  Serial.print(RomAddr);
  Serial.print(" data:");
  Serial.print(ReadRomData());
  Serial.println(";");
  RomAddr++;
}
RomAddr=0;
delay(15000);







}







