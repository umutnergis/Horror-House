#include <Arduino.h>
int sensorpin1 = A0;
int sensorpin2 = A1;
int sensorpin3 = A2;
int sensorpin4 = A3;
int sensorpin5 = A4;
int sensorpin6 = A5;
int sensorpin7 = 2;
int starttime;
bool timestate;
int relaypin = 3;


int sensorValue1;
int sensorValue2;
int sensorValue3;
int sensorValue4;
int sensorValue5;
int sensorValue6;
int sensorValue7;

void setup() {
    
    Serial.begin(9600);
    pinMode(sensorpin7,INPUT);
    pinMode(relaypin , OUTPUT);
    digitalWrite(relaypin,LOW);
   
}

void loop() {
     
    readData();
    logData();
   
    if(stateforloop()){
        Serial.println("girdi");
        delay(5000);
        digitalWrite(relaypin, HIGH);
        delay(10000);
        digitalWrite(relaypin,LOW);
        while(sensorValue1 > 350 && sensorValue2 > 410 && sensorValue3 > 300 && sensorValue4 > 420 && sensorValue5 > 510 && sensorValue6 > 400 && sensorValue7 == 1 ) {
           
           readData();
           Serial.println("while ici");
           logData();
           
        digitalWrite(relaypin,LOW);
          }
    }
    else{
        digitalWrite(relaypin, LOW);
    }
    delay(100);
}

bool readData( ){
sensorValue2 = analogRead(sensorpin1);
     sensorValue4 = analogRead(sensorpin2);
     sensorValue3 = analogRead(sensorpin3);
     sensorValue6 = analogRead(sensorpin4);
     sensorValue5 = analogRead(sensorpin5);
     sensorValue1 = analogRead(sensorpin6);
     sensorValue7 = digitalRead(sensorpin7);
     
}

void logData() {
    Serial.println("S1: " + String(sensorValue1) + " S2: " + String(sensorValue2) + " S3: " + String(sensorValue3) + " S4: " + String(sensorValue4) + " S5: " + String(sensorValue5) + " S6: " + String(sensorValue6) + " S7: " + String(sensorValue7));
}

bool stateforloop(){
  if(sensorValue1 > 340 && sensorValue2 > 400 && sensorValue3 > 310 && sensorValue4 > 410 && sensorValue5 > 500 && sensorValue6 > 390 && sensorValue7 == 1){
      starttime = millis();
      timestate = true;
      if(timestate == true){
        if(millis()-starttime <= 5000){
          if(sensorValue1 > 340 && sensorValue2 > 400 && sensorValue3 > 310 && sensorValue4 > 410 && sensorValue5 > 500 && sensorValue6 > 390 && sensorValue7 == 1){
            return true;
            }
          }       
        }
     } 
     else{
      return false;
      }
  }
