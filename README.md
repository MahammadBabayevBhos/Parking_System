# Parking_System
#include <SPI.h>                          
#include <MFRC522.h>                      
#include <Servo.h>                        

int RST_PIN = 9;                          
int SS_PIN = 10;
int servoPin = 8;                         

Servo motor;                              
MFRC522 parking(SS_PIN, RST_PIN);            
byte ID[4] = {0, 0, 0, 0};          
void setup() { 
  motor.attach(servoPin);                 
  Serial.begin(9600);                     
  SPI.begin();                            
  parking.PCD_Init();                        
}
 
void loop() {

  if ( ! parking.PICC_IsNewCardPresent())    
    return;

  if ( ! parking.PICC_ReadCardSerial())
    return;

  if (parking.uid.uidByte[0] == ID[0] && parking.uid.uidByte[1] == ID[1] && parking.uid.uidByte[2] == ID[2] && parking.uid.uidByte[3] == ID[3] ){
    Serial.println("PLS ENTER");
    IdModifier();
    motor.write(0);                 
    delay(15000);
  }
  else{                                 
    Serial.println("Unauthorized Card");
    IdModifier();
  }
  parking.PICC_HaltA();
}
void IdModifier(){
  Serial.print("ID Number: ");
  for(int i = 0; i < 4; i++){
    Serial.print(parking.uid.uidByte[i]);
    Serial.print(" ");
  }
  Serial.println("");
}
