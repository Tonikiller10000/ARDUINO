//program cu caramida
const int pingPin = 4;
long duration, inches, cm;

const int MdrSpa = 13;
const int MdrFata =12;
const int pdr=5;

const int MsgSpa = 7;
const int MsgFata =8;
const int psg=6;

long sensors[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
long masuraSenz = 0;
int sw=11;
int sumaSenz = 0;
int p=0,s=0, c=0, pozitie = 0;
int proportional = 0;
long integral = 0;
int derivative = 0;
int propOld = 0;
 int control = 0;
double pf=0,ps=0;
int  pw =70;
float Kp = .3;
float Ki = .000001;
float Kd = 10.105;
int prop,bd=0,bs=0,nrSenz=6;
int limit =(nrSenz-1)*1000/2;

void setup()
{
 pinMode (MdrFata, OUTPUT);
 pinMode (MsgFata,OUTPUT);
 pinMode (MdrSpa, OUTPUT);
 pinMode (MsgSpa, OUTPUT);
 pinMode(pdr,OUTPUT);
 pinMode(psg,OUTPUT);
 Serial.begin(9600);
 pinMode (sw,INPUT);
 digitalWrite(sw, HIGH);
 }


void loop()
{
 citeste();
  vezi();
 decide();
 set_motors();
 
}

void citeste()
{
 for (int i = 0; i < nrSenz; i++)
 {
   sensors[i] = analogRead(i);
   
  if (sensors[i] < 200)
   {
     sensors[i] = 0;
   }
 }
masuraSenz = 0;
 
for (int i = 0; i < nrSenz; i ++)
 {
   masuraSenz += sensors[i] * i * 1000;
 }

sumaSenz = 0;
 
 for (int i = 0; i < nrSenz; i++)
 {
   sumaSenz += int(sensors[i]);
 }

pozitie = int(masuraSenz / sumaSenz);

proportional = pozitie - limit;
 prop=proportional;
if (-proportional==limit+1) proportional=propOld;

if (-prop != limit+1) {bd=0;bs=0;ps=0;pf=0;}
//if (analogRead (1)<250) bs=0;
//if (analogRead (nrSenz-2)<250)bd=0;
 integral = integral + proportional;

 derivative = proportional - propOld;

 
  propOld = proportional;

 control = int(proportional * Kp + integral * Ki + derivative * Kd);// ec de miscare
}

void decide()
{
  
  //  Serial.print("PROP");Serial.print(' ');Serial.println(prop);// delay (100);

//cauta linie  
if (proportional>1500 && -prop==limit+1 ) {bs=1;pf=pw;ps=pw/5;baga_linie();} //-prop==limit+1 conditie daca e pe alb
if (proportional<-1500 && -prop==limit+1 ) {bd=1;pf=pw; ps=pw/5;baga_linie();}//


}



void baga_linie()
{
  
while (bs==1)
 {
   citeste();
   ps=ps+.05;
  if (ps>pw) ps=pw;
  
  digitalWrite(MsgSpa,1);
  digitalWrite(MdrSpa,0);
  digitalWrite(MsgFata,0);
  digitalWrite(MdrFata,1);//////
  analogWrite(psg,ps);
  analogWrite(pdr,pf);
  
  
//   control = pw;   
 }

 while (bd==1)
 {
   citeste();
    ps=ps+.05;
  if (ps>pw) ps=pw;
  digitalWrite(MsgSpa,0);
  digitalWrite(MdrSpa,1);
  digitalWrite(MsgFata,1);
  digitalWrite(MdrFata,0);
  analogWrite(pdr,ps);
  analogWrite(psg,pf);
  
 // control = -pw;
 }

 
}
void set_motors()
{
 digitalWrite(MdrSpa,0);
 digitalWrite(MsgSpa,0);
//Serial.print("bs");Serial.print(' ');Serial.println(bs); delay (100);
//Serial.print("bd");Serial.print(' ');Serial.println(bd); delay (100);
  if (control > pw)
 {
   control = pw;
 }
 

 if (control < -pw)
 {
   control = -pw;
 }
 
 if (control < 0)
 {
   digitalWrite(MdrSpa,0);
 digitalWrite(MsgSpa,0);
 digitalWrite(MdrFata,1);
 digitalWrite(MsgFata,1);
   analogWrite(pdr, pw + control);
   analogWrite(psg, pw);
 }
else
 {
   digitalWrite(MdrSpa,0);
 digitalWrite(MsgSpa,0);
 digitalWrite(MdrFata,1);
 digitalWrite(MsgFata,1);
   analogWrite(pdr, pw);
   analogWrite(psg, pw - control);
 }
}

void opreste()
{


  digitalWrite(MdrSpa,0);
  digitalWrite(MsgFata,0);
  digitalWrite(MsgSpa,0);
  digitalWrite(MdrFata,0);
 while (1);
}

void vezi()
{
   if (digitalRead(sw)==0) p++ ;
   if (p==1 && s==0) 
   {
      digitalWrite(MdrSpa,0);
      digitalWrite(MsgSpa,0);
      digitalWrite(MsgFata,1);
      digitalWrite(MdrFata,1);
      analogWrite(psg,140);
      analogWrite(pdr,170);
      delay(600);s=1;
       digitalWrite(MdrSpa,0);
       digitalWrite(MsgFata,0);
      digitalWrite(MsgSpa,0);
      digitalWrite(MdrFata,0);
      delay(1500);
      
   }
   //Serial.println(c);
   if (p>100 && s==1 && c==0) caramida();

  
 // Serial.print(cm);  Serial.print("cm");  Serial.println();  delay(100);
} 




void caramida()
{
  bs=0;bd=0;
 c=1;
  
//spate
  digitalWrite(MdrSpa,1);
  digitalWrite(MdrFata,0);
  analogWrite(pdr,pw);
  digitalWrite(MsgFata,0);
  digitalWrite(MsgSpa,1);
  analogWrite(psg,pw);
  
  delay (50);
  digitalWrite(MdrSpa,1);
  digitalWrite(MsgSpa,1);
  analogWrite(pdr,80);
 analogWrite(psg,80);
 digitalWrite(MdrFata,0);
 digitalWrite(MsgFata,0);
 
delay (500);


// deviatia dupa caramida
 digitalWrite(MdrSpa,1);
 digitalWrite(MsgSpa,0);
 digitalWrite(MdrFata, 0);
 digitalWrite(MsgFata,1);
 analogWrite(pdr,50);
 analogWrite(psg,0);
 
 
delay (150);

// mergi in dreptul caramizii
//opreste();
 digitalWrite(MdrSpa,0);
 digitalWrite(MsgSpa,0);
 digitalWrite(MdrFata,1);
 digitalWrite(MsgFata,1);
 analogWrite(pdr, 70);
 analogWrite(psg, 50);
delay (1000);
/*
/opreste();

// intoarce 

  analogWrite(MdrSpa,50);
 analogWrite(MsgSpa,0);
 analogWrite(MdrFata, 0);
 analogWrite(MsgFata, 50);
delay (300);
//opreste();
*/
citeste();
while (-prop==limit+1)
 {

citeste();
//Serial.print(proportional);    delay(100);
 digitalWrite(MdrSpa,0);
 digitalWrite(MsgSpa,0);
 digitalWrite(MdrFata,1);
 digitalWrite(MsgFata,1);
 analogWrite(pdr, 100);
 analogWrite(psg, 100);
//  if (proportional<limit-1000 && proportional>-limit+1000) return;
 // delay (500);
 //goto a;
 }
}  
