#include <CrsfSerial.h>  // https://github.com/CapnBry/CRServoF/
#include <PicoGamepad.h> // https://gitlab.com/realrobots/PicoGamepad/-/tree/master

#include "calibration.h"

// ONLY UNCOMMENT 1 Board ID
//#define BOARD_ID 1  // PiPico
//#define BOARD_ID 2  // TINY2040
#define BOARD_ID 3  // WaveShare RP2040-Zero
//#define BOARD_ID 4  // Seeed XAIO 2040

// Blink routine variables and state tracking
#define BLINK_ENABLED                    // comment this line out to disable led blink
#define BLINK_TIME 60000                 // blink routine window (in ms)
#define BLINK_DELAY 500                  // delay in between led state change (in ms)

static bool serialEcho;
static char serialInBuff[64];
static uint8_t serialInBuffLen;

bool led_state = false;                  // track led on/off state
unsigned long ms_curr = 0;               // current time
unsigned long ms_last_link_changed = 0;  // last time crsf link changed
unsigned long ms_last_led_changed = 0;   // last time led changed state in blink routine

#include "board_defs.h"

UART Serial2(CRSF_TX, CRSF_RX, NC, NC);

CrsfSerial crsf(Serial2, CRSF_BAUDRATE); // pass any HardwareSerial port
int channel_data = 0;
int map_data = 0;

PicoGamepad gamepad;

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
    gamepad.SetThrottle(map_data);

    // Rx - Channel 8
    channel_data = crsf.getChannel(8);
    map_data = map(channel_data, \
      CHANNEL_8_LOW_EP,          \
      CHANNEL_8_HIGH_EP,         \
      JOYSTICK_LOW,              \
      JOYSTICK_HIGH);
    gamepad.SetS0(map_data);

    // Ry - unused
    // gamepad.SetRy(map_data);
    // Rz - unused
    // gamepad.SetRz(map_data);
    // S0 - unused
    // gamepad.SetS0(map_data);

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
  ms_last_link_changed = millis();
  ms_last_led_changed = ms_last_link_changed;
  led_state = true;
  led_on();
}

void crsfLinkDown() {
  ms_last_link_changed = millis();
  ms_last_led_changed = ms_last_link_changed;
  led_state = false;
  led_off();
}

static void passthroughBegin(uint32_t baud)
{
    if (baud != crsf.getBaud())
    {
        // Force a reboot command since we want to send the reboot
        // at 420000 then switch to what the user wanted
        const uint8_t rebootpayload[] = { 'b', 'l' };
        crsf.queuePacket(CRSF_ADDRESS_CRSF_RECEIVER, CRSF_FRAMETYPE_COMMAND, &rebootpayload, sizeof(rebootpayload));
    }
    crsf.setPassthroughMode(true, baud);
    
    serialEcho = false;
}

static void crsfOobData(uint8_t b)
{
    Serial.write(b);
}

/***
 * @brief Processes a text command like we're some sort of CLI or something
 * @return true if CrsfSerial was placed into passthrough mode, false otherwise
*/
static bool handleSerialCommand(char *cmd)
{
    // Fake a CRSF RX on UART6
    bool prompt = true;
    if (strcmp(cmd, "#") == 0)
    {
        Serial.println("Fake CLI Mode, type 'exit' or 'help' to do nothing\r\n");
        serialEcho = true;
    }

    else if (strcmp(cmd, "serial") == 0)
        Serial.println("serial 5 64 0 0 0 0\r\n");

    else if (strcmp(cmd, "get serialrx_provider") == 0)
        Serial.println("serialrx_provider = CRSF\r\n");

    else if (strcmp(cmd, "get serialrx_inverted") == 0)
        Serial.println("serialrx_inverted = OFF\r\n");

    else if (strcmp(cmd, "get serialrx_halfduplex") == 0)
        Serial.println("serialrx_halfduplex = OFF\r\n");

    else if (strncmp(cmd, "serialpassthrough 5 ", 20) == 0)
    {
        Serial.println(cmd);

        unsigned int baud = atoi(&cmd[20]);
        passthroughBegin(baud);

        return true;
    }

    else
        prompt = false;

    if (prompt)
        Serial.print("# ");

    return false;
}

static void checkSerialInNormal()
{
    while (Serial.available())
    {
        char c = Serial.read();
        if (serialEcho && c != '\n')
            Serial.write(c);

        if (c == '\r' || c == '\n')
        {
            if (serialInBuffLen != 0)
            {
                Serial.write('\n');
                serialInBuff[serialInBuffLen] = '\0';
                serialInBuffLen = 0;

                bool goToPassthrough = handleSerialCommand(serialInBuff);
                // If need to go to passthrough, get outta here before we dequeue any bytes
                if (goToPassthrough)
                    return;
            }
        }
        else
        {
            serialInBuff[serialInBuffLen++] = c;
            // if the buffer fills without getting a newline, just reset
            if (serialInBuffLen >= sizeof(serialInBuff))
                serialInBuffLen = 0;
        }
    }  /* while Serial */
}

static void checkSerialInPassthrough()
{
    static uint32_t lastData = 0;
    static bool LED = false;
    bool gotData = false;
    unsigned int avail;
    while ((avail = Serial.available()) != 0)
    {
        uint8_t buf[16];
        avail = Serial.readBytes((char *)buf, min(sizeof(buf), avail));
        crsf.write(buf, avail);
        LED ? led_on() : led_off();
        LED = !LED;
        gotData = true;
    }
    // If longer than X seconds since last data, switch out of passthrough
    if (gotData || !lastData)
        lastData = millis();

    // Turn off LED 1s after last data
    else if (LED && (millis() - lastData > 1000))
    {
        LED = false;
        led_off();
    }

    // Short blink LED after timeout
    else if (millis() - lastData > 5000)
    {
        lastData = 0;
        led_on();
        delay(200);
        led_off();
        crsf.setPassthroughMode(false);
    }
}

static void checkSerialIn()
{
    if (crsf.getPassthroughMode())
        checkSerialInPassthrough();
    else
        checkSerialInNormal();
}

#ifdef BLINK_ENABLED
void led_loop() {
  ms_curr = millis();
  // link is down
  if(!crsf.isLinkUp()) {
    // within the blink routine window (BLINK_TIME)
    if(ms_curr < (ms_last_link_changed + BLINK_TIME)) {
      // handle led toggle delay
      if(ms_curr > (ms_last_led_changed + BLINK_DELAY)) {
        ms_last_led_changed = ms_curr;
        led_state ? led_on() : led_off();
        led_state = !led_state;  // toggle led state
      }
    }
    else
    {
      // ensure the led is off if the blink routine expired and link is down
      led_off();
    }
  }
}
#endif

void setup()
{
    Serial.begin(115200);
    boardSetup();
    crsfLinkDown();

    gamepad.send_update();

    // Attach the channels callback
    crsf.onPacketChannels = &packetChannels;
    crsf.onLinkUp = &crsfLinkUp;
    crsf.onLinkDown = &crsfLinkDown;
    crsf.onOobData = &crsfOobData;
    crsf.begin();
}

void loop()
{
    // Must call CrsfSerial.loop() in loop() to process data
    crsf.loop();
    checkSerialIn();
    #ifdef BLINK_ENABLED
    led_loop();
    #endif
}