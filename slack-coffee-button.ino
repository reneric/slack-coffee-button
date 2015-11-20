// Output pins
const int redLed = D2;
const int greenLed = D1;
const int boardLed = D7;
const int pushButton = A0;
const int vibrator = D6;
const int power = A5;

// Fresh coffee period in minutes
int freshCoffeeDelay = 60;


int freshCoffeeDelayMillis = freshCoffeeDelay * 60 * 1000;
unsigned long coffeeTimer = 0;
int coffeeTimerStarted = 0;


void setup() {
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(boardLed, OUTPUT);
    pinMode(vibrator, OUTPUT);
    pinMode(power, OUTPUT);
    pinMode(pushButton, INPUT);
    digitalWrite(power, HIGH);
}

void loop() {
    int buttonPushed = digitalRead(pushButton);

    if (buttonPushed == LOW) {
        coffeeTimer = millis();
        coffeeTimerStarted = 1;
        digitalWrite(boardLed, LOW);
        digitalWrite(greenLed, HIGH);
        digitalWrite(redLed, LOW);
        vibrate();
        Particle.publish("lmslack");
        blinkGreen();
    }
    else {
        if (coffeeTimerStarted == 1) {
            if (millis() - coffeeTimer < freshCoffeeDelayMillis) {
                coffeeIsFresh();
            } else {
                coffeeTimerStarted = 0;
            }
        } else {
            coffeeIsStale();
        }
    }
}

void coffeeIsFresh() {
    digitalWrite(boardLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
}

void coffeeIsStale() {
    digitalWrite(boardLed, LOW);
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
}

void blinkRed() {
    for(int i=0;i<3;i++){
        digitalWrite(redLed, HIGH);
        digitalWrite(vibrator, HIGH);
        delay(200);
        digitalWrite(redLed, LOW);
        digitalWrite(vibrator, LOW);
        delay(200);
    }
}

void blinkGreen() {
    for(int i=0;i<3;i++){
        digitalWrite(greenLed, HIGH);
        digitalWrite(vibrator, HIGH);
        delay(200);
        digitalWrite(greenLed, LOW);
        digitalWrite(vibrator, LOW);
        delay(200);
    }
}

void vibrate() {
    digitalWrite(vibrator, HIGH);
    delay(200);
    digitalWrite(vibrator, LOW);
    delay(1500);
}





