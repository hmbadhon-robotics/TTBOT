#include "NewPing.h"
#include <Servo.h>
Servo myservo;

#define numberOfValsRec 1
#define digitsPerValRec 2

#define echoPinF 8
#define trigPinF 8
#define echoPinL 4
#define trigPinL 4
#define echoPinR 7
#define trigPinR 7
#define echoPinB 2
#define trigPinB 2
#define MAX_DISTANCE 400

int valsRec[numberOfValsRec];
int stringLength = numberOfValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString;
int serialData;
//----------//
boolean state_F, state_B, state_L, state_R = LOW;


NewPing sonarF(trigPinF, echoPinF, MAX_DISTANCE);
NewPing sonarL(trigPinL, echoPinL, MAX_DISTANCE);
NewPing sonarR(trigPinR, echoPinR, MAX_DISTANCE);
NewPing sonarB(trigPinB, echoPinB, MAX_DISTANCE);


float durationF; // Stores First HC-SR04 pulse duration value
float durationL; // Stores Second HC-SR04 pulse duration value
float durationR; // Stores Third HC-SR04 pulse duration value
float durationB; // Stores Fourth HC-SR04 pulse duration value
float distanceF; // Stores calculated distance in cm for First Sensor
float distanceL; // Stores calculated distance in cm for Second Sensor
float distanceR; // Stores calculated distance in cm for Third Sensor
float distanceB; // Stores calculated distance in cm for Fourth Sensor
float soundsp;  // Stores calculated speed of sound in M/S
float soundcm;  // Stores calculated speed of sound in cm/ms
int iterations = 4;

int pos = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(6);
  myservo.write(70);
  pinMode(3, OUTPUT); // 2 wheels with pin 3, 9, 10, 11
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}
void forward(boolean f)
{
  //Serial.println("Forward");
  digitalWrite(3, 0);
  digitalWrite(9, f);
  digitalWrite(10, 0);
  digitalWrite(11, f);
}

void backward(boolean b)
{
  //Serial.println("Backward");
  digitalWrite(3, b);
  digitalWrite(9, LOW);
  digitalWrite(10, b);
  digitalWrite(11, LOW);
}

void left(boolean l)
{
  //Serial.println("Left");
  digitalWrite(3, LOW);
  digitalWrite(9, l);
  digitalWrite(10, l);
  digitalWrite(11, LOW);

}
void right(boolean r)
{
  //Serial.println("Right");
  digitalWrite(3, r);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, r);
}
void stopp()
{
  digitalWrite(3, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void up()
{
  if (pos < 140)
  {
    pos = pos + 10;
    myservo.write(pos);
  }

}
void down()
{
  if (pos > 10)
  {
    pos = pos - 10;
    myservo.write(pos);
  }

}

void receiveData() {

  while (Serial.available()) {

    char c = Serial.read();

    if (c == '$') {

      counterStart = true;

    }

    if (counterStart) {

      if (counter < stringLength) {

        receivedString = String(receivedString + c);
        counter++;

      }

      if (counter >= stringLength) {

        for (int i = 0; i < numberOfValsRec; i++) {

          int num = (i * digitsPerValRec) + 1;
          valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();

        }

        receivedString = "";
        counter = 0;
        counterStart = false;

      }
    }
  }
}



void loop()
{
  soundsp = 346.5;

  soundcm = soundsp / 10000;

  durationF = sonarF.ping_median(iterations);
  durationL = sonarL.ping_median(iterations);
  durationR = sonarR.ping_median(iterations);
  durationB = sonarB.ping_median(iterations);


  distanceF = (durationF / 2) * soundcm;
  distanceL = (durationL / 2) * soundcm;
  distanceR = (durationR / 2) * soundcm;
  distanceB = (durationB / 2) * soundcm;


  //Serial.println(m);

  if (distanceF <= 30) {
    state_F = LOW;
  }
  else if (distanceF > 30 || distanceF > MAX_DISTANCE) {
    state_F = HIGH;
  }
  if (distanceB <= 20) {
    state_B = LOW;
  }
  else if (distanceB > 20) {
    state_B = HIGH;
  }
  if (distanceL <= 20) {
    state_L = LOW;
  }
  else if (distanceL > 20) {
    state_L = HIGH;
  }
  if (distanceR <= 20) {
    state_R = LOW;
  }
  else if (distanceR > 20) {
    state_R = HIGH;
  }



  //Motors
  receiveData();
  serialData = valsRec[0];

  if (serialData == 1) {
    forward(state_F);
  }

  else if (serialData == 2) {
    backward(state_B);
  }

  else if (serialData == 3) {
    left(state_L);
  }

  else if (serialData == 4) {
    right(state_R);
  }

  else if (serialData == 5) {
    up();
    delay(10);
  }
  else if (serialData == 6) {
    down();
    delay(10);
  }
  else stopp();

  /*
    // DEBUG PINS AND SENSORS

    Serial.print(digitalRead(5), DEC);
    Serial.print("\t");

    Serial.print(digitalRead(9), DEC);
    Serial.print("\t");

    Serial.print(digitalRead(10), DEC);
    Serial.print("\t");

    Serial.print(digitalRead(11), DEC);
    Serial.print("\t");
    Serial.print("\n");



    Serial.print(distanceF, 0);
    Serial.print("\t");

    Serial.print(distanceB, 0);
    Serial.print("\t");

    Serial.print(distanceL, 0);
    Serial.print("\t");

    Serial.print(distanceR, 0);
    Serial.print("\t");
    Serial.print("\n");


    Serial.print(state_F);
    Serial.print("\t");write

    Serial.print(state_B);
    Serial.print("\t");

    Serial.print(state_L);
    Serial.print("\t");

    Serial.print(state_R);
    Serial.print("\t");
    Serial.print("\n");


    delay(1000);

    //END DEBUGGING
  */
}
