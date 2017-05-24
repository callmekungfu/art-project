#define PIR 2
#define SUCK 13
#define BLOW 10
#define SUCK_D 1000 // 10 SECONDS
#define BLOW_D 500 // 5 SECONDS

int pos = 0;
boolean finish_blow = false;
boolean finish_suck = false;

void setup() {
  Serial.begin (9600);
  pinMode(SUCK, OUTPUT);
  pinMode(BLOW, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  boolean motion = scanPosition();
  //if object appeared for more than 1 second, activate the sucker
  if(motion && !finish_suck){
    // reset position flag
    pos = 0;
    int c = 10;
    int ss = SUCK_D/c;
    int bs = BLOW_D/c;
    Serial.println("sucking");
    for(int i = 0; i < ss; i++){
      digitalWrite(SUCK, HIGH);
      delay(c);  
    }
    finish_blow = false;
    Serial.println("sucking stopped");
    digitalWrite(SUCK, LOW);
    finish_suck = true;
  }
  
  if(motion && !finish_blow){
    pos = 0;
    int c = 10;
    int bs = BLOW_D/c;
    Serial.println("blowing");
    for(int i = 0; i < bs; i++){
      digitalWrite(BLOW, HIGH);
      delay(c);  
    }
    finish_suck = false;
    Serial.println("blowing stopped");
    digitalWrite(BLOW, LOW);
    finish_blow = true;  
    motion = false;
  }
  //evecute the code on a two second clock
  delay(2000);
}

boolean scanPosition(){
  int pirVal = digitalRead(PIR);
  if(pirVal == LOW){
    Serial.println("motion detected");
    return true;
  }
  return false;
}
