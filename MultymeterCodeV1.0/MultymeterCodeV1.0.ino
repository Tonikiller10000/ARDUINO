#include <TFT.h>  
#include <SPI.h>


#define R20K 5
#define GND1 4
#define CapacitorPin        0          
#define CapacitorChargePin    6         
#define CapacitorDischargePin 7        
#define ResistorValue         10000.0F

unsigned long startTime;
unsigned long elapsedTime;               
float CapacitorValue, LastCapacitorValue;
int i=1;
int GndState=0;


//TFT TFTscreen = TFT(10, 9, 8); // CS,A0,RESET
void setup() {

  pinMode(R20K, OUTPUT);  
  digitalWrite(R20K, LOW);
  pinMode(R20K, INPUT); 
  pinMode(GND1, OUTPUT);  
  digitalWrite(GND1, LOW);
  pinMode(GND1, INPUT);  
  pinMode(A5, INPUT);  

  //TFTscreen.begin();
  pinMode(CapacitorChargePin, OUTPUT);     
  digitalWrite(CapacitorChargePin, LOW);  
  Serial.begin(9600); 
}

void loop() {
if(digitalRead(A5)==HIGH)
  GndState=1;
else
  GndState=0;
if(GndState==0){
  pinMode(GND1, INPUT); 
}
else{
  pinMode(GND1, OUTPUT);  
  digitalWrite(GND1, LOW);
}


//charge 
  digitalWrite(CapacitorChargePin, HIGH);  
  startTime = millis();
  while(analogRead(CapacitorPin ) < 648){}
  elapsedTime= millis() - startTime;
//calculate value
  CapacitorValue = ((float)elapsedTime / ResistorValue) *1000 *1000;   
  if(CapacitorValue < LastCapacitorValue-100 || CapacitorValue > LastCapacitorValue+100){
    LastCapacitorValue = CapacitorValue;
    //update(CapacitorValue);
  }
  Serial.print(GndState%2);
  Serial.print(" --- ");        
  Serial.print((long)CapacitorValue);       
  Serial.println(" nF");     
//stop charging & discharge 
  digitalWrite(CapacitorChargePin, LOW);          
  pinMode(CapacitorDischargePin, OUTPUT);            
  digitalWrite(CapacitorDischargePin, LOW); 
  while(analogRead(CapacitorPin ) > 0){}
  pinMode(CapacitorDischargePin, INPUT);    
  
  
}










/*
void update(float CapacitorValue){
  String t;
  char s[20];
  t = String(CapacitorValue);
  t.toCharArray(s,20);       
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  //TFTscreen.stroke(random(0, 255), random(0, 255), random(0, 255));
  TFTscreen.stroke(255,255,255);  
  TFTscreen.text((int)s, 10, 35);   
  TFTscreen.text("m", 120, 5);     
  TFTscreen.text("uF", 120, 20);    
  TFTscreen.text("nF", 120, 35);   
  TFTscreen.text("pF", 120, 50);   
  //TFTscreen.line(0,64,160,64);
  //TFTscreen.rect(50,34,60,60);

}
*/












