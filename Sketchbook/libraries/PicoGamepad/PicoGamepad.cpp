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

#include "stdint.h"
#include "PluggableUSBHID.h"
#include "PicoGamepad.h"
#include "usb_phy_api.h"

#define REPORT_ID_KEYBOARD 1
#define REPORT_ID_VOLUME 3

using namespace arduino;

//uint8_t inputArray[35];

PicoGamepad::PicoGamepad(bool connect, uint16_t vendor_id, uint16_t product_id, uint16_t product_release) : USBHID(get_usb_phy(), 0, 0, vendor_id, product_id, product_release)
{
    //_lock_status = 0;
    for (int i = 0; i < 4; i++)
    {
        SetHat(i, HAT_DIR_C);
    }
}

PicoGamepad::PicoGamepad(USBPhy *phy, uint16_t vendor_id, uint16_t product_id, uint16_t product_release) : USBHID(phy, 0, 0, vendor_id, product_id, product_release)
{
    //_lock_status = 0;
    for (int i = 0; i < 4; i++)
    {
        SetHat(i, HAT_DIR_C);
    }
    // User or child responsible for calling connect or init
}

PicoGamepad::~PicoGamepad()
{
    // for (int i = 0; i < 35; i++)
    // {
    //     inputArray[i] = 0;
    // }
    for (int i = 0; i < 4; i++)
    {
        SetHat(i, HAT_DIR_C);
    }
}

const uint8_t *PicoGamepad::report_desc()
{
    static const uint8_t reportDescriptor[] = {
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x04, // USAGE (Gamepad)
        0xa1, 0x01, // COLLECTION (Application)
        0x85, 0x01, //   REPORT_ID (1)

        0x05, 0x09, // USAGE_PAGE (Button)
        0x19, 0x01, // USAGE_MINIMUM (Button 1)
        0x29, 0x80, // USAGE_MAXIMUM (Button 128)
        0x15, 0x00, // LOGICAL_MINIMUM (0)
        0x25, 0x01, // LOGICAL_MAXIMUM (1)
        0x95, 0x80, // REPORT_COUNT (128)
        0x75, 0x01, // REPORT_SIZE (1)
        0x81, 0x02, // INPUT (Data,Var,Abs)

        0x05, 0x01,       // USAGE_PAGE (Generic Desktop) // analog axes
        0x09, 0x30,       // USAGE (X)
        0x09, 0x31,       // USAGE (Y)
        0x16, 0x01, 0x80, //LOGICAL_MINIMUM (-32767)
        0x26, 0xFF, 0x7F, //LOGICAL_MAXIMUM (32767)
        0x75, 0x10,       //     REPORT_SIZE (16)
        0x95, 0x02,       // REPORT_COUNT (2)
        0x81, 0x02,       // INPUT (Data,Var,Abs)

        0x09, 0x39,     // USAGE (HATSWITCH)
        0x15, 0x00,     // LOGICAL_MINIMUM (0)
        0x25, 0x07,     // LOGICAL_MAXIMUM (7)
        0x35, 0x00,     // PHYSICAL_MINIMUM (0)
        0x46, 0x38, 01, // PHYSICAL_MAXIMUM (315)
        0x65, 0x14,     // UNIT (Eng Rot:Angular Pos)
        0x75, 0x04,     // REPORT_SIZE (4)
        0x95, 0x01,     // REPORT_COUNT (1)
        0x81, 0x02,     // INPUT(Data, Var, Abs)

        0x09, 0x39,     // USAGE (HATSWITCH)
        0x15, 0x00,     // LOGICAL_MINIMUM (0)
        0x25, 0x07,     // LOGICAL_MAXIMUM (7)
        0x35, 0x00,     // PHYSICAL_MINIMUM (0)
        0x46, 0x38, 01, // PHYSICAL_MAXIMUM (315)
        0x65, 0x14,     // UNIT (Eng Rot:Angular Pos)
        0x75, 0x04,     // REPORT_SIZE (4)
        0x95, 0x01,     // REPORT_COUNT (1)
        0x81, 0x02,     // INPUT(Data, Var, Abs)

        0x09, 0x39,     // USAGE (HATSWITCH)
        0x15, 0x00,     // LOGICAL_MINIMUM (0)
        0x25, 0x07,     // LOGICAL_MAXIMUM (7)
        0x35, 0x00,     // PHYSICAL_MINIMUM (0)
        0x46, 0x38, 01, // PHYSICAL_MAXIMUM (315)
        0x65, 0x14,     // UNIT (Eng Rot:Angular Pos)
        0x75, 0x04,     // REPORT_SIZE (4)
        0x95, 0x01,     // REPORT_COUNT (1)
        0x81, 0x02,     // INPUT(Data, Var, Abs)

        0x09, 0x39,     // USAGE (HATSWITCH)
        0x15, 0x00,     // LOGICAL_MINIMUM (0)
        0x25, 0x07,     // LOGICAL_MAXIMUM (7)
        0x35, 0x00,     // PHYSICAL_MINIMUM (0)
        0x46, 0x38, 01, // PHYSICAL_MAXIMUM (315)
        0x65, 0x14,     // UNIT (Eng Rot:Angular Pos)
        0x75, 0x04,     // REPORT_SIZE (4)
        0x95, 0x01,     // REPORT_COUNT (1)
        0x81, 0x02,     // INPUT(Data, Var, Abs)

        0x09, 0x32,       // USAGE (Z)
        0x09, 0x33,       // USAGE (Rx)
        0x09, 0x34,       // USAGE (Ry)
        0x09, 0x35,       // USAGE (Rz)   //36-37=steering s0
        0x16, 0x01, 0x80, //LOGICAL_MINIMUM (-32767)
        0x26, 0xFF, 0x7F, //LOGICAL_MAXIMUM (32767)
        0x75, 0x10,       //     REPORT_SIZE (16)
        0x95, 0x04,       //     REPORT_COUNT (4)
        0x81, 0x02,       //     INPUT (Data, Variable, Absolute) ;20 bytes (slider 1 and slider 2)

        0x05, 0x02, //   USAGE_PAGE (Simulation Controls)
        0x09, 0xBB, //   USAGE (Throttle)
        0x16, 0x01, 0x80, //LOGICAL_MINIMUM (-32767)
        0x26, 0xFF, 0x7F, //LOGICAL_MAXIMUM (32767)
        0x75, 0x10,       //     REPORT_SIZE (16)
        0x95, 0x01,       //     REPORT_COUNT (2)
        0x81, 0x02,                    //   INPUT (Data,Var,Abs)

        0x05, 0x01,       // USAGE_PAGE (Generic Desktop) // analog axes
        0x09, 0x36, //   USAGE (Slider)
        0x16, 0x01, 0x80, //LOGICAL_MINIMUM (-32767)
        0x26, 0xFF, 0x7F, //LOGICAL_MAXIMUM (32767)
        0x75, 0x10,       //     REPORT_SIZE (16)
        0x95, 0x01,       //     REPORT_COUNT (2)
        0x81, 0x02,                    //   INPUT (Data,Var,Abs)

        0xc0 // END_COLLECTION

    };
    reportLength = sizeof(reportDescriptor);
    return reportDescriptor;
}

bool PicoGamepad::randomizeInputs()
{
    _mutex.lock();

    HID_REPORT report;
    report.data[0] = 0x01;
    for (int i = 1; i < 36; i++)
    {
        report.data[i] = random();
    }
    report.length = 35;

    if (!send(&report))
    {
        _mutex.unlock();
        return false;
    }

    _mutex.unlock();
    return true;
}

void PicoGamepad::SetButton(int idx, bool val)
{
    if (idx > 128 || idx < 0)
    {
        return;
    }
    bitWrite(inputArray[idx / 8], idx % 8, val);
}

void PicoGamepad::SetX(uint16_t val)
{
    inputArray[X_AXIS_LSB] = LSB(val);
    inputArray[X_AXIS_MSB] = MSB(val);
}

void PicoGamepad::SetY(uint16_t val)
{
    inputArray[Y_AXIS_LSB] = LSB(val);
    inputArray[Y_AXIS_MSB] = MSB(val);
}

void PicoGamepad::SetZ(uint16_t val)
{
    inputArray[Z_AXIS_LSB] = LSB(val);
    inputArray[Z_AXIS_MSB] = MSB(val);
}

void PicoGamepad::SetRx(uint16_t val)
{
    inputArray[Rx_AXIS_LSB] = LSB(val);
    inputArray[Rx_AXIS_MSB] = MSB(val);
}

void PicoGamepad::SetRy(uint16_t val)
{
    inputArray[Ry_AXIS_LSB] = LSB(val);
    inputArray[Ry_AXIS_MSB] = MSB(val);
}

void PicoGamepad::SetRz(uint16_t val)
{
    inputArray[Rz_AXIS_LSB] = LSB(val);
    inputArray[Rz_AXIS_MSB] = MSB(val);
}

void PicoGamepad::SetThrottle(uint16_t val)
{
    inputArray[THROTTLE_AXIS_LSB] = LSB(val);
    inputArray[THROTTLE_AXIS_MSB] = MSB(val);
}

void PicoGamepad::SetS0(uint16_t val)
{
    inputArray[THROTTLE_AXIS_LSB] = LSB(val);
    inputArray[THROTTLE_AXIS_MSB] = MSB(val);
}

void PicoGamepad::SetS1(uint16_t val)
{
    inputArray[S0_AXIS_LSB] = LSB(val);
    inputArray[S0_AXIS_MSB] = MSB(val);
}


void PicoGamepad::SetHat(uint8_t hatIdx, uint8_t dir)
{
    uint8_t hatDir[9][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 1, 0, 0},
        {0, 1, 0, 1},
        {0, 1, 1, 0},
        {0, 1, 1, 1},
        {1, 0, 0, 0}};
    switch (hatIdx)
    {
    case 0:
        for (int i = 0; i < 4; i++)
        {
            bitWrite(inputArray[HAT0_1], 3 - i, hatDir[dir][i]);
        }
        break;
    case 1:
        for (int i = 0; i < 4; i++)
        {
            bitWrite(inputArray[HAT0_1], 7 - i, hatDir[dir][i]);
        }
        break;
    case 2:
        for (int i = 0; i < 4; i++)
        {
            bitWrite(inputArray[HAT2_3], 3 - i, hatDir[dir][i]);
        }
        break;
    case 3:
        for (int i = 0; i < 4; i++)
        {
            bitWrite(inputArray[HAT2_3], 7 - i, hatDir[dir][i]);
        }
        break;
    }
}

bool PicoGamepad::send_update()
{
    _mutex.lock();

    HID_REPORT report;
    report.data[0] = 0x01;
    for (int i = 1; i < 36; i++)
    {
        report.data[i] = inputArray[i - 1];
    }

    report.length = 35;

    if (!send(&report))
    {
        _mutex.unlock();
        return false;
    }

    _mutex.unlock();
    return true;
}

bool PicoGamepad::send_inputs(uint8_t *values)
{
    _mutex.lock();

    HID_REPORT report;
    report.data[0] = 0x01;
    for (int i = 1; i < 36; i++)
    {
        report.data[i] = values[i - 1];
    }

    report.length = 35;

    if (!send(&report))
    {
        _mutex.unlock();
        return false;
    }

    _mutex.unlock();
    return true;
}

bool PicoGamepad::test_send(uint16_t b0, uint16_t b1, uint16_t b2, uint16_t b3, uint16_t b4, uint16_t b5, uint16_t b6, uint16_t b7,
                            uint16_t x, uint16_t y, uint16_t hats, uint16_t z, uint16_t Rx, uint16_t Ry, uint16_t Rz, uint16_t s0, uint16_t s1)
{
    _mutex.lock();

    HID_REPORT report;

    report.data[0] = 0x01;
    report.data[1] = LSB(b0);
    report.data[2] = MSB(b0);
    report.data[3] = LSB(b1);
    report.data[4] = MSB(b1);
    report.data[5] = LSB(b2);
    report.data[6] = MSB(b2);
    report.data[7] = LSB(b3);
    report.data[8] = MSB(b3);
    report.data[9] = LSB(b4);
    report.data[10] = MSB(b4);
    report.data[11] = LSB(b5);
    report.data[12] = MSB(b5);
    report.data[13] = LSB(b6);
    report.data[14] = MSB(b6);
    report.data[15] = LSB(b7);
    report.data[16] = MSB(b7);
    report.data[17] = LSB(x);
    report.data[18] = MSB(x);
    report.data[19] = LSB(y);
    report.data[20] = MSB(y);
    report.data[21] = LSB(hats);
    report.data[22] = MSB(hats);
    report.data[23] = LSB(z);
    report.data[24] = MSB(z);
    report.data[25] = LSB(Rx);
    report.data[26] = MSB(Rx);
    report.data[27] = LSB(Ry);
    report.data[28] = MSB(Ry);
    report.data[29] = LSB(Rz);
    report.data[30] = MSB(Rz);
    report.data[31] = LSB(s0);
    report.data[32] = MSB(s0);
    report.data[33] = LSB(s1);
    report.data[34] = MSB(s1);

    report.length = 35;

    if (!send(&report))
    {
        _mutex.unlock();
        return false;
    }

    _mutex.unlock();
    return true;
}

#define DEFAULT_CONFIGURATION (1)
#define TOTAL_DESCRIPTOR_LENGTH ((1 * CONFIGURATION_DESCRIPTOR_LENGTH) + (1 * INTERFACE_DESCRIPTOR_LENGTH) + (1 * HID_DESCRIPTOR_LENGTH) + (2 * ENDPOINT_DESCRIPTOR_LENGTH))

const uint8_t *PicoGamepad::configuration_desc(uint8_t index)
{
    if (index != 0)
    {
        return NULL;
    }
    uint8_t configuration_descriptor_temp[] = {
        CONFIGURATION_DESCRIPTOR_LENGTH, // bLength
        CONFIGURATION_DESCRIPTOR,        // bDescriptorType
        LSB(TOTAL_DESCRIPTOR_LENGTH),    // wTotalLength (LSB)
        MSB(TOTAL_DESCRIPTOR_LENGTH),    // wTotalLength (MSB)
        0x01,                            // bNumInterfaces
        DEFAULT_CONFIGURATION,           // bConfigurationValue
        0x00,                            // iConfiguration
        C_RESERVED | C_SELF_POWERED,     // bmAttributes
        C_POWER(0),                      // bMaxPower

        INTERFACE_DESCRIPTOR_LENGTH, // bLength
        INTERFACE_DESCRIPTOR,        // bDescriptorType
        0x00,                        // bInterfaceNumber
        0x00,                        // bAlternateSetting
        0x02,                        // bNumEndpoints
        HID_CLASS,                   // bInterfaceClass
        HID_SUBCLASS_BOOT,           // bInterfaceSubClass
        HID_PROTOCOL_KEYBOARD,       // bInterfaceProtocol
        0x00,                        // iInterface

        HID_DESCRIPTOR_LENGTH,                // bLength
        HID_DESCRIPTOR,                       // bDescriptorType
        LSB(HID_VERSION_1_11),                // bcdHID (LSB)
        MSB(HID_VERSION_1_11),                // bcdHID (MSB)
        0x00,                                 // bCountryCode
        0x01,                                 // bNumDescriptors
        REPORT_DESCRIPTOR,                    // bDescriptorType
        (uint8_t)(LSB(report_desc_length())), // wDescriptorLength (LSB)
        (uint8_t)(MSB(report_desc_length())), // wDescriptorLength (MSB)

        ENDPOINT_DESCRIPTOR_LENGTH, // bLength
        ENDPOINT_DESCRIPTOR,        // bDescriptorType
        _int_in,                    // bEndpointAddress
        E_INTERRUPT,                // bmAttributes
        LSB(MAX_HID_REPORT_SIZE),   // wMaxPacketSize (LSB)
        MSB(MAX_HID_REPORT_SIZE),   // wMaxPacketSize (MSB)
        1,                          // bInterval (milliseconds)

        ENDPOINT_DESCRIPTOR_LENGTH, // bLength
        ENDPOINT_DESCRIPTOR,        // bDescriptorType
        _int_out,                   // bEndpointAddress
        E_INTERRUPT,                // bmAttributes
        LSB(MAX_HID_REPORT_SIZE),   // wMaxPacketSize (LSB)
        MSB(MAX_HID_REPORT_SIZE),   // wMaxPacketSize (MSB)
        1,                          // bInterval (milliseconds)
    };
    MBED_ASSERT(sizeof(configuration_descriptor_temp) == sizeof(_configuration_descriptor));
    memcpy(_configuration_descriptor, configuration_descriptor_temp, sizeof(_configuration_descriptor));
    return _configuration_descriptor;
}
