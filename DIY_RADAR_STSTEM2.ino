#include <Servo.h>

Servo servo;
const int trigPin = 8;
const int echoPin = 9;
const int servoPin = 10;

long duration;
int distance;
const int threshold = 100; // Max detection range in cm

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  sweep(0, 180, 2);   // Sweep left to right
  sweep(180, 0, -2);  // Sweep right to left
}

void sweep(int startAngle, int endAngle, int step) {
  for (int angle = startAngle; angle != endAngle + step; angle += step) {
    servo.write(angle);
    delay(60);  // Allow servo to reach position

    // Trigger ultrasonic pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read echo response
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    if (distance > 2 && distance < threshold) {
      Serial.print(angle);
      Serial.print(",");
      Serial.println(distance);
    }
  }
}
