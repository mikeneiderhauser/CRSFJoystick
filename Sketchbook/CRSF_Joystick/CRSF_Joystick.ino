#include <CrsfSerial.h>  // https://github.com/CapnBry/CRServoF/
#include <PicoGamepad.h> // https://gitlab.com/realrobots/PicoGamepad/-/tree/master

#include "calibration.h"

// ONLY UNCOMMENT 1 Board ID
//#define BOARD_ID 1  // PiPico
//#define BOARD_ID 2  // TINY2040
#define BOARD_ID 3  // WaveShare RP2040-Zero
//#define BOARD_ID 4  // Seeed XAIO 2040

#include "board_defs.h"

UART Serial2(CRSF_TX, CRSF_RX, NC, NC);

CrsfSerial crsf(Serial2, CRSF_BAUDRATE); // pass any HardwareSerial port
int channel_data = 0;
int map_data = 0;

PicoGamepad gamepad;
//#define BTN_PRINT

btn_config *c;

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
    
    // Rx - Channel 3 - T
    channel_data = crsf.getChannel(3);
    map_data = map(channel_data, \
      CHANNEL_3_LOW_EP,          \
      CHANNEL_3_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gamepad.SetRx(map_data);
    
    // Ry - Channel 4 - R
    channel_data = crsf.getChannel(4);
    map_data = map(channel_data, \
      CHANNEL_4_LOW_EP,          \
      CHANNEL_4_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gamepad.SetRy(map_data);

    // Z - Channel 5
    channel_data = crsf.getChannel(5);
    map_data = map(channel_data, \
      CHANNEL_5_LOW_EP,          \
      CHANNEL_5_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gamepad.SetZ(map_data);

    // Rz - Channel 6
    channel_data = crsf.getChannel(6);
    map_data = map(channel_data, \
      CHANNEL_6_LOW_EP,          \
      CHANNEL_6_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gamepad.SetRz(map_data);
    
    // Rx - Channel 7
    channel_data = crsf.getChannel(7);
    map_data = map(channel_data, \
      CHANNEL_7_LOW_EP,          \
      CHANNEL_7_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gamepad.SetS0(map_data);

    // Rx - Channel 8
    channel_data = crsf.getChannel(8);
    map_data = map(channel_data, \
      CHANNEL_8_LOW_EP,          \
      CHANNEL_8_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gamepad.SetS1(map_data);

    // Ry - unused
    // gamepad.SetRy(map_data);
    // Rz - unused
    // gamepad.SetRz(map_data);
    // S0 - unused
    // gamepad.SetS0(map_data);
    // S1 - unused
    // gamepad.SetS1(map_data);

    // Multi-position switches can be set up in calibrations.h
    // The button will report HIGH when the channel is withing
    // a lower / upper bound (inclusive) constraint.
    // Default is HIGH (1510, 2011) else LOW

    for(uint8_t i = 0; i < NUM_BUTTONS; i++){
      c = &btn_map[i];
      channel_data = crsf.getChannel(c->channel);
      // bounds check inclusive
      if(channel_data >= c->lower_bound && channel_data <= c->upper_bound) {
        map_data = c->invert ? LOW : HIGH;
      }
      else {
        map_data = c->invert ? HIGH : LOW;
      }
      gamepad.SetButton(c->id, map_data);

      #ifdef BTN_PRINT
      Serial.print("b: "); Serial.print(c->id));
      Serial.print(" c: "); Serial.print(channel_data); 
      Serial.print(" m: "); Serial.println(map_data);
      #endif
    }
    // TODO what to do with Channel 13,14,15,16 (NA,NA,LQ,RSSI)

    // Set hat direction, 4 hats available. direction is clockwise 0=N 1=NE 2=E 3=SE 4=S 5=SW 6=W 7=NW 8=CENTER 
    // gamepad.SetHat(0, 8);

    gamepad.send_update();
}

void crsfLinkUp() {
  led_on();
}

void crsfLinkDown() {
  led_off();
}

void setup()
{
    Serial.begin(115200);
    boardSetup();
    led_off();

    gamepad.send_update();
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
