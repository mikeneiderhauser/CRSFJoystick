#ifndef CALIBRATION
#define CALIBRATION

#define CHANNEL_1_LOW_EP 989
#define CHANNEL_1_HIGH_EP 2011

#define CHANNEL_2_LOW_EP 989
#define CHANNEL_2_HIGH_EP 2011

#define CHANNEL_3_LOW_EP 989
#define CHANNEL_3_HIGH_EP 2011

#define CHANNEL_4_LOW_EP 989
#define CHANNEL_4_HIGH_EP 2011

#define CHANNEL_5_LOW_EP 989
#define CHANNEL_5_HIGH_EP 2011

#define CHANNEL_6_LOW_EP 989
#define CHANNEL_6_HIGH_EP 2011

#define CHANNEL_7_LOW_EP 989
#define CHANNEL_7_HIGH_EP 2011

#define CHANNEL_8_LOW_EP 989
#define CHANNEL_8_HIGH_EP 2011

#define CHANNEL_AUX_SW_LOW 1000
#define CHANNEL_AUX_SW_MID 1510
#define CHANNEL_AUX_SW_HIGH 2011

#define JOYSTICK_LOW (-32767)
#define JOYSTICK_HIGH 32767
#define CHANNEL_AUX_SW_LOW_MAP LOW
#define CHANNEL_AUX_SW_HIGH_MAP HIGH

// upper bound and lower bound constrain where button reports HIGH and is inclusive
// Typically use MID / HIGH
typedef struct btn_config {
    byte channel;
    byte id;
    int lower_bound;
    int upper_bound;
    bool invert;
} btn_config;

#define NUM_BUTTONS 8
btn_config btn_map[NUM_BUTTONS] = {
    {
    5,                    // channel
    0,                    // id
    CHANNEL_AUX_SW_MID,   // lower bound
    CHANNEL_AUX_SW_HIGH,  // upper bound
    false                 // invert
    },

    {
    6,                    // channel
    1,                    // id
    CHANNEL_AUX_SW_MID,   // lower bound
    CHANNEL_AUX_SW_HIGH,  // upper bound
    false                 // invert
    },

    {
    7,                    // channel
    2,                    // id
    CHANNEL_AUX_SW_MID,   // lower bound
    CHANNEL_AUX_SW_HIGH,  // upper bound
    false                 // invert
    },

    {
    8,                    // channel
    3,                    // id
    CHANNEL_AUX_SW_MID,   // lower bound
    CHANNEL_AUX_SW_HIGH,  // upper bound
    false                 // invert
    },

    {
    9,                    // channel
    4,                    // id
    CHANNEL_AUX_SW_MID,   // lower bound
    CHANNEL_AUX_SW_HIGH,  // upper bound
    false                 // invert
    },

    {
    10,                    // channel
    5,                    // id
    CHANNEL_AUX_SW_MID,   // lower bound
    CHANNEL_AUX_SW_HIGH,  // upper bound
    false                 // invert
    },

    {
    11,                    // channel
    6,                    // id
    CHANNEL_AUX_SW_MID,   // lower bound
    CHANNEL_AUX_SW_HIGH,  // upper bound
    false                 // invert
    },

    {
    12,                    // channel
    7,                    // id
    CHANNEL_AUX_SW_MID,   // lower bound
    CHANNEL_AUX_SW_HIGH,  // upper bound
    true                  // invert  - EX FOR INVERT
    }
};

// Channel1 - A
// Channel2 - E 
// Channel3 - T
// Channel4 - R
// Channel5 - Aux 1
// Channel6 - Aux 2
// Channel7 - Aux 3
// Channel8 - Aux 4
// Channel9 - Aux 5
// Channel10 - Aux 6
// Channel11 - Aux 7
// Channel12 - Aux 8
// Channel13
// Channel14
// Channel15 - LQ
// Channel16 - RSSI

#endif