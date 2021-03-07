#include <Servo.h>


Servo myservo;

void setup() {
  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  myservo.attach(9);

}

void loop() {
  int VA0 = analogRead(A0);
  char answer;
  int i = 0;
  

  if(VA0 < 341){
    answer = 'a';
  }
  else if((340 < VA0) && (VA0 < 682)){
    answer = 'b';
  }
  else if(681 < VA0 < 1025){
    answer = 'c';
  }

  Serial.println(answer);
  Serial.write(answer);
  
while(i < 200){
    int VA0 = analogRead(A0);
  int pos = VA0/6;
  myservo.write(pos);
    delay(25);
    i++;
  }

  
  
}

void angle(){
  int VA0 = analogRead(A0);
  int pos = VA0/6;
  myservo.write(pos);
}
