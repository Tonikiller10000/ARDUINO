






 
/*vol=analogRead(pa3);
Serial.println(vol); 
digitalWrite(p13,HIGH);
while(Serial.available() == 0){}
myname=Serial.readString();
Serial.println(myname);*/




















int b1=13,b2=12,b3=11,b4=10,b5=9,b6=8,b7=7,b8=6;//bits
int data=5,oe=4,save=3,clk=2,v=0;//shift register + v
unsigned long int adress1=900000000;//adress
float ds = 0.0001, d1=1000, d2 = 10;//delays



int convBtoD(unsigned long int bnum){int dnum = 0;
  for(int i=0;i<8;i++){
    if(bnum%10==1){dnum=dnum+(int)(pow(2,i)+0.5);}
    bnum = bnum/10;}
    return dnum;}
unsigned long int convDtoB(int dnum){unsigned long int bnum=9;
  for(int i=8;i>0;i--){
    if(dnum>=pow(2, i-1)){dnum=dnum-pow(2, i-1);bnum = bnum*10+1;}
    else bnum = bnum *10;}
    return bnum;}
void shiftreg( unsigned long int shiftcode1,unsigned long int shiftcode2){
  digitalWrite(oe,HIGH);digitalWrite(save,LOW);
    while(shiftcode2>9){
      if (shiftcode2%10 == 0)digitalWrite(data,LOW);
      else digitalWrite(data,HIGH);
      shiftcode2 = shiftcode2 / 10;delay(3*ds);
      digitalWrite(clk,HIGH);delay(2*ds); digitalWrite(clk,LOW);}
    while(shiftcode1>9){
      if (shiftcode1%10 == 0)digitalWrite(data,LOW);
      else digitalWrite(data,HIGH);
      shiftcode1 = shiftcode1 / 10;delay(3*ds);
      digitalWrite(clk,HIGH);delay(2*ds); digitalWrite(clk,LOW);}
      delay(2*ds);digitalWrite(save,HIGH);delay(2*ds);
      digitalWrite(save,LOW);digitalWrite(oe,LOW);
      delay(d1);}
void setpins(int type){
  if(type == 0){
    pinMode(b1, INPUT);pinMode(b2, INPUT);pinMode(b3, INPUT);pinMode(b4, INPUT);
    pinMode(b5, INPUT);pinMode(b6, INPUT);pinMode(b7, INPUT);pinMode(b8, INPUT);}
  else{
    pinMode(b1, OUTPUT);pinMode(b2, OUTPUT);pinMode(b3, OUTPUT);pinMode(b4, OUTPUT);
    pinMode(b5, OUTPUT);pinMode(b6, OUTPUT);pinMode(b7, OUTPUT);pinMode(b8, OUTPUT);}}   
unsigned long int readadress(int ads){unsigned long int rb=9;
  setpins(0);delay(d2);shiftreg(convDtoB(ads),900001000);
  rb = (rb*10 + digitalRead(b1))*10 + digitalRead(b2);
  rb = (rb*10 + digitalRead(b3))*10 + digitalRead(b4);
  rb = (rb*10 + digitalRead(b5))*10 + digitalRead(b6);
  rb = (rb*10 + digitalRead(b7))*10 + digitalRead(b8);
  return rb;}


void setup(){
  setpins(0);
  pinMode(data, OUTPUT);pinMode(oe, OUTPUT);
  pinMode(save, OUTPUT);pinMode(clk, OUTPUT);
  digitalWrite(data,LOW);digitalWrite(oe,HIGH);
  digitalWrite(save,LOW);digitalWrite(clk,LOW); 
  Serial.begin(9600); }
  
void loop(){
  Serial.print(v);
  Serial.print(" -data: ");
  Serial.println(readadress(v));
  v=v+1;
delay(d1);}

