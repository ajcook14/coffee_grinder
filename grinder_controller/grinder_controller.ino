#define BUTTON1 2    /* basket touch sensor */
#define BUTTON2 12   /* decrement duration */
#define BUTTON3 13   /* increment duration */
#define MOTOR 5

unsigned duration = 5000; /* duration of the grind in ms */
unsigned long start, pause;
struct {
  unsigned first:1;  /* the first increment or decrement */
} flags;

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
}

void loop() {
  while (digitalRead(BUTTON1) == LOW) {
    for (flags.first = 1; (digitalRead(BUTTON3) == HIGH) && (duration <= 65250);) {
      duration += 250;
      Serial.println(duration);
      delay(100);
      if (flags.first) {
        delay(400);
        flags.first = 0;
      }
    }
    for (flags.first = 1; (digitalRead(BUTTON2) == HIGH) && (duration >= 250);) {
      duration -= 250;
      Serial.println(duration);
      delay(100);
      if (flags.first) {
        delay(400);
        flags.first = 0;
      }
    }
  }

  start = millis();

  for (;;) {
    digitalWrite(MOTOR, HIGH);

    if (digitalRead(BUTTON1) == LOW) {
      pause = millis() - start;
      digitalWrite(MOTOR, LOW);
      while (digitalRead(BUTTON1) == LOW);
      start = millis() - pause;
    }
    else if (millis() - start > duration) {
      digitalWrite(MOTOR, LOW);
      while (digitalRead(BUTTON1) == HIGH);
      delay(100);
      break;
    }
  }
}
