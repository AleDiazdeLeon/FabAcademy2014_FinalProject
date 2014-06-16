//LIBRARIES
#include <Arduino.h> 

//SPEAKER STUFF
#define NOTE_C 1915
#define NOTE_D 1700
#define NOTE_E 1519 
#define NOTE_F 1432
#define NOTE_G 1275
#define NOTE_A 1136
#define NOTE_B 1014
#define NOTE_c 956
#define NOTE_B0 31
#define NOTE_C4 262
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_DS8 4978
#define NOTE_B2 123
int notes[] = {NOTE_DS8,NOTE_B2,NOTE_C,NOTE_C4,NOTE_B0,NOTE_D,NOTE_G3,NOTE_E,NOTE_F,NOTE_A3,NOTE_G,NOTE_B3,NOTE_A,NOTE_B,NOTE_c};

//INPUTS
int sel1Pin = 3;     // the number of the SELECTOR 1
int sel2Pin = 2;     // the number of the SELECTOR 2
int sel3Pin = 1;     // the number of the SELECTOR 3

//OTPUTS
int speakerPin = 7;      // the number of the speaker
int ledPin = 8;      // the number of the LED
int servoPin = 10;      // the number of the servo

//POTENTIOMETER
int potValueL;         // variable en el que se almacena el dato leído
int potValueS;         // variable en el que se almacena el dato leído
int potVal;
int potPin = 0;       // potenciómetro conectado al pin 0

//SERVO
int minPulse = 500;   // Minimum servo position
int maxPulse = 2500;  // Maximum servo position
int pulse = 0;        // Amount to pulse the servo
int lastPulse = 0;    // the time in milliseconds of the last pulse
int refreshTime = 0; // the time needed in between pulses
int analogValue = 0;  // the value returned from the analog sensor

//SELECTOR
int buttonState = 0;         // variable for reading the pushbutton status

//SPEAKER MELODY
/*int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 30;

//SPEAKER PLAYS MELODIES WITHOUT LIBRARY
void playTone(int tone, int duration) {
for (long i = 0; i < duration * 1000L; i += tone * 2) {
digitalWrite(speakerPin, HIGH);
delayMicroseconds(tone);
digitalWrite(speakerPin, LOW);
delayMicroseconds(tone);
 }
}
void playNote(char note, int duration) {
char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

// play the tone corresponding to the note name
for (int i = 0; i < 8; i++) {
if (names[i] == note) {
playTone(tones[i], duration);
  }
 }
}
*/

void setup()
{ 
// Initialize selector pins as inputs:
  pinMode(sel1Pin, INPUT);
  pinMode(sel2Pin, INPUT);
  pinMode(sel3Pin, INPUT);   
// Initialize component pins as inputs:
  pinMode(speakerPin, OUTPUT);   // sets speaker as output. Only if it's not woring with analog (potentiometer)
  pinMode(ledPin, OUTPUT);   // sets LED as output
  pinMode(servoPin, OUTPUT);   // sets servo as output
// Initialize servo:
   pulse = minPulse;           // Set the motor position value to the minimum
}

void loop(){
  
// ACTIVATE LED and potentiometer -------------------------------------------------

  buttonState = digitalRead(sel1Pin);{
    
  if (buttonState == HIGH) {  
  potValueL = analogRead(potPin);
  potValueL = map(potValueL, 0, 1023, 0, 255);
  analogWrite(ledPin, potValueL); 
}
else {
  digitalWrite(ledPin, LOW);
  }
 }

// ACTIVATE SPEAKER and potentiometer----------------------------------------------------------

  buttonState = digitalRead(sel2Pin);{
    
    if (buttonState == HIGH) {  
    int potValueS = analogRead(potPin); // 0 - 1023
    // divide by 69 as we have 15 pitches. 1023/15 ~ 68.5
    int notes = potValueS/69;
    analogWrite(speakerPin, notes);

    //delay(100); 
  }
    
    else {
  digitalWrite(speakerPin, LOW);
  }
 }

/*
SPEAKER PLAYS MELODY, NO POTENTIOMETER-----------------------------------------------------------------
{ buttonState = digitalRead(sel2Pin);
//val = analogRead(speakerPin);   // lee la tensión en el pin
 
  if (buttonState == HIGH) {     
    // turn LED on:    
    //analogWrite(speakerPin, val / 4);  // los valores de analogRead van desde 0 a 1023 y los valores de analogWrite values van desde 0 a 255, por eso ajustamos el ciclo de trabajo a el valor leído dividido por 4.
for (int i = 0; i < length; i++) {
if (notes[i] == ' ') {
delay(beats[i] * tempo); // rest
} 
else {
playNote(notes[i], beats[i] * tempo);
}
// pause between notes
delay(tempo / 64); 
}

  }
  else {
     //turn speaker off:
   digitalWrite(speakerPin, LOW); 
  }  
}
}
*/

 // ACTIVATE SERVO ---------------------------------------------------------------------------------------------
  /* 
 Part of the Servo Code by Tom Igoe
 additions by Carlyn Maw
 Created 28 Jan. 2006
 Updated 7 Jun. 2006
 */
  
  buttonState = digitalRead(sel3Pin);{ 
    if (buttonState == HIGH) {  
  analogValue = analogRead(potPin);      // read the analog input
  pulse = (analogValue / 10) * 19 + 500;    // convert the analog value to a range between minPulse and maxPulse. 
  // pulse the servo again if rhe refresh time (20 ms) have passed:
  if (millis() - lastPulse >= refreshTime) {
    digitalWrite(servoPin, HIGH);   // Turn the motor on
    delayMicroseconds(pulse);       // Length of the pulse sets the motor position
    digitalWrite(servoPin, LOW);    // Turn the motor off
    lastPulse = millis();           // save the time of the last pulse
  }
}
 else {
  digitalWrite(servoPin, LOW);
  }
}
}

