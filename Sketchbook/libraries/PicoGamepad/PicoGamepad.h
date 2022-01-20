/*
 * Copyright (c) 2018-2019, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PicoGamepad_H
#define PicoGamepad_H

#include "PluggableUSBHID.h"
#include "platform/Stream.h"
#include "PlatformMutex.h"

// values addresses
#define BTN0_7 0
#define BTN8_15 1
#define BTN16_23 2
#define BTN24_31 3
#define BTN32_39 4
#define BTN40_47 5
#define BTN48_55 6
#define BTN56_63 7
#define BTN64_71 8
#define BTN72_79 9
#define BTN80_87 10
#define BTN88_95 11
#define BTN96_103 12
#define BTN104_111 13
#define BTN112_119 14
#define BTN120_127 15

#define X_AXIS_LSB 16
#define X_AXIS_MSB 17
#define Y_AXIS_LSB 18
#define Y_AXIS_MSB 19

#define HAT0_1 20 // Hats are 4 bit direction (0-9), 2 hats per byte
#define HAT2_3 21

#define Z_AXIS_LSB 22
#define Z_AXIS_MSB 23
#define Rx_AXIS_LSB 24
#define Rx_AXIS_MSB 25
#define Ry_AXIS_LSB 26
#define Ry_AXIS_MSB 27
#define Rz_AXIS_LSB 28
#define Rz_AXIS_MSB 29

#define THROTTLE_AXIS_LSB 30
#define THROTTLE_AXIS_MSB 31
// #define S0_AXIS_LSB 30
// #define S0_AXIS_MSB 31
#define S0_AXIS_LSB 32
#define S0_AXIS_MSB 33

#define HAT_DIR_N 0
#define HAT_DIR_NE 1
#define HAT_DIR_E 2
#define HAT_DIR_SE 3
#define HAT_DIR_S 4
#define HAT_DIR_SW 5
#define HAT_DIR_W 6
#define HAT_DIR_NW 7
#define HAT_DIR_C 8

namespace arduino
{

    class PicoGamepad : public USBHID
    {
    public:
        // Array of 8 bit values which holds all inputs to be passed via HID

        /**
    * Basic constructor
    *
    * Construct this object optionally connecting and blocking until it is ready.
    *
    * @note Do not use this constructor in derived classes.
    *
    * @param connect_blocking true to perform a blocking connect, false to start in a disconnected state
    * @param vendor_id Your vendor_id
    * @param product_id Your product_id
    * @param product_release Your product_release
    */
        PicoGamepad(bool connect_blocking = true, uint16_t vendor_id = 0x1235, uint16_t product_id = 0x0050, uint16_t product_release = 0x0001);

        /**
    * Fully featured constructor
    *
    * Construct this object with the supplied USBPhy and parameters. The user
    * this object is responsible for calling connect() or init().
    *
    * @note Derived classes must use this constructor and call init() or
    * connect() themselves. Derived classes should also call deinit() in
    * their destructor. This ensures that no interrupts can occur when the
    * object is partially constructed or destroyed.
    *
    * @param phy USB phy to use
    * @param vendor_id Your vendor_id
    * @param product_id Your product_id
    * @param product_release Your product_release
    */
        PicoGamepad(USBPhy *phy, uint16_t vendor_id = 0x1235, uint16_t product_id = 0x0050, uint16_t product_release = 0x0001);

        /**
     * Destroy this object
     *
     * Any classes which inherit from this class must call deinit
     * before this destructor runs.
     */
        virtual ~PicoGamepad();

        /**
    * To send a character defined by a modifier(CTRL, SHIFT, ALT) and the key
    *
    * @code
    * //To send CTRL + s (save)
    *  keyboard.key_code('s', KEY_CTRL);
    * @endcode
    *
    * @param modifier bit 0: KEY_CTRL, bit 1: KEY_SHIFT, bit 2: KEY_ALT (default: 0)
    * @param key character to send
    * @returns true if there is no error, false otherwise
    */

        bool send_inputs(uint8_t *values);

        bool test_send(uint16_t b0, uint16_t b1, uint16_t b2, uint16_t b3, uint16_t b4, uint16_t b5, uint16_t b6, uint16_t b7,
                       uint16_t x, uint16_t y, uint16_t hats, uint16_t z, uint16_t Rx, uint16_t Ry, uint16_t Rz, uint16_t s0, uint16_t s1);

        bool randomizeInputs();

        void SetButton(int idx, bool val);
        void SetX(uint16_t val);
        void SetY(uint16_t val);
        void SetZ(uint16_t val);
        void SetRx(uint16_t val);
        void SetRy(uint16_t val);
        void SetRz(uint16_t val);
        void SetS0(uint16_t val);
        void SetThrottle(uint16_t val);
        void SetS1(uint16_t val);

        // 4 Hats available 0-3, direction is clockwise 0=N 1=NE 2=E 3=SE 4=S 5=SW 6=W 7=NW 8=CENTER
        void SetHat(uint8_t hatIdx, uint8_t dir);

        bool send_update();
        /*
    * To define the report descriptor. Warning: this method has to store the length of the report descriptor in reportLength.
    *
    * @returns pointer to the report descriptor
    */
        virtual const uint8_t *report_desc();

    protected:
        /*
    * Get configuration descriptor
    *
    * @returns pointer to the configuration descriptor
    */
        virtual const uint8_t *configuration_desc(uint8_t index);

    private:
        uint8_t inputArray[35];

        uint8_t _configuration_descriptor[41];
        PlatformMutex _mutex;
    };
}

#endif
