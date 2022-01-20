#include <CrsfSerial.h>  // https://github.com/CapnBry/CRServoF/
#include <PicoGamepad.h> // https://gitlab.com/realrobots/PicoGamepad/-/tree/master

#include "calibration.h"

UART Serial2(4, 5, NC, NC);  // GPIO 4/5, physical pin 6/7

CrsfSerial crsf(Serial2, CRSF_BAUDRATE); // pass any HardwareSerial port
int channel_data = 0;
int map_data = 0;

PicoGamepad gamepad;
//#define BTN_PRINT
//#define BTN_PRINT_SUM

#ifdef BTN_PRINT_SUM
byte aux[8] = {0,0,0,0,0,0,0,0};
#endif

/***
 * This callback is called whenever new channel values are available.
 * Use crsf.getChannel(x) to get us channel values (1-16).
 ***/
void packetChannels()
{
    // Manually expanding instead of looping so I can change params as needed
    
    // X - Channel 1 - A
    channel_data = crsf.getChannel(1);
    map_data = map(channel_data, \
      CHANNEL_1_LOW_EP,          \
      CHANNEL_1_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gamepad.SetX(map_data);
    
    // Y - Channel 2 - E
    channel_data = crsf.getChannel(2);
    map_data = map(channel_data, \
      CHANNEL_2_LOW_EP,          \
      CHANNEL_2_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gamepad.SetY(map_data);
    
    // Z - Channel 3 - T
    channel_data = crsf.getChannel(3);
    map_data = map(channel_data, \
      CHANNEL_3_LOW_EP,          \
      CHANNEL_3_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gamepad.SetZ(map_data);
    
    // Rx - Channel 4 - R
    channel_data = crsf.getChannel(4);
    map_data = map(channel_data, \
      CHANNEL_4_LOW_EP,          \
      CHANNEL_4_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gamepad.SetRx(map_data);
    
    // Ry - unused
    // gamepad.SetRy(map_data);
    // Rz - unused
    // gamepad.SetRz(map_data);
    // S0 - unused
    // gamepad.SetS0(map_data);
    // S1 - unused
    // gamepad.SetS1(map_data);

    // TODO how to handle multi position switches (would have to be defined somehow by the user)
    // for now, sticking to 1 bit switches
    
    // Set button 0 of 128 by reading button on digital pin 28
    // gamepad.SetButton(0, !digitalRead(28));
    // button 0 - Channel 5 / Aux 1 - arm
    channel_data = crsf.getChannel(5);
    map_data = map(channel_data, \
      CHANNEL_AUX_SW_LOW,        \
      CHANNEL_AUX_SW_HIGH,       \
      CHANNEL_AUX_SW_LOW_MAP,    \
      CHANNEL_AUX_SW_HIGH_MAP);
    gamepad.SetButton(0, map_data);
    #ifdef BTN_PRINT_SUM
    aux[0] = map_data;
    #endif
    #ifdef BTN_PRINT
    Serial.print("c: "); Serial.print(channel_data); 
    Serial.print(" m: "); Serial.println(map_data);
    #endif
    
    // button 1 - Channel 6 / Aux 2
    channel_data = crsf.getChannel(6);
    map_data = map(channel_data, \
      CHANNEL_AUX_SW_LOW,        \
      CHANNEL_AUX_SW_HIGH,       \
      CHANNEL_AUX_SW_LOW_MAP,    \
      CHANNEL_AUX_SW_HIGH_MAP);
    gamepad.SetButton(1, map_data);
    #ifdef BTN_PRINT_SUM
    aux[1] = map_data;
    #endif
    #ifdef BTN_PRINT
    Serial.print("c: "); Serial.print(channel_data); 
    Serial.print(" m: "); Serial.println(map_data);
    #endif
    
    // button 2 - Channel 7 / Aux 3
    channel_data = crsf.getChannel(7);
    map_data = map(channel_data, \
      CHANNEL_AUX_SW_LOW,        \
      CHANNEL_AUX_SW_HIGH,       \
      CHANNEL_AUX_SW_LOW_MAP,    \
      CHANNEL_AUX_SW_HIGH_MAP);
    gamepad.SetButton(2, map_data);
    #ifdef BTN_PRINT_SUM
    aux[2] = map_data;
    #endif
    #ifdef BTN_PRINT
    Serial.print("c: "); Serial.print(channel_data); 
    Serial.print(" m: "); Serial.println(map_data);
    #endif
    
    // button 3 - Channel 8 / Aux 4
    channel_data = crsf.getChannel(8);
    map_data = map(channel_data, \
      CHANNEL_AUX_SW_LOW,        \
      CHANNEL_AUX_SW_HIGH,       \
      CHANNEL_AUX_SW_LOW_MAP,    \
      CHANNEL_AUX_SW_HIGH_MAP);
    gamepad.SetButton(3, map_data);
    #ifdef BTN_PRINT_SUM
    aux[3] = map_data;
    #endif
    #ifdef BTN_PRINT
    Serial.print("c: "); Serial.print(channel_data); 
    Serial.print(" m: "); Serial.println(map_data);
    #endif
    
    // button 4 - Channel 9 / Aux 5
    channel_data = crsf.getChannel(9);
    map_data = map(channel_data, \
      CHANNEL_AUX_SW_LOW,        \
      CHANNEL_AUX_SW_HIGH,       \
      CHANNEL_AUX_SW_LOW_MAP,    \
      CHANNEL_AUX_SW_HIGH_MAP);
    gamepad.SetButton(4, map_data);
    #ifdef BTN_PRINT_SUM
    aux[4] = map_data;
    #endif
    #ifdef BTN_PRINT
    Serial.print("c: "); Serial.print(channel_data); 
    Serial.print(" m: "); Serial.println(map_data);
    #endif
    
    // button 5 - Channel 10 / Aux 6
    channel_data = crsf.getChannel(10);
    map_data = map(channel_data, \
      CHANNEL_AUX_SW_LOW,        \
      CHANNEL_AUX_SW_HIGH,       \
      CHANNEL_AUX_SW_LOW_MAP,    \
      CHANNEL_AUX_SW_HIGH_MAP);
    gamepad.SetButton(5, map_data);
    #ifdef BTN_PRINT_SUM
    aux[5] = map_data;
    #endif
    #ifdef BTN_PRINT
    Serial.print("c: "); Serial.print(channel_data); 
    Serial.print(" m: "); Serial.println(map_data);
    #endif
    
    // button 6 - Channel 11 / Aux 7
    channel_data = crsf.getChannel(11);
    map_data = map(channel_data, \
      CHANNEL_AUX_SW_LOW,        \
      CHANNEL_AUX_SW_HIGH,       \
      CHANNEL_AUX_SW_LOW_MAP,    \
      CHANNEL_AUX_SW_HIGH_MAP);
    gamepad.SetButton(6, map_data);
    #ifdef BTN_PRINT_SUM
    aux[6] = map_data;
    #endif
    #ifdef BTN_PRINT
    Serial.print("c: "); Serial.print(channel_data); 
    Serial.print(" m: "); Serial.println(map_data);
    #endif
    
    // button 7 - Channel 12 / Aux 8
    channel_data = crsf.getChannel(12);
    map_data = map(channel_data, \
      CHANNEL_AUX_SW_LOW,        \
      CHANNEL_AUX_SW_HIGH,       \
      CHANNEL_AUX_SW_LOW_MAP,    \
      CHANNEL_AUX_SW_HIGH_MAP);
    gamepad.SetButton(7, map_data);
    #ifdef BTN_PRINT_SUM
    aux[7] = map_data;
    #endif
    #ifdef BTN_PRINT
    Serial.print("c: "); Serial.print(channel_data); 
    Serial.print(" m: "); Serial.println(map_data);
    #endif

    #ifdef BTN_PRINT_SUM
    for(byte i =0 ;i < 8; i++) {
      Serial.print(aux[i]);
    }
    Serial.println("");
    #endif

    // TODO what to do with Channel 13,14,15,16 (NA,NA, LQ,RSSI)

    // Set hat direction, 4 hats available. direction is clockwise 0=N 1=NE 2=E 3=SE 4=S 5=SW 6=W 7=NW 8=CENTER 
    // gamepad.SetHat(0, 8);

    gamepad.send_update();
    
}

void crsfLinkUp() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void crsfLinkDown() {
  digitalWrite(LED_BUILTIN, LOW);
}


void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    // If something other than changing the baud of the UART needs to be done, do it here
    // Serial1.end(); Serial1.begin(500000, SERIAL_8N1, 16, 17);

    // Attach the channels callback
    crsf.onPacketChannels = &packetChannels;
    crsf.onLinkUp = &crsfLinkUp;
    crsf.onLinkDown = &crsfLinkDown;
}

void loop()
{
    // Must call CrsfSerial.loop() in loop() to process data
    crsf.loop();
}
