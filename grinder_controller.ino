#define MOTOR 1
#define BUTTON 2
#define DURATION 5000  // The duration of the grind in ms - to be ruled out in next version

unsigned long start, pause;
void setup() {
  pinMode(MOTOR, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  while(digitalRead(BUTTON) == LOW);

  start = millis();

  while(1) {
    digitalWrite(MOTOR, HIGH);

    if(digitalRead(BUTTON) == LOW) {
      pause = millis() - start;
      digitalWrite(MOTOR, LOW);
      while(digitalRead(BUTTON) == LOW);
      start = millis() - pause;
    }
    else if(millis() - start > DURATION) {
      digitalWrite(MOTOR, LOW);
      while(digitalRead(BUTTON) == HIGH);
      break;
    }
  }
}
