#include <Servo.h>

Servo servo;

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

// Motor pins
const int leftMotor1  = 2;
const int leftMotor2  = 3;
const int rightMotor1 = 4;
const int rightMotor2 = 5;

long duration;
int distance;

int getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0)
    return 400;

  return duration * 0.034 / 2;
}

void forward()
{
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}

void stopCar()
{
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}

void turnLeft()
{
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}

void turnRight()
{
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
}

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);

  servo.attach(servoPin);
  servo.write(90);

  Serial.begin(9600);
}

void loop()
{
  int frontDistance = getDistance();

  if (frontDistance > 20)
  {
    forward();
  }
  else
  {
    stopCar();
    delay(300);

    // Scan left
    servo.write(150);
    delay(500);
    int leftDistance = getDistance();

    // Scan right
    servo.write(30);
    delay(500);
    int rightDistance = getDistance();

    // Center
    servo.write(90);
    delay(300);

    if (leftDistance > rightDistance)
    {
      turnLeft();
      delay(600);
    }
    else
    {
      turnRight();
      delay(600);
    }

    stopCar();
    delay(200);
  }
}
