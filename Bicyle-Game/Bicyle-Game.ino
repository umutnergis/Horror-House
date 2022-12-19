  #include <Arduino.h>
  #define DEBUG
  #define voltage_source A1
  #define first_number 2
  #define second_number 3
  #define third_number 4
  #define fourth_number 5
  #define CLOSE_TIME 1000

  int voltage;
  int num;
  unsigned long old_time = 0;
  unsigned long new_time;

  unsigned long wrong_time = 0;
  unsigned long correct_time = 0;

  bool first_open = false;
  bool second_open = false;
  bool third_open = false;
  bool fourth_open = false;

  void setup()
  {
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
    pinMode(first_number, OUTPUT);
    pinMode(second_number, OUTPUT);
    pinMode(third_number, OUTPUT);
    pinMode(fourth_number, OUTPUT);
  }

  void loop()
  {

    old_time = new_time;
    while (true)
    {
      delay(100);
      voltage = analogRead(voltage_source);
      new_time = millis();
  #ifdef DEBUG
      Serial.println("NEW-TİME " + String(new_time) + " difference " + String(new_time - old_time));
  #endif
      if (new_time - old_time >= 15000 && (new_time - correct_time < 1000))
      {
        Serial.println("BREAK");

        unsigned long diff = new_time - old_time;
        first_open = diff > 15000 && diff < 20000;
        second_open = diff > 20000 && diff < 25000;
        third_open = diff > 25000 && diff < 30000;
        fourth_open = diff > 30000;

        if (first_open)
        {
          digitalWrite(first_number, HIGH);
          Serial.println("first open");
        }
        else if (second_open)
        {
          digitalWrite(second_number, HIGH);
          Serial.println("first second open");
        }
        else if (third_open)
        {
          digitalWrite(third_number, HIGH);
          Serial.println("first second third open");
        }
        else if (fourth_open)
        {
          digitalWrite(fourth_number, HIGH);
          Serial.println("first second third fourth open");
        }
      }

      if (voltage >= 400)
      {
        correct_time = millis();
  #ifdef DEBUG
        Serial.println("CORRECT TIME " + String(correct_time));
  #endif
      }
      else
      {
        wrong_time = millis();
  #ifdef DEBUG
        Serial.println("WRONG TIME " + String(wrong_time));
  #endif
      }

      if (correct_time < wrong_time)
      {
        if ((new_time - correct_time) > 1000)
        {
          old_time = new_time;
          // correct_time = millis();
          // wrong_time = millis();
          close_lights();
        }
      }
    }
  }

  void close_lights()
  {
    Serial.println("Lights closed");
    if (fourth_open)
    {
      digitalWrite(fourth_number, HIGH);
      delay(CLOSE_TIME);
      digitalWrite(third_number, LOW);
      delay(CLOSE_TIME);
      digitalWrite(second_number, LOW);
      delay(CLOSE_TIME);
      digitalWrite(first_number, LOW);
    }
    else if (third_open)
    {
      digitalWrite(third_number, HIGH);
      delay(CLOSE_TIME);
      digitalWrite(second_number, LOW);
      delay(CLOSE_TIME);
      digitalWrite(first_number, LOW);
    }
    else if (second_open)
    {
      digitalWrite(second_number, HIGH);
      delay(CLOSE_TIME);
      digitalWrite(first_number, LOW);
    }
    else if (first_open)
    {
      digitalWrite(first_number, HIGH);
    }
    fourth_open = false;
    third_open = false;
    second_open = false;
    first_open = false;
  }
