#include <Servo.h>

Servo myservo;

char incomingByte;
int currentQuestion = 1;
int correctAnswers = 0;

void question(String question, String answer1, String answer2, String answer3) {
  Serial.println(question);
  Serial.println(answer1);
  Serial.println(answer2);
  Serial.println(answer3);
}

void setup () {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(9);

  Serial.println("Welcome");
  question("Which of the answers describes something you can’t do to conserve energy?", "a. Close the curtain when you leave the room", "b. Turn down the heat in your house and wear a sweater instead", "c. Walk or ride your bike instead of driving");
}

char answer;

void joystick() {
  int VA0 = analogRead(A0);
  int i = 0;

  while (i < 300) {
    VA0 = analogRead(A0);
    int pos = VA0 / 6;
    myservo.write(pos);
    delay(25);
    i++;
  }

//  Serial.println(VA0);

  if (VA0 < 341) {
    answer = 'a';
  }
  else if ((340 < VA0) && (VA0 < 682)) {
    answer = 'b';
  }
  else if (681 < VA0 < 1025) {
    answer = 'c';
  }
  Serial.println(answer);
  
}

void loop ()  {

  joystick();

  //if (Serial.available() > 0) {
  // incomingByte = Serial.read();
  //Serial.println(incomingByte);

  if (currentQuestion == 1) {
    if (answer == 'a') {
      Serial.println ("True!");
      correctAnswers++;
    }
    else if (answer == 'b' || answer == 'c') {
      Serial.println ("False!");
    }

    delay(1000);
    question("Which appliance spends more energy?", "a. TV", "b. Fridge", "c. Air conditioner");
  }

  if (currentQuestion == 2) {
    if (answer == 'c') {
      Serial.println ("True!");
      correctAnswers++;
    }
    else if (answer == 'b' || answer == 'a') {
      Serial.println ("False!");
    }

    delay(1000);
    question("What advice helps us save electrical energy?", "a. Leave the TV on", "b. Use energy-saving bulbs", "c. Leave the appliances plugged in at night");
  }

  if (currentQuestion == 3) {
    if (answer == 'b') {
      Serial.println ("True!");
      correctAnswers++;
    }
    else if (answer == 'c' || answer == 'a') {
      Serial.println ("False!");
    }


    delay(1000);
    question("When is the world water day?", "a. May 8", "b. July 28", "c. March 22");
  }

  if (currentQuestion == 4) {
    if (answer == 'c') {
      Serial.println ("True!");
      correctAnswers++;
    }
    else if (answer == 'b' || answer == 'a') {
      Serial.println ("False!");
    }

    delay(1000);
    question("What is done in “the time of the planet”?", "a. We turn off all possible artifacts for one hour", "b. We save water", "c. We talk about electric power");
  }

  if (currentQuestion == 5) {
    if (answer == 'a') {
      Serial.println ("True!");
      correctAnswers++;
    }
    else if (answer == 'b' || answer == 'c') {
      Serial.println ("False!");
    }


    Serial.print(" You've answered  ");
    Serial.print(correctAnswers);
    Serial.println(" correct answers.");
  }

  currentQuestion++;

//}
}
