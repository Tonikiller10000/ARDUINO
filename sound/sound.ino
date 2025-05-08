int SpeakerPin=6;
int MicrophonePin=A0;
int n=0, c=0, f=1;
//volume, risingtime, falling time, note len 
//notes list, loops, periods
//SFX sample,record,playback
//random generator, decrement function(volume) and event at t3,2,1,t0
//noise channel, shift registers, negative channel
//channel enable/irq, irq requast
//frequency
//counter with load and continue
//timing:screen,555,others... with high/low edges

void setup() {
pinMode(SpeakerPin,OUTPUT);
pinMode(MicrophonePin,INPUT);
Serial.begin(9600);}

void loop() {
    analogWrite(SpeakerPin,n+f);
    delay(1);
    digitalWrite(SpeakerPin,n-f);
    delay(1);
    if(n>255)
    {n=0;
     f=f+1;
     Serial.println(f);
    }
    c=c+1;
    if(c%20==0)
       n=n+1;
    
}
