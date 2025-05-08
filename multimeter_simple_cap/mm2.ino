#define analogPin 0          
#define chargePin 13         
#define dischargePin 11        
#define resistorValue 10000.0F   

unsigned long startTime;
unsigned long elapsedTime;               
float nF;

void setup(){
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);  
  Serial.begin(9600);             
}

void loop(){
//charge 
  digitalWrite(chargePin, HIGH);  
  startTime = millis();
  while(analogRead(analogPin) < 648){}
  elapsedTime= millis() - startTime;
//calculate value
  nF = ((float)elapsedTime / resistorValue) * 1000* 10000;   
  Serial.print((long)nF);       
  Serial.println(" nF");     
//stop charging  
  digitalWrite(chargePin, LOW);    
//discharge        
  pinMode(dischargePin, OUTPUT);            
  digitalWrite(dischargePin, LOW); 
  while(analogRead(analogPin) > 0){}
  pinMode(dischargePin, INPUT);            
} 