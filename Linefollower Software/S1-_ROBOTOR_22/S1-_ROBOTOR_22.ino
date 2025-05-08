/*
  TELECOMANDA          D4

  SENZOR FATA:         D2
  SENZOR STANGA:       A0
  SENZOR DREAPTA:      A1

  MOTOARE:
    DREAPTA: INAINTE   D7
             INAPOI    D8
             VITEZA    D9

    STANGA: INAINTE   D12
             INAPOI    D13
             VITEZA    D11

  BUTOANE:   BUTON1    A2 (D16)
             BUTON2    A3 (D17)
             BUTON3    A4 (D18)
             BUTON4    A5 (D19)
*/

#define TELECOMANDA      3
#define SENZOR_JOS   A3

#define SENZOR_FATA_STANGA 14//0 CAND VEDE
#define SENZOR_FATA_DREAPTA 15//0 CAND VEDE

#define STANGA_INAINTE    8
#define STANGA_INAPOI     7
#define STANGA_VITEZA     9

#define DREAPTA_INAINTE   5
#define DREAPTA_INAPOI    10
#define DREAPTA_VITEZA    6

#define BUTON1           11   //1 CAND E APASAT
#define BUTON2           12
#define BUTON3           13
#define BUTON_JOS_NEGATIV        18 //0 CAND E APASAT

int bs = 0, bd = 0, bstr = 0;
int variabila = 0;

void setup()
{


  //  Serial.begin(9600);
  pinMode(TELECOMANDA, INPUT);

  pinMode(SENZOR_FATA_STANGA, INPUT);
  pinMode(SENZOR_FATA_DREAPTA, INPUT);

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


  // while(digitalRead(TELECOMANDA)==0); //telecomanda


  if (digitalRead(BUTON1) == 0) bs = 1;
  else if (digitalRead(BUTON2) == 0) bd = 1;
  else if (digitalRead(BUTON3) == 0) bstr = 1;
delay(1800);


  while (analogRead(SENZOR_JOS) > 200)
  {
    viteza(100, 100);
    inainte();
  }

  viteza(200, 200); inapoi(); delay(300);

  //viteza(200, 200);
 /// dreapta();
  ///delay(110);
  //oprire();
  //delay(1);




  ///viteza(100,100); inainte(); delay (700); viteza(200,200); inapoi();delay(400); //brasov

}

void loop()
{
  variabila = 0;
  //  if(digitalRead(TELECOMANDA)==0) {oprire(); while(1);} //telecomanda

  // while(digitalRead(BUTON_JOS_NEGATIV)==1){viteza(255,255);inainte();} //inainte si bine
  while (digitalRead(SENZOR_FATA_STANGA) == 0 && digitalRead(SENZOR_FATA_DREAPTA) == 0) {
    viteza(255, 255);  //inainte si bine
    inainte();
  }

  if (digitalRead(SENZOR_FATA_STANGA) == 0 || digitalRead(SENZOR_FATA_DREAPTA) == 0)  {
    variabila = 1;
    viteza(255, 255);
    inainte();
  }
  if (digitalRead(SENZOR_FATA_STANGA) == 0 && digitalRead(SENZOR_FATA_DREAPTA) == 1)  {
    bs = 1;
    bd = 0;
  }
  if (digitalRead(SENZOR_FATA_STANGA) == 1 && digitalRead(SENZOR_FATA_DREAPTA) == 0)  {
    bs = 0;
    bd = 1;
  }

  if (bd == 1 && bs == 0 && variabila == 1) {
    viteza(100, 255);
    inainte();
  }
  if (bs == 1 && bd == 0 && variabila == 1) {
    viteza(255, 100);
    inainte();
  }

  if (bd == 1 && bs == 0 && variabila == 0) {
    viteza(0, 100);
    dreapta();
  }
  if (bs == 1 && bd == 0 && variabila == 0) {
    viteza(100, 0);
    stanga();
  }


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
  digitalWrite(DREAPTA_INAINTE, LOW);
  digitalWrite(DREAPTA_INAPOI, HIGH);

  digitalWrite(STANGA_INAINTE, LOW);
  digitalWrite(STANGA_INAPOI, HIGH);
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
  analogWrite(DREAPTA_VITEZA, y);
}
