#define first_in A0
#define second_in A1
#define third_in A2
#define fourth_in A3
#define DEBUG
#define relay 4
bool check_values();
void read_values();
void relay_system();
void setup() {
  pinMode(first_in,INPUT);
  pinMode(second_in,INPUT);
  pinMode(third_in,INPUT);
  pinMode(fourth_in,INPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW);
  
  #ifdef DEBUG
  Serial.begin(9600);
  #endif

}

void loop() {
  float first_varible= analogRead(A0)*(5.0/1023.0);
  float second_varible= analogRead(A1)*(5.0/1023.0);
  float third_varible= analogRead(A2)*(5.0/1023.0);
  float fourth_varible= analogRead(A3)*(5.0/1023.0);
  digitalWrite(relay,LOW); 
  read_values();
  check_values();
  while((first_varible >4 && second_varible >4 && third_varible >4 && fourth_varible >4));
   

}


void read_values(){
  
  float first_varible= analogRead(A0)*(5.0/1023.0);
  float second_varible= analogRead(A1)*(5.0/1023.0);
  float third_varible= analogRead(A2)*(5.0/1023.0);
  float fourth_varible= analogRead(A3)*(5.0/1023.0);

  Serial.println("A0: " + String(first_varible) + " A1: " + String(second_varible) + " A2: " + String(third_varible) + " A3: " + String(fourth_varible));  
  
  }

bool check_values(){
  float first_varible= analogRead(A0)*(5.0/1023.0);
  float second_varible= analogRead(A1)*(5.0/1023.0);
  float third_varible= analogRead(A2)*(5.0/1023.0);
  float fourth_varible= analogRead(A3)*(5.0/1023.0);
  if(first_varible <= 3.40 && first_varible >= 3.30 && second_varible >= 4.90 && second_varible <= 5.10 && third_varible <= 5.10 && third_varible >= 4.90 && fourth_varible >= 0 && fourth_varible <=0.2 ){
    relay_system();
    
    }
   else{
    return false;
    }
  
  }

void relay_system(){
  #ifdef DEBUG
  Serial.println("Relay on");
  #endif
  digitalWrite(relay,HIGH);
  delay(3000);
  digitalWrite(relay,LOW);
  
  
  }
