volatile int index = 0;
long iDelay= 0;
long period = 0;
long prevInterrupt = 0;

int valueArray[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

const byte interruptPin = 2;
volatile byte state = LOW;


void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), lectura, CHANGE);
  
  Serial.begin(9600);
  prevInterrupt = millis();
  
}

void loop() {
  // se lee la muestra
  valueArray[index] = analogRead(A0);
  //Se envia el valor
  Serial.write(valueArray[index]);
  // aumento del contador
  index++;
  // Espera a la siguiene muestra.
  delay(iDelay);
}

void lectura(){
  index = 0;
  long actInterrupt = millis();
  period = actInterrupt - prevInterrupt;
  iDelay = period/12;
  prevInterrupt = actInterrupt;
}

