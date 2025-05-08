int DataPin[8]={6,7,8,9,10,11,12,13};
int E_WE =    A0;
int E_OE =    A1;
int S_DATA =  A2;
int S_OE =    A3;
int S_LATCH = A4;
int S_CLK =   A5;

int ADDR = 0;

void setDataPins(int Mode){  //1=input 0=output
  if (Mode==1)
    for(int i=0;i<7;i++)pinMode(DataPin[i],INPUT);
  else
    for(int i=0;i<7;i++)pinMode(DataPin[i],OUTPUT);
}
void E_Write(int Data,int Addr){}
void E_Read(int Addr){}
void SetAddr(int Addr){
shiftOut(S_DATA,S_CLK,Addr)

}




void setup() {
  pinMode(E_WE,  OUTPUT);
  pinMode(E_OE,  OUTPUT);
  pinMode(S_DATA,   OUTPUT);
  pinMode(S_OE,     OUTPUT);
  pinMode(S_LATCH,    OUTPUT);
  pinMode(S_CLK,  OUTPUT);

  digitalWrite(E_WE, HIGH);
  digitalWrite(E_OE, HIGH);
  digitalWrite(S_DATA,  LOW);
  digitalWrite(S_OE, LOW);
  digitalWrite(S_LATCH, LOW);
  digitalWrite(S_CLK,    HIGH);
  
  Serial.begin(9600);}







}

void loop() {
  

}
