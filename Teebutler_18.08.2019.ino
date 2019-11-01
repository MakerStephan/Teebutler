

// ----------------------------
// --- Teebutler Home       ---
// --- Stephan Maier        ---
// --- 18.08.2019           ---
// ----------------------------
#include <Servo.h>
#include "pitches.h"
 
Servo Arm;              // Servo 1 zuweisen
 
// maximaler Ohr Winkel. Je nach Tassen Höhe anpassen
int max_Winkel=75;
int min_Winkel=10;
int hilfs_Winkel=0;
int zwischen_Winkel=45;
 
// notes in the melody1:
int melody_1[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations_1[] = {4, 8, 8, 4, 4, 4, 4, 4};
// notes in the melody2:
int melody_2[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_C4, 0, 0, 0, 0};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations_2[] = {4, 8, 8, 4, 4, 4, 4, 4};
 
int LED1=8;               // LED  2 minuten
int LED2=7;               // LED  3 minuten
int LED3=6;               // LED  4 minuten
int LED4=5;               // LED  5 minuten
int LED5=4;               // LED  6 minuten
int LED6=3;               // LED  8 minuten
int LED7=2;               // LED 10 minuten
int speakerOut = 10;      // Piezo Lautsprecher
int Time=2;               // Time for Tea in minuten
int xy=0;
int takt=0;
 
void setup() {
  pinMode(speakerOut, OUTPUT);    // Lautsprecher Ausgang
  pinMode(LED1, OUTPUT);          // LED 1
  pinMode(LED2, OUTPUT);          // LED 2
  pinMode(LED3, OUTPUT);          // LED 3
  pinMode(LED4, OUTPUT);          // LED 4
  pinMode(LED5, OUTPUT);          // LED 5
  pinMode(LED6, OUTPUT);          // LED 6
  pinMode(LED7, OUTPUT);          // LED 7
  pinMode(A1, INPUT);             // ON and minutes select switch
  pinMode(A2, INPUT);             // Start / Stop select switch

  // alle LEDs an
  analogWrite(LED1, 255);   // 2 Minuten LED einschalten
  analogWrite(LED2, 255);   // alle anderen aus
  analogWrite(LED3, 255);   // alle anderen aus
  analogWrite(LED4, 255);   // alle anderen aus
  analogWrite(LED5, 255);   // alle anderen aus
  analogWrite(LED6, 255);   // alle anderen aus
  analogWrite(LED7, 255);   // alle anderen aus
    
  Arm.attach(11);         // attaches the servo Arm to pin D11 servo object
  Arm.write(min_Winkel);  // tell servo 1 to go to position 15°
 
  ON_OFF_Sound();         // Play Sound. Ready to make Tea

  analogWrite(LED1, 255);   // 2 Minuten LED einschalten
  analogWrite(LED2, 0);     // alle anderen aus
  analogWrite(LED3, 0);     // alle anderen aus
  analogWrite(LED4, 0);     // alle anderen aus
  analogWrite(LED5, 0);     // alle anderen aus
  analogWrite(LED6, 0);     // alle anderen aus
  analogWrite(LED7, 0);     // alle anderen aus
}
 
void loop() {
 
  if (analogRead(A1) > 900 ) SelectNextTime();    // Mit Taster 1 Zeit einstellen
  if (analogRead(A2) > 900 ) TeaTime() ;          // Mit Taster 2 Tea Time Starten
 
}
// ------------------------------------------------------------------
// ------------------------------------------------------------------
void SelectNextTime(){
  // Warten bis Taster losgelassen
  do { delay(20); }while (analogRead(A1)>500);
 
  // Zeit einstellen. 2,3,5,8,10 & 12 minuten
  switch (Time) {
    case 2:
      Time=3;
      analogWrite(LED1, 0);   // LED's
      analogWrite(LED2, 255);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      analogWrite(LED6, 0);
      analogWrite(LED7, 0);
      //LEDx=LED2;
      break;
    case 3:
      Time=4;
      analogWrite(LED1, 0);   // LED's
      analogWrite(LED2, 0);
      analogWrite(LED3, 255);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      analogWrite(LED6, 0);
      analogWrite(LED7, 0);
      //LEDx=LED3;
      break;
    case 4:
      Time=5;
      analogWrite(LED1, 0);   // LED's
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 255);
      analogWrite(LED5, 0);
      analogWrite(LED6, 0);
      analogWrite(LED7, 0);
      //LEDx=LED4;
      break;
    case 5:
      Time=6;
      analogWrite(LED1, 0);   // LED's
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 255);
      analogWrite(LED6, 0);
      analogWrite(LED7, 0);
      //LEDx=LED5;
      break;
    case 6:
      Time=8;
      analogWrite(LED1, 0);   // LED's
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      analogWrite(LED6, 255);
      analogWrite(LED7, 0);
      //LEDx=LED4;
      break;
    case 8:
      Time=10;
      analogWrite(LED1, 0);   // LED's
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      analogWrite(LED6, 0);
      analogWrite(LED7, 255);
      //LEDx=LED5;
      break;
    case 10:
      Time=2;
      analogWrite(LED1, 255);   // LED's
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      analogWrite(LED6, 0);
      analogWrite(LED7, 0);
      //LEDx=LED1;
      break;
  }
}
// ----------------------------
void TeaTime () {
  // Warten bis Taster losgelassen
  do { delay(20); }while (analogRead(A2)>500);

      // Tee Beutel langsam abwärts bis zum eingestellten Winkel
      for (int p = min_Winkel; p < max_Winkel; p++){
        Arm.write(p);
        delay(20);
      } 
    
 
  // Schleife für die Anzahl der Minuten
  for (int i = 1; i <= Time; i++){
    //if (i<2){

  

    // Diese Schleife dauert 1 Minute.
    for (int x=0;x<=20;x++){
      
    if (i<3){
      if (xy==0){
        analogWrite(LED1, 0);
        xy=1;
      }
      else {
        analogWrite(LED1, 240);
        xy=0;
      }
    }
    if (i==3){
      analogWrite(LED1, 255);
      if (xy==0){
        analogWrite(LED2, 0);
        xy=1;
      }
      else {
        analogWrite(LED2, 240);
        xy=0;
      }
      
    }
    if (i==4){
      analogWrite(LED2, 240);
      if (xy==0){
        analogWrite(LED3, 0);
        xy=1;
      }
      else {
        analogWrite(LED3, 240);
        xy=0;
      }
      
    }
    if (i==5){
      analogWrite(LED3, 255);
      if (xy==0){
        analogWrite(LED4, 0);
        xy=1;
      }
      else {
        analogWrite(LED4, 240);
        xy=0;
      }
      
    }
    if (i==6){
      analogWrite(LED4, 240);
      if (xy==0){
        analogWrite(LED5, 0);
        xy=1;
      }
      else {
        analogWrite(LED5, 240);
        xy=0;
      }
      
    }
    if (i==7 || i==8){
      analogWrite(LED5, 255);
      if (xy==0){
        analogWrite(LED6, 0);
        xy=1;
      }
      else {
        analogWrite(LED6, 240);
        xy=0;
      }
      
    }
    if (i>=9){
      analogWrite(LED6, 240);
      if (xy==0){
        analogWrite(LED7, 0);
        xy=1;
      }
      else {
        analogWrite(LED7, 240);
        xy=0;
      }
      
    }
    
      // Kurz vor Ende der Minute den Beutel anheben.
      if (x>19){
        if (i==5){
          
          for (int p = max_Winkel; p >= zwischen_Winkel; p--){
            Arm.write(p);
            delay(40);
          }
          delay(1000);
          // Tee Beutel langsam abwärts bis zum eingestellten Winkel
          for (int p = zwischen_Winkel; p < max_Winkel; p++){
            Arm.write(p);
            delay(40);
          }
        }
      }
    
      // LED's fade in /out in increments of 5 points:
      for (int fadeValue = 15 ; fadeValue <= 250; fadeValue += 5) {
      //   analogWrite(LED1, fadeValue);
      //   analogWrite(LED7, 255-fadeValue);
      //   analogWrite(LED3, fadeValue);
        // wait for 30 milliseconds to see the dimming effect
        delay(30);
        if (analogRead(A2) > 900 ) break;             // Tea Time Stoppen
      }
 
      // LED's fade in / out in increments of 5 points:
      for (int fadeValue = 250 ; fadeValue >= 15; fadeValue -= 5) {
      //  analogWrite(LED1, fadeValue);
      //  analogWrite(LED7, 255-fadeValue);
      //  analogWrite(LED3, fadeValue);
        // wait for 30 milliseconds to see the dimming effect
        delay(30);
        if (analogRead(A2) > 900 ) break;             // Tea Time Stoppen
      }
    
      if (analogRead(A2) > 900 ) break;             // Tea Time Stoppen
    }
    if (analogRead(A2) > 900 ) break;             // Tea Time Stoppen
  }
  
  // Arm nach oben
  for (int p = max_Winkel; p >=hilfs_Winkel; p--){
    Arm.write(p);
    delay(20);
  }
  delay(500);
  // Tee Beutel langsam abwärts bis zum eingestellten Winkel
  for (int p = hilfs_Winkel; p < min_Winkel; p++){
    Arm.write(p);
    delay(20);
  }
  
  // Warten bis Taster losgelassen
  do { delay(20); }while (analogRead(A2)>500);
  
  for (int nachlauf = 1 ; nachlauf <=5 ; nachlauf++){

    ON_OFF_Sound();         // Play sound ready to make Tea

    for (int minute = 1 ; minute <= 56 ; minute++){

      if (takt==0){
        takt=1;
        analogWrite(LED1, 0);
      }
      else{
        takt=0;
        analogWrite(LED1, 255);
      }

      for (int sekunde = 1 ; sekunde <= 50 ; sekunde++){

        delay(20);
        if (analogRead(A2) > 900 ) break;             // Tea Time Stoppen
      }
      
      if (analogRead(A2) > 900 ) break;             // Tea Time Stoppen
    }

    if (analogRead(A2) > 900) break;
  }
  
  ON_OFF2_Sound();         // Play sound ready to make Tea

  // Warten bis Taster losgelassen
  do { delay(20); }while (analogRead(A2)>500);
  
  // Zeit wieder auf 2 min.
  Time=2;
      analogWrite(LED1, 255);   // LED's
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, 0);
      analogWrite(LED6, 0);
      analogWrite(LED7, 0);
}
 
void ON_OFF_Sound(){
    for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration_1 = 1000 / noteDurations_1[thisNote];
    tone(speakerOut, melody_1[thisNote], noteDuration_1);
    int pauseBetweenNotes = noteDuration_1 * 1.30;
    delay(pauseBetweenNotes);
    noTone(speakerOut);
  }
}

void ON_OFF2_Sound(){
    for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration_2 = 1000 / noteDurations_2[thisNote];
    tone(speakerOut, melody_2[thisNote], noteDuration_2);
    int pauseBetweenNotes = noteDuration_2 * 1.30;
    delay(pauseBetweenNotes);
    noTone(speakerOut);
  }
}
 

