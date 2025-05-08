int F2=A2, F3=A3, F4=A4, F5=A5;

void setup(){
  pinMode(F2, INPUT); 
  pinMode(F3, INPUT); 
  pinMode(F4, INPUT); 
  pinMode(F5, INPUT); 
  Serial.begin(9600);     
}

void loop(){      
  Serial.print(analogRead(F2));  
  Serial.print(", ");  
  Serial.print(analogRead(F3));  
  Serial.print(", ");  
  Serial.print(analogRead(F4));  
  Serial.print(", ");  
  Serial.print(analogRead(F5));  
  Serial.print("   -   ");  
  Serial.print(analogRead(F2)/4); 
  Serial.print(", ");  
  Serial.print(analogRead(F3)/4); 
  Serial.print(", ");
  Serial.print(analogRead(F4)/4); 
  Serial.print(", ");
  Serial.print(analogRead(F5)/4); 
  Serial.println(";");  
}