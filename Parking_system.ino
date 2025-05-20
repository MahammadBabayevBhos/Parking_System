#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 rfid(SS_PIN, RST_PIN);


byte allowedCards[][4] = {
  {240, 140, 54, 249},
  {123, 45, 67, 89},    
};

const int numAllowedCards = sizeof(allowedCards) / sizeof(allowedCards[0]);

void setup() {
  Serial.begin(9600);
  SPI.begin();  
  rfid.PCD_Init();
  Serial.println("RFID sistemi hazirdir.");
}

void loop() {
 
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  Serial.print("ID Numune: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i]);
    Serial.print(" ");
  }
  Serial.println();

  if (isAuthorized(rfid.uid.uidByte)) {
    Serial.println("Giris icazesi verildi.");
  } else {
    Serial.println("Unauthorized Card");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

bool isAuthorized(byte *uid) {
  for (int i = 0; i < numAllowedCards; i++) {
    bool match = true;
    for (int j = 0; j < 4; j++) {
      if (uid[j] != allowedCards[i][j]) {
        match = false;
        break;
      }
    }
    if (match) return true;
  }
  return false;
}
