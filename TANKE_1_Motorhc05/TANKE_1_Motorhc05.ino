
/* include library */
#include <Servo.h>           // Add Servo library
#include <SoftwareSerial.h> // libreria que permite establecer pines digitales

SoftwareSerial miBT(19, 18);   // pin 19 como RX, pin 18 como TX

// ----------- Puenteh

int ENA = 42;      // ENA de L298N a pin digital 5
int ENB = 52;      // ENb de L298N a pin digital 5
//derecho
int IN1 = 44;      // IN1 de L298N a pin digital 2
int IN2 = 46;      // IN2 de L298N a pin digital 3
//izquierdo
int IN3 = 48;      // IN2 de L298N a pin digital 2
int IN4 = 50;      // IN3 de L298N a pin digital 3

int speedCar = 256;      // variable para almacenar valor de velocidad
int speedMAX = 256;      // variable para almacenar valor de velocidad
int speedMED = 170;      // variable para almacenar valor de velocidad
int speedMIN = 130;      // variable para almacenar valor de velocidad
int speedOff = 0 ;

void setup(){
  
  Serial.begin(38400);
  Serial1.begin(38400);
  
  pinMode(IN1, OUTPUT);   // IN1 como salida  
  pinMode(IN2, OUTPUT);   // IN2 como salida
  pinMode(ENA, OUTPUT);   // ENA como salida
  pinMode(IN3, OUTPUT);   // IN3 como salida
  pinMode(IN4, OUTPUT);   // IN4 como salida
  pinMode(ENB, OUTPUT);   // ENB como salida

}

void loop(){

    //------------Bluetooth
  if (Serial1.available()){     // si hay informacion disponible desde modulo
    char DATO = Serial1.read();   // almacena en DATO el caracter recibido desde modulo
    Serial.write(DATO);
    Serial.println('\r\n'); 
     Serial.println("dato" + DATO);

    
      if(DATO == '1') { MotorForward();}
      else if(DATO == '3') {MotorBackward();}
      else if(DATO == '4') {TurnLeft();}
      else if(DATO == '2') {TurnRight();}
      else if(DATO == '0') {MotorStop(); }
      
      else if(DATO == '6') SetSpeedCarMAX() ; 
      else if(DATO == '7') SetSpeedCarMED();   
      else if(DATO == '8') SetSpeedCarMIN();  
 
  }
  delay(50);
  
}



// Funciones de motores
/* FORWARD */
void MotorForward(){
  Serial.println(speedCar);

  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB

  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW); 
  digitalWrite(IN4,HIGH);
}

/* BACKWARD */
void MotorBackward(){
    Serial.println(speedCar);

  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB
  
  digitalWrite(IN1,LOW);  
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
/* TURN RIGHT */
void TurnRight(){
    Serial.println(speedCar);

  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
   analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB
  
  digitalWrite(IN1, LOW); // IN1 a cero logico
  digitalWrite(IN2, HIGH);  // IN2 a uno logico
  digitalWrite(IN3, LOW); // IN3 a cero logico
  digitalWrite(IN4, HIGH);  // IN4 a uno logico
}

/* TURN LEFT */
void TurnLeft(){
   Serial.println(speedCar);

   analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
   analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB

  digitalWrite(IN1, HIGH); // IN1 a cero logico
  digitalWrite(IN2, LOW);  // IN2 a uno logico
  digitalWrite(IN3, HIGH); // IN3 a cero logico
  digitalWrite(IN4, LOW);  // IN4 a uno logicologico
}

void MotorStop(){   
  analogWrite(ENA, speedOff);    // deshabilita motor A
  analogWrite(ENB, speedOff);    // deshabilita motor B
}

//  -----------------------  SPEED  -----------------------
int SetSpeedCarMAX(){
  speedCar = speedMAX;
    Serial.print("speedCar "+ speedCar);

  delay(90);  
}


int SetSpeedCarMED(){
  speedCar = speedMED;
    Serial.print("speedCar "+ speedCar);

  delay(90);  
}


int SetSpeedCarMIN(){
  speedCar = speedMIN;
  
  delay(90);  
}
