#define ECHO_LEFT 12
#define TRIGGER_LEFT 13

#define ECHO_RIGHT 2
#define TRIGGER_RIGHT 3

#define ECHO_CENTER 7
#define TRIGGER_CENTER 8

#define M1 10
#define M2 9
#define M3 6
#define M4 5

#define SPEED 150

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(TRIGGER_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIGGER_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIGGER_CENTER, OUTPUT);
  pinMode(ECHO_CENTER, INPUT);

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);

  pinMode(11, OUTPUT);
  pinMode(4, OUTPUT);

  digitalWrite(11, HIGH);
  digitalWrite(4, HIGH);
}

int state = 3;

void loop()
{
  // put your main code here, to run repeatedly:
  float distanceLeft = calculateDistance(TRIGGER_LEFT, ECHO_LEFT);
  float distanceRight = calculateDistance(TRIGGER_RIGHT, ECHO_RIGHT);
  float distanceCenter = calculateDistance(TRIGGER_CENTER, ECHO_CENTER);

  if (distanceCenter < 20 || distanceRight < 20 || distanceLeft < 20)
  {
    if (distanceLeft > distanceRight && distanceLeft > 15)
    {
      state = 1;
    }
    else if (distanceRight > distanceLeft && distanceRight > 15)
    {
      state = 2;
    }
  }
  else
  {
    state = 3;
  }

  switch (state)
  {
  case 1:
    left();
    break;
  case 2:
    right();
    break;
  case 3:
    forward();
    break;
  }
}

float calculateDistance(int trigger, int echo)
{
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  float time = pulseIn(echo, HIGH);
  float distance = ((time * 0.000340) / 2.0) * 100.0;

  return distance;
}

void right()
{
  analogWrite(M1, SPEED);
  digitalWrite(M2, LOW);

  analogWrite(M3, SPEED);
  digitalWrite(M4, LOW);
}

void left()
{
  digitalWrite(M1, LOW);
  analogWrite(M2, SPEED);

  digitalWrite(M3, LOW);
  analogWrite(M4, SPEED);
}

void back()
{
  digitalWrite(M1, LOW);
  analogWrite(M2, SPEED);

  analogWrite(M3, SPEED);
  digitalWrite(M4, LOW);
}

void forward()
{
  analogWrite(M1, SPEED);
  digitalWrite(M2, LOW);

  digitalWrite(M3, LOW);
  analogWrite(M4, SPEED);
}

void stop()
{
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);

  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
}