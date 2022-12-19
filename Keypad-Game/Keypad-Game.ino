
#include <Keypad.h>
#define ROLE 2
#define BUZZER 3
#define LEN 7


/*
T -> Tamamlanırsa
K -> Tuş girilirse
F -> Tuş yanlış girilirse
*/

const char enter = '3';
const char keys[LEN] = {'B', '6', 'C', '#', '5', 'D','3'};
char fill_keys[LEN] = {};
long last_add = 0;

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns
// define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {11, 10, 9, 8}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4};   // connect to the column pinouts of the keypad

// initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(9600);
  pinMode(ROLE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop()
{
  char customKey = customKeypad.getKey();
  if (customKey)
  {
    addOrder(customKey);
    Serial.println(customKey);
    if (checkOrder())
    {
      Serial.println("f");
      openDoor();
    } else {
      if (customKey == enter) {
        
        buzz('F');
      }
    }
  }
}

void openDoor() {
  digitalWrite(ROLE, HIGH);
  buzz('T');
  digitalWrite(ROLE, LOW);
  clearOrder();
  
}

void clearOrder() {
for (size_t i = 0; i < LEN; i++)
    {
      fill_keys[i] = '0';
    }
}

void addOrder(char key)
{
  buzz('K');
  if (!((millis() - last_add) < 3000))
  {
    clearOrder();
  }
  for (int i = 0; i < LEN - 1; i++)
  {
    fill_keys[i] = fill_keys[i + 1];
  }
  fill_keys[LEN - 1] = key;
  last_add = millis();
}

bool checkOrder()
{
  for (int i = 0; i < LEN; i++)
  {
    if (fill_keys[i] != keys[i])
    {
      return false;
    }
  }
  return true;
}

void buzz(char state)
{
  if (state == 'T')
  {
    analogWrite(BUZZER, 90);
    delay(1000);
    digitalWrite(BUZZER, LOW);
  }
  else if (state == 'F')
  {
    for (size_t i = 0; i < 5; i++)
    {
      analogWrite(BUZZER, 100);
      delay(70);
      analogWrite(BUZZER, 0);
      delay(70);
    }
  }
  else if (state == 'K')
  {
    analogWrite(BUZZER, 90);
    delay(100);
    digitalWrite(BUZZER, LOW);
  }
}
