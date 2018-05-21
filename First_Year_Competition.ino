int LM1 = 2;
int LM2 = 3;
int RM1 = 4;
int RM2 = 5;

int speakerPin = 6;
int tempo = 300;
int length = 15;
char notes[] = "ccggaagffeeddc ";

//A0 = Line 1
//A1 = Line 2
//A2 = Greyscale
int valONE = 0;
int valTWO = 0;
int greyVal = 0;

//Greyscale range: 50-400
//C 262: 50 - 100
//D 293: 101 - 150
//E 330: 151 - 200
//F 349: 201 - 250
//G 392: 251 - 300
//A 466: 301 - 350
//B 494: 351 - 400
//C 523: 401 - 450

void playTone(int tone)
{
  digitalWrite(speakerPin, HIGH);
  delayMicroseconds(tone);
  digitalWrite(speakerPin, LOW);
  delayMicroseconds(tone);
}

void playNote(char note)
{
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};

  for(int i = 0; i < 8; i++)
  {
    if (names[i] == note)
    {
      playTone(tones[i]);
    }
  }
}

void setup()
{  
  Serial.begin(9600);
//  pinMode(LM1, OUTPUT);
//  pinMode(LM2, OUTPUT);
//  pinMode(RM1, OUTPUT);
//  pinMode(RM2, OUTPUT);

  pinMode(speakerPin, OUTPUT);

//  pinMode(A0, INPUT);
//  pinMode(A1, INPUT);

  pinMode(A2, INPUT);
}

void loop()
{
//  valONE = analogRead(A0);
//  valTWO = analogRead(A1);
//  Serial.print(valONE);
//  Serial.print(" ");
//  Serial.print(valTWO);
//  Serial.println("");
//
//  if (valONE > 350 || valTWO > 350)
//  {
//    digitalWrite(LM1,  HIGH);
//    digitalWrite(LM2,  LOW);
//    digitalWrite(RM1,  HIGH);
//    digitalWrite(RM2,  LOW);
////    Serial.println("Backward");
//  }
//  else
//  {
//    digitalWrite(LM1,  LOW);
//    digitalWrite(LM2,  HIGH);
//    digitalWrite(RM1,  LOW);
//    digitalWrite(RM2,  HIGH);
////    Serial.println("Forward");
//  }

  greyVal = analogRead(A2);
  Serial.println(greyVal);

  char note = ' ';
  if (greyVal < 100)
  {
    note = 'c';
    playNote(note);
  }
  else if (greyVal < 200)
  {
    note = 'd';
    playNote(note);
  }
  else if (greyVal < 300)
  {
    note = 'e';
    playNote(note);
  }
  else if (greyVal < 400)
  {
    note = 'f';
    playNote(note);
  }
  else if (greyVal < 500)
  {
    note = 'g';
    playNote(note);
  }
  else if (greyVal < 600)
  {
    note = 'a';
    playNote(note);
  }
  else if (greyVal < 700)
  {
    note = 'b';
    playNote(note);
  }
  else
  {
    note = 'C';
    playNote(note);
  }
}

