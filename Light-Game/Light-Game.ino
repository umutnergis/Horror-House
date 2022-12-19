#define first_Input A0
#define second_Input A1
#define third_Input A2
#define box_Input A3
#define led1_Relay 2
#define led2_Relay 3
#define led3_Relay 4
#define door_Relay 5
#define door2_Relay 6
#define game_Start 7
#define DEBUG
#define last_sit
bool situation1 = false;
int count = 0;
int readvalue1 = analogRead(A0);
int readvalue2 = analogRead(A1);
int readvalue3 = analogRead(A2);
int readvaluebox = analogRead(A3);
int gamevalue = digitalRead(7);
void run_Box();
void read_List();
void order_List();
//void piston_sit(bool situation);
void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif
  for(int i = 2; i <= 5; i++){
  pinMode(i,OUTPUT);
  }
  pinMode(7,INPUT);
  
}

void loop()
{ 
 
  Serial.println("13 pin " +String(digitalRead(7)));
  int condition = digitalRead(7);
  while(condition == 1){
  
  read_List();
  delay(500);
  order_List();
  run_Box();
  if(situation1 == true){
    break;}
  }
  

  delay(100);
}

void read_List()
{

  int readvalue1 = analogRead(A0);
  int readvalue2 = analogRead(A1);
  int readvalue3 = analogRead(A2);
#ifdef DEBUG
  Serial.println("A0 " + String(readvalue1) + " A1 " + String(readvalue2) + " A2 " + String(readvalue3));
#endif
}
void order_List()
{

  int readvalue1 = analogRead(A0);
  int readvalue2 = analogRead(A1);
  int readvalue3 = analogRead(A2);
  bool statement1 = (680 <= readvalue1 && readvalue1 <= 840);
  bool statement2 = (470 <= readvalue2 && readvalue2 <= 625);
  bool statement3 = (50 <= readvalue3 && readvalue3 <= 160);
  int num_array[3] = {0, 1, 2};
  int count = 0;
  if (statement1 && num_array[count] == 0)
  {
    digitalWrite(led1_Relay, HIGH);

#ifdef DEBUG
    Serial.println("Led 1 yandı" + String(num_array[count]));
#endif
    count++;
#ifdef DEBUG
    Serial.println("Led 2 yanması için hazır" + String(num_array[count]));
#endif
// while(!(statement2));
#ifdef DEBUG
    Serial.println("Led 2 için her şey hazır");
#endif
  }
  else
  {
    digitalWrite(led1_Relay, LOW);
  }
  if (statement2 && num_array[count] == 1)
  {
    digitalWrite(led2_Relay, HIGH);
#ifdef DEBUG
    Serial.println("Led 2 yandı");
#endif

    count++;
#ifdef DEBUG
    Serial.println("Led 3 yanması için hazır" + String(num_array[count]));
#endif
    // while(!(statement3));
    Serial.println("Led 3 için her şey hazır");
  }
  else
  {
    digitalWrite(led2_Relay, LOW);
  }
  if (statement3 && num_array[count] == 2)
  {
    digitalWrite(led3_Relay, HIGH);
    Serial.println("Led 3 yandı");
    digitalWrite(door_Relay, HIGH);
    Serial.println("PISTON ÇALIŞTI");
    delay(2000);
    digitalWrite(led3_Relay, LOW);
    digitalWrite(led2_Relay, LOW);
    digitalWrite(led1_Relay, LOW);
    digitalWrite(door_Relay, LOW);
    situation1 = true;
    while (readvalue1 < 900 || readvalue2 < 900 || readvalue3 < 900)
    {
      readvalue1 = analogRead(A0);
      readvalue2 = analogRead(A1);
      readvalue3 = analogRead(A2);
      Serial.println("A1: " + String(readvalue1) + " A2: " + String(readvalue2) + " A3 : " + String(readvalue3));
#ifdef DEBUG
      Serial.println("Loopa geri dönecek");
#endif
      
      delay(100);
    }
  }
  else
    digitalWrite(led3_Relay, LOW);
}

void run_Box()
{
  int readvaluebox = analogRead(A3);
  Serial.println("VALUE BOX " + String(readvaluebox));
  if (readvaluebox > 1000)
  {
    piston_sit(true);
  }
  else
  {
    piston_sit(false);
  }
}
void piston_sit(bool situation)
{
  if (situation)
  {
    digitalWrite(door2_Relay, HIGH);
    delay(2000);
    digitalWrite(door2_Relay, LOW);
  }

  else
  {
    digitalWrite(door2_Relay, LOW);
  }
}
