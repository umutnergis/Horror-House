#include <Arduino.h>
#include <SPI.h>
#include <RFID.h>
#define role 8
#define resetpin 10
#define DEBUG




String okunmasiGerekenkart1 = "218112224128202"; // kırmızı
String okunmasiGerekenkart2 = "1056746195199"; // siyah
String okunmasiGerekenkart3 = "1056746195199"; // sarı


RFID kart1(2, 9);
RFID kart2(3, 9);
RFID kart3(4, 9);

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  kart1.init();
  kart2.init();
  kart3.init();
  digitalWrite(resetpin,HIGH);
  pinMode(role, OUTPUT);
  pinMode(resetpin,OUTPUT);
  digitalWrite(role, HIGH);
#ifdef DEBUG
  Serial.println("basladi");
#endif
}

void loop()
{

  if (kart1.isCard() || kart2.isCard() || kart3.isCard())
  {
    if (kart1.readCardSerial() || kart2.readCardSerial() || kart3.readCardSerial())
    {
      #ifdef DEBUG
        Serial.println("okudu");
      #endif
      String card1 = "";
      String card2 = "";
      String card3 = "";
      for (byte i = 0; i < 5; i++)
      {
        card1 += String(kart1.serNum[i]);
      }
      for (byte i = 0; i < 5; i++)
      {
        card2 += String(kart2.serNum[i]);
      }
      for (byte i = 0; i < 5; i++)
      {
        card3 += String(kart3.serNum[i]);
      }

#ifdef DEBUG
      Serial.println("Uc kartta kart buldu ve okudu. Card1: " + card1 + "   Card2: " + card2 + " Card3: " + card3);
#endif
      if (((card3 == okunmasiGerekenkart3) && (card1 == okunmasiGerekenkart1) && (card2 == okunmasiGerekenkart2)))
      {
        digitalWrite(role, LOW);
        delay(5000);
        digitalWrite(resetpin,LOW);
#ifdef DEBUG
        Serial.println("Sifre cozuldu");
#endif
      }
      //else
      //{
        //digitalWrite(role, HIGH);
      //}
      
    }
    //else
    //{
      //digitalWrite(role, HIGH);
    //}
    
  }
  //else {
  //digitalWrite(role, HIGH);
  //}
  kart1.halt();
  kart2.halt();
  kart3.halt();
}
