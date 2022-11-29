#ifndef BOARD_DEFS
#define BOARD_DEFS

#define LED_TYPE_SINGLE 1
#define LED_TYPE_NEOPIXEL 2
#define LED_TYPE_RGB 3

// PiPico
#if BOARD_ID == 1
    #define CRSF_TX 4  // physical 6
    #define CRSF_RX 5  // physical 7

    #define LED_TYPE LED_TYPE_SINGLE
    #define LED_PIN 25
    
    void boardSetup() {
      pinMode(LED_PIN,OUTPUT);
    }

    void led_off() {
      digitalWrite(LED_PIN, LOW);
    }
    
    void led_on() {
      digitalWrite(LED_PIN, HIGH);
    }
#endif

// TINY2040
#if BOARD_ID == 2
    #define CRSF_TX 4
    #define CRSF_RX 5

    #define LED_TYPE LED_TYPE_RGB
    #define LED_PIN_R 18
    #define LED_PIN_G 19
    #define LED_PIN_B 20
    
    void boardSetup() {
      pinMode(LED_PIN_R,OUTPUT);
      pinMode(LED_PIN_G,OUTPUT);
      pinMode(LED_PIN_B,OUTPUT);
    }

    void led_off() {
      digitalWrite(LED_PIN_R, HIGH);
      digitalWrite(LED_PIN_G, HIGH);
      digitalWrite(LED_PIN_B, HIGH);
    }
    
    void led_on() {
      digitalWrite(LED_PIN_R, HIGH);
      digitalWrite(LED_PIN_G, HIGH);
      digitalWrite(LED_PIN_B, LOW);
    }
#endif

// WaveShare RP2040-Zero
#if BOARD_ID == 3
    #define CRSF_TX 4
    #define CRSF_RX 5

    #define LED_TYPE LED_TYPE_NEOPIXEL
    #define LED_PIN 16

    #include <Adafruit_NeoPixel.h>
    Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);
    
    void boardSetup() {
      // noop
    }

    void led_off() {
      pixels.setPixelColor(0, pixels.Color(0,0,0));
      pixels.show();
    }
    
    void led_on() {
      pixels.setPixelColor(0, pixels.Color(0,0,255));
      pixels.show();
    }
#endif

// Seeed XAIO 2040
#if BOARD_ID == 4
    #define CRSF_TX 0
    #define CRSF_RX 1

    // 1 NEOPixel - currently unused
    #define LED_TYPE LED_TYPE_NEOPIXEL
    #define LED_NEO_PWR 11
    #define LED_PIN 12

    #include <Adafruit_NeoPixel.h>
    Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);
    
    // 1 Active Low RGB
    //#define LED_ACTIVE_LOW LED_ACTIVE_LOW_TRUE
    //#define LED_TYPE LED_TYPE_RGB
    #define LED_PIN_R 17
    #define LED_PIN_G 16
    #define LED_PIN_B 25

    void boardSetup() {
        // Enable neopixel LED
        pinMode(LED_NEO_PWR, OUTPUT);
        digitalWrite(LED_NEO_PWR,HIGH);
        // Turn off user led
        pinMode(LED_PIN_R,OUTPUT);
        pinMode(LED_PIN_G,OUTPUT);
        pinMode(LED_PIN_B,OUTPUT);
        digitalWrite(LED_PIN_R, HIGH);
        digitalWrite(LED_PIN_G, HIGH);
        digitalWrite(LED_PIN_B, HIGH);
    }

    void led_off() {
      pixels.setPixelColor(0, pixels.Color(0,0,0));
      pixels.show();
    }
    
    void led_on() {
      pixels.setPixelColor(0, pixels.Color(0,0,255));
      pixels.show();
    }
    
#endif

#endif
