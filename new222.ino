#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
#define LED_PIN A0 
#define LED_PIN A1
#define LED_PIN A2

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  Serial.println("I am waiting for card...");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }

  strID.toUpperCase();
  Serial.print("Tap card key: ");
  Serial.println(strID);
  delay(1000);

  if (strID.indexOf("D9:CF:D0:56") >= 0) {  //put your own tap card key;
    Serial.println("********************");
    Serial.println("**Authorised access**");
    Serial.println("********************");
    digitalWrite(A0, HIGH);// A0= green
    digitalWrite(A1, LOW);  // A1= red 
    digitalWrite(A2, LOW); // A2 = orange
   
    delay (8000);// During this delay we can let the ambulance go from traffic intersection
   
    digitalWrite(A1, HIGH);// A1= red
     digitalWrite(A0, LOW);  // A0 = green
    digitalWrite(A2, LOW);// A2 = orange
   
    delay(6000);
    
    digitalWrite(A2, HIGH);//A2 = orange
    digitalWrite(A0, LOW);// A0 = green
    digitalWrite(A1, LOW);// A1= red
delay(6000);
digitalWrite(A0, HIGH);// A0= green
    digitalWrite(A1, LOW);  // A1= red 
    digitalWrite(A2, LOW); // A2 = orange
   delay(6000);
 digitalWrite(A2, LOW);//A2 = orange
    digitalWrite(A0, LOW);// A0 = green
    digitalWrite(A1, LOW);// A1= red

   
    delay(6000);
    
    return;
  }
  else {
    Serial.println("****************");
    Serial.println("**Unauthorized Access**");
    Serial.println("****************");
    digitalWrite(A1, HIGH);// A1= red
    digitalWrite(A0, LOW);//A0 = green
    digitalWrite(A2, LOW);  //A2 = orange
    delay (8000);
    digitalWrite(A1, LOW);   // A1= red
    digitalWrite(A2, HIGH);  //A2 = orange
    digitalWrite(A0, LOW);  // A0 = green
    delay(6000);
    
    digitalWrite(A0, HIGH);  //A0 = green
    digitalWrite(A1, LOW);   // A1= red
    digitalWrite(A2, LOW);  //A2 = orange
    delay(6000);

    digitalWrite(A2, LOW);//A2 = orange
    digitalWrite(A0, LOW);// A0 = green
    digitalWrite(A1, LOW);// A1= red

    delay(6000);
 
    
    return;
  }
  
}
