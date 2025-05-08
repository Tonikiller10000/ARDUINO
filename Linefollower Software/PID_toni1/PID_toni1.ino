#define Ben 3
#define Bin1 2
#define Bin2 4
#define Aen 5
#define Ain1 6
#define Ain2 7


int ps=255, pd=255, p=0;
int sensorNr=8, lineCenter = (sensorNr-1)*1000/2, lineMissingInterval = 1500;
int lineDeviation = 0, linePosition =0,  lineOldPosition = 0;
int sensorsPins[8] = {A5,A4,A3,A2,A1,A0,A7,A6};
int sensorsValues[8]={0,0,0,0,0,0,0,0};

void MotA (int dir, int speed){
    int in1, in2;
    if(!speed){ in1=0;in2=0;}
    if(dir){ in1=1;in2=0;}
    if(!dir){ in1=0;in2=1;}
    analogWrite(Aen, speed); 
    digitalWrite(Ain1, in1);
    digitalWrite(Ain2, in2);}
void MotB (int dir, int speed){
    int in1, in2;
    if(!speed){ in1=0;in2=0;}
    if(dir){ in1=1;in2=0;}
    if(!dir){ in1=0;in2=1;}
    analogWrite(Ben, speed); 
    digitalWrite(Bin1, in1);
    digitalWrite(Bin2, in2);}
void sensorsRead(){
  int l=400, L=800;
  for(int i=0;i<sensorNr;i++){
      sensorsValues[i]=analogRead(sensorsPins[i]);// the rest between l and L ???
      if(sensorsValues[i]<l) sensorsValues[i]=0;
      if(sensorsValues[i]>L) sensorsValues[i]=1000;    
  }}
void sensorsDisplay(){
  for(int i=0;i<sensorNr;i++){
    Serial.print(sensorsValues[i]);
    Serial.print(" ");}}
int sensorsActiveNr=0
  for(int i = 0;i<sensorsNr;i++){
    if(sensorValues[i]!=0)
      sensorsActiveNr++;}
int sensorsFirstActive=0
  for(int i = 0;i<sensorsNr;i++)
    if(sensorValues[i]!=0){
      sensorsFirstActive = i;
      break;
    }
int sensorsPositionSum(){
  int SPS=0;
  for(int i=1;i<=sensorNr;i++)
    SPS+=i*sensorsValues[i];
  return SPS;}
int sensorsSum(){
  int SS=0;
  for(int i=1;i<=sensorNr;i++)
    SS+=sensorsValues[i];
  return SS;}




int sensorsPS=0, sensorsSS=0;
if(sensorsActiveNr==3){
  int sensorsActiveTreshhold=300;
if(sensorValues[sensorsFirstActive]<sensorsTreshhold && sensorValues[sensorsFirstActive]+2<sensorsTreshhold){
  sensorsFirstActive=sensorsFirstActive+1;
  sensorsActiveNr =1;
}
else 
{
  if(sensorValues[sensorsFirstActive] >sensorValues[sensorsFirstActive+1])
    sensorsPS=sensorsFirstActive;sensorsSS=sensorsFirstActive+1;
  else
    sensorsPS=sensorsFirstActive+1;sensorsSS=sensorsFirstActive;
  sensorsActiveNr =2;
}
}

int sensorsInterpolation=0;
if(sensorsActiveNr==2 && sensorsPS==0 && sensorsSS==0){
  if(sensorsValues[sensorsActiveNr] > sensorsValues[sensorsActiveNr+1]){
    sensorsPS=sensorsActiveNr;sensorsSS=sensorsActiveNr+1;sensorInterpolation=sensorsSS/1000;
   }
  else if(sensorsValues[sensorsActiveNr] < sensorsValues[sensorsActiveNr+1]){
    sensorsPS=sensorsActiveNr+1;sensorsSS=sensorsActiveNr;sensorInterpolation=sensorsSS/1000;
  }
  else{sensorsInterpolation=0.5;}
}
sensorInterpolation=sensorsSS/1000;
LinePosition = 0;//princilap sensor witrh polarisation to second and in interval of 0 to 8000;
// -4000 is 0 middle and +-2000 is for rigth itrerupted line
//else curbe protocol for motors







// LineDeviation = linePosition - lineOldPosition;
// lineOldPosition = linePosition;

// if (-linePosition==lineCenter+1) linePosition=lineOldPosition; 	//pentru linii intrerupte;
// if (-linePosition!=lineCenter+1) bd=bs=0;      			//se anuleza procedura.

// if (linePosition>1500  && -linePosition==lineCenter+1) bs=1; 
// if (linePosition<-1500 && -linePosition==LineCenter+1) bd=1;
// pf=pw; ps=pw;
// while (bs==1){
// 	citeste();
// 	MotorStanga("spate",ps)
// 	MotorDreapta("fata",pf)}
// while (bd==1){
// 	citeste();
// 	MotorStanga("fata",pf)
// 	MotorDreapta("spate",ps)}


void setup() {
  pinMode(Aen, OUTPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Ben, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
sensorsRead();
int pdef=800;
int dd=1, ds=1;
p=int(sensorsPositionSum()/sensorsSum()); 
if(p>0 && p<4)
  pd=10*p+pdef;
if(p>4 && p<8)
  ps=10*p+pdef;
if(p==6 || p==7)
  {dd=0;pd+=10;pd = ps;}
if(p==1 || p==2)
  {ds=0;ps+=10;ps = pd;}
if(p==4)
  {MotA( ds, ps+30); MotB( dd, pd+30);}
else
  {MotA( ds, ps); MotB( dd, pd);}


}



