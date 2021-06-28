#define BOXSIZE 10 //box size (cm)
#define TRIG 9 //ultra - sending 
#define ECHO 8 //ultra - receiving 
#define BUZZ 4 //buzzer
#define DOOR 2 //magnetic door sensor   

int doorSensor = 0; 

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(DOOR, INPUT_PULLUP);
  Serial.begin(9600); 
  
}

void loop() {
  //check the status of door 
  doorSensor = digitalRead(DOOR); 
  if(doorSensor!=LOW){ //door is opened

    //check the box 
    float duration, distance;
    digitalWrite(TRIG, HIGH); 
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW); 
    duration = pulseIn(ECHO, HIGH); 
    distance = ((float)(340 * duration) / 10000) / 2; 
    boolean hasSth = distance < BOXSIZE; 
   
    while(hasSth){ //sth in the box 
      doorSensor = digitalRead(DOOR);
       if (doorSensor == LOW) { // stops when door is closed
        hasSth = false;
        break;
      }

      //ring the buzzer
      tone(BUZZ, 500, 100);
      delay(1000); 

      //check the box again 
      digitalWrite(TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG, LOW); 
      duration = pulseIn(ECHO, HIGH);
      distance = ((float)(340 * duration) / 10000) / 2; 
      hasSth = distance < BOXSIZE;
      delay(2); 
    }
  }
}
