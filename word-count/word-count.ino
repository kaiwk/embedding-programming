#define NONE 0
#define SHORT 1
#define LONG 2

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

int btn_state = LOW;
int press_type = NONE;
int during_t = 0, down_t = 0;
int word_count = 0;

void detectKey() {
  btn_state = digitalRead(buttonPin);

  if (btn_state == LOW) {
    down_t = millis();
    digitalWrite(ledPin, HIGH);
  } else {
    during_t = millis() - down_t;
    if (during_t < 10) {
      press_type = NONE;
    } else if (during_t > 500) {
      press_type = LONG;
      Serial.println("long press");
    } else {
      press_type = SHORT;
      Serial.println("short press");
    }
    digitalWrite(ledPin, LOW);
  }

  if (press_type == LONG) {
    ++word_count;
  }

  Serial.print("word count: ");
  Serial.println(word_count);

  press_type = NONE;
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), detectKey, CHANGE);
}

void loop() {
}
