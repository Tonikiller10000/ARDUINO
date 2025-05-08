if(!cap_scale)
    {       
      pinMode(A1,INPUT);
      pinMode(A2, OUTPUT);  
      pinMode(C, OUTPUT); 
      digitalWrite(A2, LOW); 
      digitalWrite(C, HIGH);  
      startTime = micros();
      while(analogRead(A1) < 648){}  
      
      //nF = 1000*microF;
      elapsedTime= micros() - startTime;
      microFarads = ((float)elapsedTime / resistorValue) - 0.01097;
      if (microFarads > 1){ Serial.print(microFarads); Serial.println(" uF"); }
      else cap_scale = true; 
      //Dharging the capacitor    
      digitalWrite(C, LOW);            
      pinMode(D, OUTPUT);            
      digitalWrite(D, LOW);         
      while(analogRead(A1) > 0){}   
      pinMode(D, INPUT);             
    }



///////////////////////////////////////


    if(cap_scale)
    {      
      pinMode(D,INPUT);
      pinMode(C,INPUT);
      pinMode(A2,OUTPUT);
      pinMode(A1, INPUT);
      
      digitalWrite(A2, HIGH);
      int val = analogRead(A1);
      digitalWrite(A2, LOW);
  
      if (val < 1000)
      {
        pinMode(A1, OUTPUT);  
        float capacitance = (float)val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);
        
        Serial.print(capacitance,0);
        Serial.println(" pF");

      }
      
      else
      {
        pinMode(A1, OUTPUT);
        delay(1);
        pinMode(A2, INPUT_PULLUP);
        unsigned long u1 = micros();
        unsigned long t;
        int digVal;  
        do
        {
          digVal = digitalRead(A2);
          unsigned long u2 = micros();
          t = u2 > u1 ? u2 - u1 : u1 - u2;
        }         
        while ((digVal < 1) && (t < 400000L));
  
        pinMode(A2, INPUT);  
        val = analogRead(A2);
        digitalWrite(A1, HIGH);
        int DhargeTime = (int)(t / 1000L) * 5;
        delay(DhargeTime);   
        pinMode(A2, OUTPUT);  
        digitalWrite(A2, LOW);
        digitalWrite(A1, LOW);
        float capacitance = -(float)t / R_PULLUP / log(1.0 - (float)val / (float)MAX_ADC_VALUE);
                                
        if (capacitance > 1000.0)
        {          
          /*Serial.print(capacitance / 1000.0, 2);
          Serial.println(" uF");*/
          cap_scale = false;          //We change the scale to 1uF - max        
        }          
        else{ Serial.print(capacitance);Serial.println(" nF"); }
      }
      while (micros() % 1000 != 0);
    }    












}
