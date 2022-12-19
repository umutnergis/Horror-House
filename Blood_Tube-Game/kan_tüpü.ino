#define DEBUG
#define sensor1 2
#define sensor2 3
#define sensor3 4
#define sensor4 5
#define sensor5 6
#define sensor6 7
#define sensor7 8
#define sensor8 9
#define sensor9 10
#define sensor10 11
#define relay 12

void setup()
{
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(sensor3, INPUT);
    pinMode(sensor4, INPUT);
    pinMode(sensor5, INPUT);
    pinMode(sensor6, INPUT);
    pinMode(sensor7, INPUT);
    pinMode(sensor8, INPUT);
    pinMode(sensor9, INPUT);
    pinMode(sensor10, INPUT);
    pinMode(relay, OUTPUT);
#ifdef DEBUG
    Serial.begin(9600);
#endif
}

void loop()
{

    bool situation = ((digitalRead(sensor1) == 0) && (digitalRead(sensor2) == 0) && (digitalRead(sensor3) == 0) && (digitalRead(sensor4) == 0) &&
                      (digitalRead(sensor5) == 0) && (digitalRead(sensor6) == 0) && (digitalRead(sensor7) == 0) && (digitalRead(sensor8) == 0) && (digitalRead(sensor9) == 0) && (digitalRead(10) == 0));
#ifdef DEBUG
    Serial.println(" S1: " + String(digitalRead(sensor1)) + " S2: " + String(digitalRead(sensor2)) + " S3: " + String(digitalRead(sensor3)) + " S4: " + String(digitalRead(sensor4)) + " S5: " + String(digitalRead(sensor5)) + " S6: " + String(digitalRead(sensor6)) + " S7: " + String(digitalRead(sensor7)) + " S8: " + String(digitalRead(sensor8)) + " S9: " + String(digitalRead(sensor9)) + " S10: " + String(digitalRead(sensor10)));
#endif
    int sensor1value = digitalRead(sensor1);
    int sensor2value = digitalRead(sensor2);
    int sensor3value = digitalRead(sensor3);
    int sensor4value = digitalRead(sensor4);
    int sensor5value = digitalRead(sensor5);
    int sensor6value = digitalRead(sensor6);
    int sensor7value = digitalRead(sensor7);
    int sensor8value = digitalRead(sensor8);
    int sensor9value = digitalRead(sensor9);
    int sensor10value = digitalRead(sensor10);
    if (situation)
    {
        digitalWrite(relay, HIGH);
        Serial.println("Röle HIGH");
        delay(2000);
        digitalWrite(relay, LOW);
        Serial.println("Röle low");
        while ((sensor1value == 0) && (sensor2value == 0) && (sensor3value == 0) && (sensor4value == 0) && (sensor5value == 0) && (sensor6value == 0) && (sensor7value == 0) && (sensor8value == 0) && (sensor9value == 0) && (sensor10value == 0))
        {
            sensor1value = digitalRead(sensor1);
            sensor2value = digitalRead(sensor2);
            sensor3value = digitalRead(sensor3);
            sensor4value = digitalRead(sensor4);
            sensor5value = digitalRead(sensor5);
            sensor6value = digitalRead(sensor6);
            sensor7value = digitalRead(sensor7);
            sensor8value = digitalRead(sensor8);
            sensor9value = digitalRead(sensor9);
            sensor10value = digitalRead(sensor10);
            
        }
    }
    else
    {
        digitalWrite(relay, LOW);
        Serial.println("Low ");
    }
    delay(200);
}