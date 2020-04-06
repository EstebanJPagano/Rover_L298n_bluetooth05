/*
  Autor: elpagano  
*/

#include <AFMotor.h>
#include <Servo.h>           // Add Servo library
#include <SoftwareSerial.h> // libreria que permite establecer pines digitales

SoftwareSerial miBT(19, 18);   // pin 19 como RX, pin 18 como TX

// ----------- Puenteh

// AF_DCMotor motor1(1);
// AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int speedCarFast = 255;      // variable para almacenar valor de velocidad
int speedCarMid = 210;      // variable para almacenar valor de velocidad
int speedCarSlow = 170;      // variable para almacenar valor de velocidad
int speedCar ;

// ---------- Servo
Servo myservoH;               // Define any servo name
int contador;
/* 
pines conectados
53 naranja
51 rojo
49 'amarillo
45 marron
*/ 

// ----------- definir led
int PinLED0 = 53; //naranja
int PinLED1 = 51; //rojo
int PinLED2 = 49; //amarillo
int PinLEDColor = 45;
int PinLEDColor1 = 32;
int PinLEDColor2 = 24;
int PinLEDColor3 = 26;

// ----------- Ultrasonico
// defines pins numbers 
const int trigPin = 28;
const int echoPin = 30;
// defines variables
long duration;
int distance;

void setup(){
  Serial.begin(38400);
  Serial1.begin(38400);

  // turn on motor
  // motor1.setSpeed(speedCarFast);
  // motor2.setSpeed(speedCarFast);
  motor3.setSpeed(speedCarFast);
  motor4.setSpeed(speedCarFast);

  //led  
  pinMode(PinLED0, OUTPUT);              
  pinMode(PinLED1, OUTPUT);
  pinMode(PinLED2, OUTPUT);
  pinMode(PinLEDColor, OUTPUT);
  pinMode(PinLEDColor1, OUTPUT);
  pinMode(PinLEDColor2, OUTPUT);
  pinMode(PinLEDColor3, OUTPUT);

  //Ultrasonico  
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  //Servos
   myservoH.attach (10);          // Define the servo signal pins
}

void loop(){
  // calcularDiatanciaMin();

    //------------Bluetooth
  if (Serial1.available()){     // si hay informacion disponible desde modulo
    char DATO = Serial1.read();   // almacena en DATO el caracter recibido desde modulo
    Serial.write(DATO);
    Serial.println('\r\n'); 
    
      if(DATO == '1') { MotorForward();}
      else if(DATO == '3') {MotorBackward();}
      else if(DATO == '4') {TurnLeft();}
      else if(DATO == '2') {TurnRight();}
      else if(DATO == '0') {MotorStop(); }  //motor stop
      
      else if(DATO == 'a') SetSpeedCarMax ();
      else if(DATO == 'b') SetSpeedCarUp();
      else if(DATO == 'c') SetSpeedCarDown();
      
      else if(DATO == 'd') {goLuces();}
      else if(DATO == 'e') {goLucesOff();}
      else if(DATO == 'f') {led_blink();}
    
      else if(DATO == 'h') { rotarCabeza_H_I(); }//rotar horizontal izquierda
      else if(DATO == 'i') { rotarCabeza_H_D(); } //rotar horizontal derecha
      else if(DATO == 'j') { rotarCabeza_H_90(); } //rotar horizontal derecha
      else if(DATO == 'k') { goLucesColor(); } 
      else if(DATO == 'l') { goLucesOffColor(); }
      else if(DATO == 'o') {goBaila();}

  }
  delay(50);
}
/*

void calcularDiatanciaMin(){
  
   long duration, distance; // start the scan
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;// convert the distance to centimeters.
  //if there's an obstacle 25 centimers, ahead, do the following: 
  if (distance < 300) {   
   Serial.println ("Close Obstacle detected!" );
    Serial.print ( distance);
     
    Serial.println (" The obstacle is declared a threat due to close distance. ");
    Serial.println (" Turning !");
    MotorStop();
        led_blink();

}
  else {
   Serial.println ("No obstacle detected. going forward");
    Serial.print ( distance);

   delay (15);
  }  

}
*/


int SetSpeedCarUp(){
  Serial.print("speedCar "+ speedCar);
  // motor1.setSpeed(speedCarMid);
  // motor2.setSpeed(speedCarMid);
  motor3.setSpeed(speedCarMid);
  motor4.setSpeed(speedCarMid);
  delay(90);  
}

int SetSpeedCarDown(){
  Serial.print("speedCar "+ speedCar);
  // motor1.setSpeed(speedCarSlow);
  // motor2.setSpeed(speedCarSlow);
  motor3.setSpeed(speedCarSlow);
  motor4.setSpeed(speedCarSlow);
  delay(90);  
}

int SetSpeedCarMax(){
  Serial.print("speedCar "+ speedCar);
  // motor1.setSpeed(speedCarFast);
  // motor2.setSpeed(speedCarFast);
  motor3.setSpeed(speedCarFast);
  motor4.setSpeed(speedCarFast);
  delay(90);  
}
// Funciones de motores
/* FORWARD */
void MotorForward(){
  // motor1.run(FORWARD);
  // motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

/* BACKWARD */
void MotorBackward(){
 //  motor1.run(BACKWARD);
  // motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  
}

/* TURN RIGHT */
void TurnRight(){
  // motor1.run(BACKWARD);
  // motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

/* TURN LEFT */
void TurnLeft(){
  // motor1.run(FORWARD);
 //  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void MotorStop(){
   Serial.write('STOP');
   Serial.println('\r\n'); 
  // motor1.run(RELEASE);
  // motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  //led_blinkColor();
}



// ** Motor End

void led_blinkColor(){
 int var = 0;
  while (var < 3) {
    digitalWrite(PinLEDColor,  HIGH);
    delay(50); 
    digitalWrite(PinLEDColor1, HIGH);
    delay(50);
    digitalWrite(PinLEDColor2,  HIGH);
    delay(50); 
    digitalWrite(PinLEDColor3,  HIGH);
    delay(50); 
    
    digitalWrite(PinLEDColor,  LOW);
    delay(50); 
    digitalWrite(PinLEDColor1, LOW);
    delay(50);
    digitalWrite(PinLEDColor2,  LOW);
    delay(50); 
    digitalWrite(PinLEDColor3,  LOW);
    delay(50); 
    var ++;
  }
}

void led_blink(){
 int var = 0;
  while (var < 3) {
    digitalWrite(PinLED0,  HIGH);
    delay(90); 
    digitalWrite(PinLED1, HIGH);
    delay(90);
    digitalWrite(PinLED2, HIGH);
    delay(90);
    led_blinkColor();

    digitalWrite(PinLED0,  LOW);
    delay(90); 
    digitalWrite(PinLED1, LOW);
    delay(90);
    digitalWrite(PinLED2, LOW);
    delay(90); 
    led_blinkColor();
    
    var ++;
  }
}


void goBaila(){
  SetSpeedCarMax();
  led_blink();  
  TurnRight();
  delay(170);
  
  led_blink();  
  TurnLeft();
  delay(170);

  led_blink();  
  TurnRight();
  delay(170);
  
  MotorStop();
}

void goLuces(){ 
  digitalWrite(PinLED0, HIGH);
  digitalWrite(PinLED1, HIGH);
  digitalWrite(PinLED2, HIGH);
}

void goLucesOff(){ 
  digitalWrite(PinLED0, LOW);
  digitalWrite(PinLED1, LOW);
  digitalWrite(PinLED2, LOW);
}

void goLucesColor(){ 
  digitalWrite(PinLEDColor, HIGH);
  digitalWrite(PinLEDColor1, HIGH);
  digitalWrite(PinLEDColor2, HIGH);
  digitalWrite(PinLEDColor3, HIGH);
}

void goLucesOffColor(){ 
  digitalWrite(PinLEDColor, LOW);
  digitalWrite(PinLEDColor1, LOW);
  digitalWrite(PinLEDColor2, LOW);
  digitalWrite(PinLEDColor3, LOW);
}

int rotarCabeza_H_I(){
  if(contador == 0){ contador = 90; }
  contador = contador + 25;               //Incrementa el contador
  delay (300);           // Retardo
  myservoH.write(contador); 
 }
 
void rotarCabeza_H_D(){ 
 if(contador == 0){ contador = 90;  }
 contador= contador - 25;               //Incrementa el contador
 delay (300);           // Retardo
 myservoH.write(contador);
}

void rotarCabeza_H_90(){ myservoH.write(90); }
