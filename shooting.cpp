// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__ESP32CORE_BLE

#include <BLEDevice.h>

// RemoteXY connection settings
#define REMOTEXY_BLUETOOTH_NAME "shooting_ESP"
#define REMOTEXY_ACCESS_PASSWORD "2557"

#include <RemoteXY.h>
#include <ESP32Servo.h>
Servo servo1;
Servo servo2;

const int servo_1 = 9;
const int servo_2 = 10;

// RemoteXY GUI configuration
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 57 bytes
  { 255,1,0,0,0,50,0,19,0,0,0,0,31,1,106,200,1,1,2,0,
  1,21,94,63,63,0,2,31,0,129,7,79,101,10,64,17,112,117,115,104,
  32,98,117,116,116,111,110,32,116,111,32,115,104,111,111,116,0 };

// this structure defines all the variables and events of your control interface
struct {

    // input variables
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

    servo1.attach(servo_1);
    servo1.write(0);

    servo2.attach(servo_2);
    servo2.write(180 - 75);
}

void loop()
{
    RemoteXY_Handler ();

    if(RemoteXY.button_01 == 1){
        servo1.write(90);
        servo2.write(180 - 110);
        delay(15);
        servo1.write(0);
        servo2.write(180 - 75);

    }

}
