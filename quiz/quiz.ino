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
  Serial.println("Welcome");
  question("Which one is an animal?", "a) cat", "b) fly", "c) cute");
}

void loop ()  {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.println(incomingByte);

    if (currentQuestion == 1) {
      if (incomingByte == 'a') {
        Serial.println ("True!");
        correctAnswers++;
      }
      else if (incomingByte == 'b' || incomingByte == 'c') {
        Serial.println ("False!");
      }

      delay(1000);
      question("Whats the capital of UK?", "a. London", "b. ", "c. ");
    }

    if (currentQuestion == 2) {
      if (incomingByte == 'c' || incomingByte == 'b') {
        Serial.println ("False!");
      }
      else if (incomingByte == 'a') {
        Serial.println ("True!");
        correctAnswers++;
      }

      Serial.print(" You've answered  ");
      Serial.print(correctAnswers);
      Serial.println(" correct answers.");
    }

    currentQuestion++;

  }
}
