
void ArduinoInternalComparator(){
//comparator on pin D6
//ADCSRB: |-|ACME|-|-|-|ADTS2|ADTS1|ADTS0|
//ACSR:   |ACD|ACBG|ACO|ACI|ACIE|ACIC|ACIS1|ACIS0|
//ADCSRA = 0b00000000;
//ADCSRB = 0b01000000;//4bit??
//ASRC   = 0b00010011;
//ADMUX =0

//ACBG set comparator Positive Input : LOW to D6 HIGH to code reference

//ACIS1 ACIS2 - interrupt mode
//0 0 - on output toggle
//0 1 - Reserved
//1 0 - on falling edge
//1 1 - on rising edge

//ACO is the comparator output and run an interrupt at every value change

// ---Analog Comparator Negative Input---
// ACME ADEN  MUX2..0 
// 0    x     xxx       D7
// 1    1     xxx       D7
// 1    0     000       ADC0
// 1    0     001       ADC1
// 1    0     010       ADC2
// 1    0     011       ADC3
// 1    0     100       ADC4
// 1    0     101       ADC5
// 1    0     110       ADC6
// 1    0     111       ADC7
}









/*

ISR (PCINT0_vect){
//...
}
ISR (PCINT1_vect){
//...
}

cli(); //disable interrupts
sei(); //enable interrupts


*/






int a=2,b=7;


void setup() {
  
// DDRB = B00000010;  // set D9 as OUTPUT
// DDRD = B00001000;  // set D3 as OUTPUT
// DDRC = B00001100;  // set A2 and A3 as OUTPUT
// PORTB = B00000010; // set D9 to HIGH
// PORTD = B00001000; // set D3 to HIGH
// PORTC = B00000100; // set A3 to LOW and A2 to HIGH


Serial.begin(9600);	

}

void loop() {


// PORTC |= B00000001;  // set the A0 to HIGH
// PORTC &= !B00000001;  // set the A0 to LOW
// int D3_value1 = PIND & B00001000; // B00001000 or B00000000
// int D3_value2 = (PIND & B00001000) >> 3; // 1 or 0






if(a+0.3>b) 
    a=b;
Serial.print("a=");
Serial.print(a);
Serial.print("b=");
Serial.println(b);
delay(1000);






/*
PCICR : 0, 0, 0, 0, 0, PCIE2, PCIE1, PCIE0
group 0/ PCIE0 = D8-D13 (0-5) 
group 1/ PCIE1 = A0-A6  (8-13)
group 2/ PCIE2 = D0-D7  (16-23)
*/
PCICR  |= B00000100;  // Enable PCMSK0, 1, 2 (port 0,1 and 2 interrupts)

PCMSK0 |= B00000101; // D8 and D10 will trigger interrupts
PCMSK1 |= B00100001; // A0 will trigger interrupts
PCMSK2 |= B00100000; // D5 will trigger interrupts
}

/*
TCCR1B : 7,6,5,4,3, CS12, CS11, CS10

000 - no clk surce 
001 - clk
010 - clk/8
011 - clk/64
100 - clk/256
101 - clk/1024
110 - external clk source on T1(falling edge)
111 - external clk source on T1(rising edge)


TCCR1A = 0;
TCCR1B = B00000100;  // clk/256
TIMSK1 = B00000010;  // set OCIE1A to 1 when match to A
OCR1A =31250;
TCNT1  =0;             //reset timer value at 0


TIMERX_COMPY_vect
X = {0,1,2}
Y = {A,B}


ISR(TIMER1_COMPA_vect){
TCNT1=0;
ledstate=!ledstate;
digitalWrite(5,ledstate);

}

*/
/*
ADMUX:
0000 - ADC0
0111 - ADC7
1000 - ADC8 // bad temperature sensor
1110 - 1.1V
1111 - 0V(GND)
ADMUX |= B00000100; // A4 is connected to conversion block

REFS1, REFS0 
00 - aref
01 - avcc
10 - aref
11 - 1.1V
ADMUX |= B11000000; // mode 4(11 - 1.1V)
 analogReference(INTERNAL); //multiple modes

ADCSRA = |= B11000000; // ADEN and ADSC to 1
//wait until ADSC is 0 and read ADCH and ADCL
while(bit_is_set(ADCSRA, ADSC));
int value = ADCL | (ADCH << 8);

ADCSRA |= B00000111; //prescalar to 128 ->125KHz

*/

/*
#include <EEPROM.h>
EEPROM.read(address);
EEPROM.write(address, value0-255)

int a;
float b;
EEPROM.get(address,a); //   int = 2 bytes
EEPROM.get(address,b); // float = 4 bytes
EEPROM.put(address,a);
EEPROM.put(address,b);

*/





















