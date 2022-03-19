#include "Adafruit_TinyUSB.h"

#include <CrsfSerial.h>  // https://github.com/CapnBry/CRServoF/

#include "calibration.h"

//#define BTN_PRINT

CrsfSerial* crsf = NULL;
int channel_data = 0;
int8_t map_data = 0;

btn_config *c;

// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_GAMEPAD()
};

// USB HID object. For ESP32 these values cannot be changed after this declaration
// desc report, desc len, protocol, interval, use out endpoint
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, false);

// Report payload defined in src/class/hid/hid.h
// - For Gamepad Button Bit Mask see  hid_gamepad_button_bm_t
// - For Gamepad Hat    Bit Mask see  hid_gamepad_hat_t
hid_gamepad_report_t    gp;

void packetChannels()
{
    // Manually expanding instead of looping so I can change params as needed
    
    // X - Channel 1 - A
    channel_data = crsf->getChannel(1);
    map_data = map(channel_data, \
      CHANNEL_1_LOW_EP,          \
      CHANNEL_1_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gp.x = map_data;
    
    // Y - Channel 2 - E
    channel_data = crsf->getChannel(2);
    map_data = map(channel_data, \
      CHANNEL_2_LOW_EP,          \
      CHANNEL_2_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gp.y = map_data;
    
    // Rx - Channel 3 - T
    channel_data = crsf->getChannel(3);
    map_data = map(channel_data, \
      CHANNEL_3_LOW_EP,          \
      CHANNEL_3_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gp.rx = map_data;
    
    // Ry - Channel 4 - R
    channel_data = crsf->getChannel(4);
    map_data = map(channel_data, \
      CHANNEL_4_LOW_EP,          \
      CHANNEL_4_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gp.ry = map_data;

    // Z - Channel 5
    channel_data = crsf->getChannel(5);
    map_data = map(channel_data, \
      CHANNEL_5_LOW_EP,          \
      CHANNEL_5_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gp.z = map_data;

    // Rz - Channel 6
    channel_data = crsf->getChannel(6);
    map_data = map(channel_data, \
      CHANNEL_6_LOW_EP,          \
      CHANNEL_6_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gp.rz = map_data;
    
    // Multi-position switches can be set up in calibrations.h
    // The button will report HIGH when the channel is withing
    // a lower / upper bound (inclusive) constraint.
    // Default is HIGH (1510, 2011) else LOW

    gp.buttons = 0;
    for(uint8_t i = 0; i < NUM_BUTTONS; i++){
      c = &btn_map[i];
      channel_data = crsf->getChannel(c->channel);
      // bounds check inclusive
      if(channel_data >= c->lower_bound && channel_data <= c->upper_bound) {
        map_data = c->invert ? LOW : HIGH;
      }
      else {
        map_data = c->invert ? HIGH : LOW;
      }
      
      if(map_data == HIGH)
      {
        gp.buttons |= TU_BIT(c->id);
      }

      #ifdef BTN_PRINT
      Serial.print("b: "); Serial.print(c->id);
      Serial.print(" c: "); Serial.print(channel_data); 
      Serial.print(" m: "); Serial.println(map_data);
      #endif
    }
    // TODO what to do with Channel 13,14,15,16 (NA,NA,LQ,RSSI)

    usb_hid.sendReport(0, &gp, sizeof(gp));
}

void crsfLinkUp() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void crsfLinkDown() {
  digitalWrite(LED_BUILTIN, LOW);
}

void setup()
{
#if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
  // Manual begin() is required on core without built-in support for TinyUSB such as mbed rp2040
  TinyUSB_Device_Init(0);
#endif

  Serial.begin(115200); 

  // Notes: following commented-out functions has no affect on ESP32
  // usb_hid.setPollInterval(2);
  // usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();

  // If something other than changing the baud of the UART needs to be done, do it here
  // Serial1.end(); Serial1.begin(500000, SERIAL_8N1, 16, 17);
  
  crsf = new CrsfSerial(Serial1, CRSF_BAUDRATE); // pass any HardwareSerial port

  pinMode(LED_BUILTIN, OUTPUT);
  
  // Attach the channels callback
  crsf->onPacketChannels = &packetChannels;
  crsf->onLinkUp = &crsfLinkUp;
  crsf->onLinkDown = &crsfLinkDown;

  // wait until device mounted
  while( !TinyUSBDevice.mounted() ) delay(1);
}

void loop()
{
//  // Remote wakeup
//  if ( TinyUSBDevice.suspended() && btn )
//  {
//    // Wake up host if we are in suspend mode
//    // and REMOTE_WAKEUP feature is enabled by host
//    TinyUSBDevice.remoteWakeup();
//  }
  
  if ( !usb_hid.ready() ) return;

  // Must call CrsfSerial.loop() in loop() to process data
  crsf->loop();
}
