

#define TELECOMANDA      3
  
#define SENZOR_JOS 2  
#define SENZOR_FATA_STANGA 15//0 CAND VEDE
#define SENZOR_FATA_DREAPTA 14//0 CAND VEDE
  
#define STANGA_INAINTE      11
#define STANGA_INAPOI       9
#define STANGA_VITEZA       10
            
#define DREAPTA_INAINTE   8
#define DREAPTA_INAPOI    7
#define DREAPTA_VITEZA    6
    
#define BUTON1           12   //1 CAND E APASAT
#define BUTON2           13
#define BUTON3           5
#define BUTON_JOS_NEGATIV        18 //0 CAND E APASAT

int bs=0,bd=0,bstr=0;
int variabila=0;

void setup()
{
  

//  Serial.begin(9600);
  pinMode(TELECOMANDA, INPUT);

  pinMode(SENZOR_FATA_STANGA, INPUT);
  pinMode(SENZOR_FATA_DREAPTA, INPUT);
  pinMode(SENZOR_JOS, INPUT);


  pinMode(BUTON1, INPUT);
  pinMode(BUTON2, INPUT);
  pinMode(BUTON3, INPUT);
  pinMode(BUTON_JOS_NEGATIV, INPUT);
  digitalWrite(BUTON1, HIGH);
  digitalWrite(BUTON2, HIGH);
  digitalWrite(BUTON3, HIGH);
  digitalWrite(BUTON_JOS_NEGATIV, HIGH);
  
  pinMode(STANGA_INAINTE, OUTPUT);
  pinMode(STANGA_INAPOI, OUTPUT);
  pinMode(STANGA_VITEZA, OUTPUT);

  pinMode(DREAPTA_INAINTE, OUTPUT);
  pinMode(DREAPTA_INAPOI, OUTPUT);
  pinMode(DREAPTA_VITEZA, OUTPUT);

  //while(digitalRead(TELECOMANDA)==0); //telecomanda

 
   if (digitalRead(BUTON1)==0) bs=1;
   else if (digitalRead(BUTON2)==0) bd=1;
   else if (digitalRead(BUTON3)==0) bstr=1;

delay(1800);


while (analogRead(SENZOR_JOS) > 50)
  {
    viteza(80, 80);
    inainte();
  }

 viteza(200, 200); inapoi(); delay(300);


  //viteza(200, 200);
 // dreapta();
 // delay(110);
 // oprire();
  //delay(1);


}




void loop()
{
  variabila = 0;
 // if(digitalRead(TELECOMANDA)==0) {oprire(); while(1);} //telecomanda

  //while(digitalRead(BUTON_JOS_NEGATIV)==1){viteza(255,255);inainte();} //inainte si bine


 
  while(digitalRead(SENZOR_FATA_STANGA)==0 && digitalRead(SENZOR_FATA_DREAPTA)==0){viteza(255,255);inainte();} //inainte si bine

  if (digitalRead(SENZOR_FATA_STANGA)==0 || digitalRead(SENZOR_FATA_DREAPTA)==0)  {variabila=1;viteza(255,255);inainte();}
  if (digitalRead(SENZOR_FATA_STANGA)==0 && digitalRead(SENZOR_FATA_DREAPTA)==1)  {bs=1;bd=0;}
  if (digitalRead(SENZOR_FATA_STANGA)==1 && digitalRead(SENZOR_FATA_DREAPTA)==0)  {bs=0;bd=1;}

  if (bd==1 && bs==0 && variabila==1){viteza(0,120);inainte();}
  if (bs==1 && bd==0 && variabila==1){viteza(120,0);inainte();}
      
  if (bd==1 && bs==0 && variabila==0){viteza(120,0);dreapta();}
  if (bs==1 && bd==0 && variabila==0){viteza(0,120);stanga();}
    
  
}

void inainte()
{
  digitalWrite(DREAPTA_INAINTE, HIGH);
  digitalWrite(DREAPTA_INAPOI, LOW);
  
  digitalWrite(STANGA_INAINTE, HIGH);
  digitalWrite(STANGA_INAPOI, LOW);
//if(digitalRead(TELECOMANDA)==0) {oprire(); while(1);}

}

void inapoi()
{
  digitalWrite(DREAPTA_INAINTE, 0);
  digitalWrite(DREAPTA_INAPOI, 1);
  
  digitalWrite(STANGA_INAINTE, 0);
  digitalWrite(STANGA_INAPOI, 1);
}

void oprire()

{
  digitalWrite(DREAPTA_INAINTE, LOW);
  digitalWrite(DREAPTA_INAPOI, LOW);
  
  digitalWrite(STANGA_INAINTE, LOW);
  digitalWrite(STANGA_INAPOI, LOW);
}

void stanga()
{
  digitalWrite(DREAPTA_INAINTE, HIGH);
  digitalWrite(DREAPTA_INAPOI, LOW);
  
  digitalWrite(STANGA_INAINTE, LOW);
  digitalWrite(STANGA_INAPOI, HIGH);
}

void dreapta()
{
  digitalWrite(DREAPTA_INAINTE, LOW);
  digitalWrite(DREAPTA_INAPOI, HIGH);
  
  digitalWrite(STANGA_INAINTE, HIGH);
  digitalWrite(STANGA_INAPOI, LOW);
}


void viteza(int x, int y)
{
  analogWrite(STANGA_VITEZA, x);
  analogWrite(DREAPTA_VITEZA,y);
}
