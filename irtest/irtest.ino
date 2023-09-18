#include <IRremote.h>
const int  VCC=2, GND2=3, RECV_PIN = 4, SW1A=8, SW1B=7, SW2A=6, SW2B=5, R = 9, GND=10, G = 11, B = 12;
int GND3 = A3;// Ligth1 = A4, Light2 = A5
int gnd = 136, Latch1=-1, Latch2=-1, SWR1=1, SWR2=1;
IRrecv irrecv(RECV_PIN);
decode_results results;

void color(int r,int g,int b)
{if(r!=256)
 analogWrite(R,r);
 if(g!=256)
 analogWrite(G,g);
 if(b!=256)
 analogWrite(B,b);}
void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(GND,OUTPUT);
  pinMode(GND2,OUTPUT);
  pinMode(GND3,OUTPUT);
  pinMode(VCC,OUTPUT);
  digitalWrite(VCC, HIGH);
  digitalWrite(GND2, LOW);  
  digitalWrite(GND3, LOW);
  analogWrite(GND,gnd);
  pinMode(SW1A,OUTPUT);
  pinMode(SW1B,INPUT);
  pinMode(SW2A,OUTPUT);
  pinMode(SW2B,INPUT);
  digitalWrite(SW1A, HIGH);
  digitalWrite(SW2A, HIGH); 
  }

void loop(){
  if (irrecv.decode(&results)){
    switch(results.value){
          case 0xFFA25D:
          Serial.println("POW");
          color(0,0,0);
          break;
          case 0xFF629D:
          Serial.println("STOP");
          break;
          case 0xFFE21D:
          Serial.println("MUTE");
          break;
          case 0xFF22DD:
          Serial.println("MODE");
          break;
          case 0xFF02FD:
          Serial.println("BACK");
          break ;  
          case 0xFFC23D:
          Serial.println("EQ");
          break ;               
          case 0xFFE01F:
          Serial.println("|<<");
          if(gnd<=238){
              gnd=gnd+17;
              analogWrite(GND,gnd);}
          break ;  
          case 0xFFA857:
          Serial.println(">>|");
          if(gnd>=17){
              gnd=gnd-17;
              analogWrite(GND,gnd);}
          break ;  
          case 0xFF906F:
          Serial.println(">||");
          break ;  
          case 0xFF6897:
          Serial.println(">>>>");
          break ;  
          case 0xFF9867:
          Serial.println("<<<<");
          break ;
          case 0xFFB04F:
          Serial.println("0");
          color(255,255,255);
          break ;
          case 0xFF30CF:
          Serial.println("1");
          color(255,256,256);
          break ;
          case 0xFF18E7:
          Serial.println("2");
          color(256,255,256);
          break ;
          case 0xFF7A85:
          Serial.println("3");
          color(256,256,255);
          break ;
          case 0xFF10EF:
          Serial.println("4");
          color(0,256,256);
          break ;
          case 0xFF38C7:
          Serial.println("5");
          color(256,0,256);
          break ;
          case 0xFF5AA5:
          Serial.println("6");
          color(256,256,0);
          break ;
          case 0xFF42BD:
          Serial.println("7");
          break ;
          case 0xFF4AB5:
          Serial.println("8");
          break ;
          case 0xFF52AD:
          Serial.println("9");
          break ;
          default:
          Serial.println("-");  
        } 
        irrecv.resume();}
  if (digitalRead(SW1B)==HIGH) { 
    if(SWR1){
      Latch1*=-1;
      SWR1=0;}}   
  else
    SWR1=1;    
  if (digitalRead(SW2B)==HIGH) { 
    if(SWR2){
      Latch2*=-1;
      SWR2=0;}}
  else
    SWR2=1 ;
  if (Latch1>0)
      digitalWrite(A4,HIGH);
  else
      digitalWrite(A4,LOW);
  if (Latch2>0)
      digitalWrite(A5,HIGH);
  else
      digitalWrite(A5,LOW);

}
