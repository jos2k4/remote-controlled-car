//#define REMOTEXY__DEBUGLOG

// DEFINITIONS
const int engine_1_F_Pin = 18; //white cable
const int engine_1_B_Pin = 19; //red cable
const int engine_2_F_Pin = 2;  //black cable
const int engine_2_B_Pin = 3;  //blue cable

//Pololu QTR-1A Pins
int sensor_1_Pin = 0;
int sensor_2_Pin = 1;
// Joystick deadzone threshold
const int deadzone = 25;

int black = 3000;

//Pololu QTR-1A Treshold value
const int blackThreshold = 500;


// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__ESP32CORE_BLE
#include <ESP32Servo.h>
Servo myServo;

#include <BLEDevice.h>

// RemoteXY connection settings
#define REMOTEXY_BLUETOOTH_NAME "Ersti_final"
#define REMOTEXY_ACCESS_PASSWORD "welovehsnr"


#include <RemoteXY.h>

// RemoteXY GUI configuration
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 55 bytes
  { 255,4,0,0,0,48,0,19,0,0,0,0,31,1,106,200,1,1,3,0,
  2,2,7,44,22,0,2,26,31,31,79,78,0,79,70,70,0,5,15,102,
  76,76,32,2,26,31,1,58,58,45,45,0,2,31,0 };

// this structure defines all the variables and events of your control interface
struct {

    // input variables
  uint8_t switch_01; // =1 if switch ON and =0 if OFF
  int8_t joystick_01_x; // from -100 to 100
  int8_t joystick_01_y; // from -100 to 100
  uint8_t button_01; // =1 if button pressed, else =0

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup()
{
   RemoteXY_Init ();

    Serial.begin(9600);


  // engines control pins
  pinMode(engine_1_F_Pin, OUTPUT);
  pinMode(engine_1_B_Pin, OUTPUT);
  pinMode(engine_2_F_Pin, OUTPUT);
  pinMode(engine_2_B_Pin, OUTPUT);

  //engines off
  analogWrite(engine_1_F_Pin, 0);
  analogWrite(engine_1_B_Pin, 0);
  analogWrite(engine_2_F_Pin, 0);
  analogWrite(engine_2_B_Pin, 0);


}

void loop()
{
   RemoteXY_Handler ();
  sensor_1_Pin = analogRead(A0);
  sensor_2_Pin = analogRead(A1);
  //RemoteXY_delay(200);
  int sensorValue1 = sensor_1_Pin;
  int sensorValue2 = sensor_2_Pin;

  // Get joystick values
  int joyX = RemoteXY.joystick_01_x;
  int joyY = RemoteXY.joystick_01_y;

// remove “//” to start debugging

  //Serial.println("1:");
 // Serial.println(sensorValue1);

  //Serial.println("2:");
  //Serial.println(sensorValue2);



    //Serial.println("2");
  //Serial.println(sensorValue2);

//car can only move when power button is set to on
if(RemoteXY.switch_01 == 1){

// Movement control logic
if (abs(joyY) > deadzone || abs(joyX) > deadzone) {

    if (joyY > deadzone) {  // Forward
        analogWrite(engine_1_F_Pin, 255);
        analogWrite(engine_2_F_Pin, 255);
        analogWrite(engine_1_B_Pin, 0);
        analogWrite(engine_2_B_Pin, 0);
        delay(100);
        analogWrite(engine_1_F_Pin, 0);
        analogWrite(engine_2_F_Pin, 0);
    } else if (joyY < -deadzone) {  // Backward
        analogWrite(engine_1_F_Pin, 0);
        analogWrite(engine_2_F_Pin, 0);
        analogWrite(engine_1_B_Pin, 255);
        analogWrite(engine_2_B_Pin, 255);
        delay(100);
        analogWrite(engine_1_B_Pin, 0);
        analogWrite(engine_2_B_Pin, 0);
    }


    if (joyX > deadzone) {  // Right
        analogWrite(engine_1_F_Pin, 0);
        analogWrite(engine_1_B_Pin, 255);
        delay(100);
        analogWrite(engine_1_B_Pin, 0);

    } else if (joyX < -deadzone) {  // Left
        analogWrite(engine_1_F_Pin, 255);
        analogWrite(engine_1_B_Pin, 0);
        delay(100);
        analogWrite(engine_1_F_Pin, 0);

    }

}
 if(sensorValue2 > 700){	//2-3cm distance to ground
        analogWrite(engine_1_B_Pin, 0);
        analogWrite(engine_2_B_Pin, 0);
        delay(200);
        analogWrite(engine_1_F_Pin, 255);
        analogWrite(engine_2_F_Pin, 255);
        delay(300);
        analogWrite(engine_1_F_Pin, 0);
        analogWrite(engine_2_F_Pin, 0);
    }
    if(sensorValue1 > 700){	//2-3cm distance to ground
        analogWrite(engine_1_F_Pin, 0);
        analogWrite(engine_2_F_Pin, 0);
        delay(50);
        analogWrite(engine_1_B_Pin, 255);
        analogWrite(engine_2_B_Pin, 255);
        delay(600);
        analogWrite(engine_1_B_Pin, 0);
        analogWrite(engine_2_B_Pin, 0);
    }} else {  // Stop all engines
    analogWrite(engine_1_F_Pin, 0);
    analogWrite(engine_1_B_Pin, 0);
    analogWrite(engine_2_F_Pin, 0);
    analogWrite(engine_2_B_Pin, 0);
}


}
