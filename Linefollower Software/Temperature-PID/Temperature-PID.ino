int PWM_pin = 3, TempRead_pin = 4;
float temperature_read = 0.0;
float set_temperature = 100;
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
int PID_value = 0;
int kp = 9.1;   int ki = 0.3;   int kd = 1.8;
int PID_p = 0;    int PID_i = 0;    int PID_d = 0;

void setup() {
  pinMode(PWM_pin,OUTPUT);
  Time = millis(); 
}

void loop() {
  temperature_read = analogRead(TempRead_pin); 
  PID_error = set_temperature - temperature_read;
  PID_p = kp * PID_error;
  if(-3 < PID_error <3)//calculate PID_i if is in (-3,3)
    PID_i = PID_i + (ki * PID_error);

  timePrev = Time;                            
  Time = millis();                            
  elapsedTime = (Time - timePrev) / 1000; 

  PID_d = kd*((PID_error - previous_error)/elapsedTime);
  PID_value = PID_p + PID_i + PID_d;

  //set PWM range between 0 and 255
  if(PID_value < 0) PID_value = 0;    
  if(PID_value > 255) PID_value = 255; 
  
  analogWrite(PWM_pin,255-PID_value);
  previous_error = PID_error;     

  //delay(300);
  //serial.println(temperature_read)
}

