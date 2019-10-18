
#include "Wire.h"
#include "MMA8653.h"
#include "Servo.h"

MMA8653 accel;
Servo servoX;
Servo servoY;

#define SERVO_MIN 0
#define SERVO_MID 90
#define SERVO_MAX 180
#define SERVOX_DELTA 2
#define SERVOY_DELTA 2
#define ACC_MIN -64
#define ACC_MAX  64

int posY = SERVO_MID;

void setup() {
  pinMode(PC13, OUTPUT);
  Serial.begin(115200);
  Wire.begin();
  accel.begin(false, 2);
//  servoX.attach(8);
//  servoY.attach(9);
  servoX.attach(PB9);
  servoY.attach(PB8);
  servoX.write(SERVO_MID);
  servoY.write(posY);
  
  delay(1000);
}


//uint8_t rdata;
//uint8_t i;
int x, y, z;
int x_old, y_old, z_old;
//uint8_t stat;
//String stringOutput;
long start=0, s_start=0, led_start=0;
bool led_on = false;
//#define TRG 120

void loop() {
  if ((millis() - s_start > 10)) {
    s_start = millis();
    accel.update();
    x = accel.getX();
    y = accel.getY();
    x = constrain(x, ACC_MIN, ACC_MAX);
    y = constrain(y, ACC_MIN, ACC_MAX);
    if ((x > (x_old+SERVOX_DELTA)) || (x < (x_old-SERVOX_DELTA))){
      x_old = x;
      servoX.write(SERVO_MAX - map(x, ACC_MIN, ACC_MAX, SERVO_MIN, SERVO_MAX));
      Serial.print("servoX = ");
      Serial.println(SERVO_MAX - map(x, ACC_MIN, ACC_MAX, SERVO_MIN, SERVO_MAX));
    }
    if ((y > (y_old+SERVOY_DELTA)) || (y < (y_old-SERVOY_DELTA))){
      y_old = y;
//      if ((y > 2) && (posY > SERVO_MIN)) {
//        posY--;// = constrain((posY - map(y, ACC_MIN, ACC_MAX, SERVO_MIN, SERVO_MAX)), SERVO_MIN, SERVO_MAX);
//        servoY.write(posY);
//        Serial.print("servoY = ");
//        Serial.println(posY);
//      }
//      else if ((y < -2) && (posY < SERVO_MAX)) {
////        posY++;
//        posY++;// = constrain((posY + map(y, ACC_MIN, ACC_MAX, SERVO_MIN, SERVO_MAX)), SERVO_MIN, SERVO_MAX);
//        servoY.write(posY);
        Serial.print("servoY = ");
//        Serial.println(posY);
//      }
      servoY.write(SERVO_MAX - map(y, ACC_MIN, ACC_MAX, SERVO_MIN, SERVO_MAX));
      Serial.println(SERVO_MAX - map(y, ACC_MIN, ACC_MAX, SERVO_MIN, SERVO_MAX));
    }
  //Serial.println("X,\tY,\tZ,\tRho,\tPhi,\tTheta");
  //if (abs(accel.getX()) > TRG || abs(accel.getY()) > TRG || abs(accel.getZ()) > TRG) digitalWrite(6, HIGH); else digitalWrite(6, LOW);
    if ((millis() - start > 1000)) {
      start = millis();
      Serial.print("X = ");
      Serial.print(x);
      Serial.print(" ,Y = ");
      Serial.print(y);
      Serial.print(" ,Z = ");
      Serial.println(accel.getZ());
    }
  }
  if ((millis() - led_start > 500)) {
    led_start = millis();
    if (led_on) {
      digitalWrite(PC13, HIGH);
      led_on = false;
    }
    else {
      digitalWrite(PC13, LOW);
      led_on = true;
    }
  }
}
