// interrupt freq = clock speed/ prescaler*(compare match register + 1)
// compare match register = [42000000Hz/ (prescaler*desired interrupt frequency)]-1
// portD = byte(127+127*sin(t/100))

// libraries
#include <QTRSensors.h>

// set up pin
int leftPower = 5;
int leftDirection = 6;
int rightPower = 10;
int rightDirection = 11;
int sensor1 = 2;
int sensor2 = 3;
int graySensor = 4;
int speaker = 9;

byte LED_PIN = 10;
byte LED_BIT = 2;


boolean toggle0 = 0;
boolean toggle1 = 0;
boolean toggle2 = 0;

int t = 0;

frequency = analogRead(A4);


void setup() 
{ 
  pinMode(leftPower, OUTPUT);  
  pinMode(rightPower, OUTPUT);
  pinMode(leftDirection, OUTPUT);  
  pinMode(rightDirection, OUTPUT); 
  pinMode(sensor1, OUTPUT);
  pinMode(sensor2, OUTPUT);
  pinMode(graySensor, OUTPUT);
  pinMode(speaker, OUTPUT);

  Serial.begin(9600);
  
  delay (2000);

  DDRD = 0xFF;
  cli();

  //set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
    
  // set timer 1 to interrupt at  1HZ
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

//set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  TCCR2B |= (1 << CS21);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);


sei();//allow interrupts

}//end setup

ISR(TIMER0_COMPA_vect){
  if (toggle0){
    digitalWrite(9,HIGH);
    toggle0 = 0;
  }
  else{
    digitalWrite(9,LOW);
    toggle0 = 1;
  }
}

ISR(TIMER1_COMPA_vect){
  if (toggle1){
    digitalWrite(11,HIGH);
    toggle1 = 0;
  }
  else{
    digitalWrite(11,LOW);
    toggle1 = 1;
  }
}
  
ISR(TIMER2_COMPA_vect){
  if (toggle2){
    digitalWrite(6,HIGH);
    toggle2 = 0;
  }
  else{
    digitalWrite(6,LOW);
    toggle2 = 1;
  }
}



// main loop
void loop() 
{  
  int power = 0;
  sensorA = digitalRead(sensorValue[1]);
  sensorB = digitalRead(sensorValue[2]);

  while (sensorA ==0 && sensorB ==0)
  {  
    drive(50);
    delay(1200000);
    grayscale();
    while (sensorA !=0 || sensorB !=0)
      lineFollow();
  }

  
 }

// line follow loop
void lineFollow(int sensorA)
{  
    if (sensorA == HIGH)
    {
      digitalWrite(leftPower,HIGH);
      digitalWrite(leftDirection,LOW);
      digitalWrite(rightPower,LOW);
      digitalWrite(rightDirection,LOW);
     }
    else
    {
      digitalWrite(rightPower,LOW);
      digitalWrite(rightDirection,HIGH);
      digitalWrite(leftPower,LOW);
      digitalWrite(leftDirection,LOW);
    }
  }


// drive at power function
void drive(int power)
{
  motor[motorA] = motor[motorC] = power;
}


// detect grayscale
void grayscale()
{
  int grayScale = 0;
  grayScale = analogRead(0);
  Serial.println(grayScale,DEC);
  delay (100);
}


// play music
int speakerOut (int tempo, int elapsedTime, int duration, int pause)
{
  while (elapsedTime < duration)
  {
    digitalWrite(speakerOut, HIGH);
    delay (2000);
    elapsedTime += elapsedTime;
  }
}

int sineWave (int time)
{
  time = time();
  int frequency = 0;
  frequency = sin(2*PI/255*time);
  return frequency;
}

double time()
{
  int size = 256;
  int array[size];

  for (count = 1; count < size; count++)
  {
    count +=0.1;
    printf()
    return count;  
  }
}

\\running the motor at three different speeds
{
  #include <Stepper.h>

// the number of steps on your motor
#define STEPS 200

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 7, 9, 8, 10);

// the previous reading from the analog input
long previous = STEPS / 2;

void setup()
{
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(30);
}

void loop()
{
  // get the sensor value.  This equation maps the
  // analogRead range to the number of steps, so the
  // motor nicely tracks a potentiometer's position
  long val = (long)analogRead(0) * STEPS / 1024;

  // move a number of steps equal to the change in the
  // sensor reading
  stepper.step(val - previous);

  // remember the previous value of the sensor
  previous = val;
}

}


