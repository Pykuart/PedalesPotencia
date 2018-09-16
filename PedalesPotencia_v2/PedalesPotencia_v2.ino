#include <stdlib.h>

volatile int index = 0;
long iDelay= 0;
long period = 0;
long prevInterrupt = 0;

String valueArray[12] = {"","","","","","","","","","","",""};

const byte interruptPin = 2;
volatile byte transmit = LOW;
volatile byte controlLectura = HIGH;


void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), lectura, CHANGE);
  
  Serial.begin(9600);
  prevInterrupt = millis();
  
}

void loop() {
  if(controlLectura && (millis() >= (iDelay*(index+1)))){
    // se lee la muestra
    char buf[4];
    itoa(analogRead(A0),buf,10);
    valueArray[index] = buf;
    // aumento del contador
    index++;
    if(index>11){
      controlLectura = LOW;
      transmit = HIGH;
    }
  }
  if(transmit){
    //Se envia el valor
    Serial.write(valueArray, 12);
    transmit = !controlLectura;
  }
}

void lectura(){
  long actInterrupt = millis();
  period = actInterrupt - prevInterrupt;
  iDelay = period/12;
  prevInterrupt = actInterrupt;
  index = 0;
  transmit = HIGH;
  controlLectura = HIGH;
}

