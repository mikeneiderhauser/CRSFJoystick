# ELRSJoystick / CRSFJoystick

<https://github.com/mikeneiderhauser/CRSFJoystick>

Named CRSFJoystick as it indicates the wire protocol between the microcontroller (pi pico) and receiver).

Arduino code using the mbed core that runs on a Pi Pico (2040) to emulate a USB HID Joystick

Pirmarily developed to use and ExpressLRS receiver and a HID Joystick for Sim use! It will work with both Tracer and Crossfire as well.

Shout out to CapnBry for the Crsf Library

https://github.com/CapnBry/CRServoF

Shout out to RealRobots.net for the Gamepad Library

https://gitlab.com/realrobots/PicoGamepad/-/tree/master

# Future Plans

- GitHub Builds
- Rework HID USB code
- Add failsafe nopulses / hold

# Demo Video
[![ELRS HID Joystick Demo](https://img.youtube.com/vi/MCOWKvFTHRc/0.jpg)](https://www.youtube.com/watch?v=MCOWKvFTHRc)

## Purchase

Originally offered of FPVExchange, but that is no longer an option. Please send me an email for availability, purchase, or to get additional info!

<housefpv@gmail.com>

You can also contact me on discord [HouseFPV](https://discordapp.com/users/HouseFPV#5899)

- Blank carrier boards for Pi Pico, Tiny 2040, and Waveshare RP2040 (old stock)
- Built and flashed units
- [DIY Section](#diy-hardware)

A few boards that I believe are based off of this project:
- HGLRC Dongle (I have samples from HGLRC on the way)
  - [HGLRC Dongle at HGLRC](https://www.hglrc.com/collections/new-arrivals/products/hglrc-c1-remote-control)
  - [HGLRC C1 Radio Kit with dongle at HGLRC](https://www.hglrc.com/collections/new-arrivals/products/hglrc-c1-remote-control)
  - [HGLRC C1 Radio Kit with dongle at RacedayQuads](https://www.racedayquads.com/products/hglrc-c1-transmitter-elrs-2-4ghz-choose-your-version?keyword=hglrc%20c1)
- Squid Stick (I have personally not tested one)
  -  [Squid Stick at Progressiverc.com](https://www.progressiverc.com/products/squid-stick-elrs-2-4ghz-usb-receiver-module)
  -  Squid Stick at RacedayQuads - Link to be posted when available
- YMZFPV Simulator Adapter (have not yet been able to confirm that this is based off of this project)
  - [YMZFPV Sim Adapter at RacedayQuads](https://www.racedayquads.com/products/ymzfpv-wireless-simulator-adapter-for-sbus-pwm-csfr-choose-your-version?keyword=simulator)


## Compatability

This project was designed primarily with ELRS usage in mind, however this code base has also been tested with TBS Crossfire Receivers (915MHZ) (last tested v6.16) and TBS Tracer Receivers (2.4GHz) (last tested v6.17) and both appear to work! Flight was teseted in the Liftoff simulator.

I no longer have TBS Crossfire nor TBS Tracer TX modules or Receivers so future tests will have to be conducted by others.

### ExpressLRS (Waveshare RP2040)
<img src="./photos/waveshare/WS2040_r_1_1.jpg" width="400" height="400">

### Crossfire

<img src="./photos/tbs/crossfire_dev_board.jpeg" width="400" height="400">

### Tracer
<img src="./photos/tbs/tracer_dev_board.jpeg" width="400" height="400">

# Building / Flashing

I recently converted the projet to PlatformIO to aid in building, board management, etc.  PlatformIO has some known quirks with PiPico boards and I'm going to leave some breadcrumbs here for later.

## VSCode with PlatformIO

### Installing VSCode and PlatformIO
<https://platformio.org/install/ide?install=vscode>

### Build for specific board / environment

At the Bottom of VSCode you will see a tool bar.  Look for `Default (CRSFJoystick)`.  Building in this state will build for all boards / environments defined in the `platformio.ini` file.  To target a sepecific board, Click on `Default (CRSFJoystick)` and select an appropriate option (Note, selection pops up at the top of vscode).

<img src="./photos/screenshots/stock_bottom_bar.png">

Click on the Checkmark on the bottom toolbar to build for the board / environment you selected.

Click on the `->` on the bottom toolbar to upload to the board.  If upload fails to find your board, please see bothe the [alternative upload](#alternative-upload) section as well as the driver section.

## Alternative upload
This is one of the standard advertised methods for uploading firmware to a pipico based microcontroller board.

Press and hold the bootsel button on your board and either plugin/power on the board or if the board is already powered press and release the reset button.

This will put the board in RP2 Boot mode.

A removable device should pop up or become available on your computer.  Drag and drop the `firmware.u2f` file from the `.pio/build/wavesharerp2040zero/` directory into this device on your computer.  Note replpace wavesharerp2040zero with the environment for your board.

## Drivers
Drivers can be hit or miss for the pipico board and platformio.  

You may need to use zadig to get vscode+platforio to be able to upload directly to the board.
<https://github.com/platformio/platform-raspberrypi/issues/2#issuecomment-828586398>

Below are the drivers I have working on my Windows 11 machine.  You may need to modify the driver selection via zadig and or device manager to get it working.

- Standard Running Mode
  - RaspberryPi Pico (Interface 0)
    - Zadig -> HidUsb v10.0.22621.819
    - Device Manager -> Human Interface Devices -> HID-compliant game controller
  - RaspberryPi Pico (Interface 1)
      - Zadig -> usbser v10.0.22621.1778
      - Device Manager -> Ports (COM & LPT) -> USB Serial Device
- RP2 Boot mode
  - RP2 Boot (Interface 0) 
    - Zadig USBSTOR v10.0.022621.1778 
    - Device Manager -> Disk Drives -> RPI RP2 USB Device 
  - RP2 Boot (Interface 1)
    - Zadig WinUSB v6.1.7600.16385
    Device Manager -> Universal Serial Bus Devices -> RP2 Boot

### Device manager clicks to change driver 
Right Click -> Properties -> Update Driver -> Browse my computer for drivers -> Let me pick from a list of available drivers on my computer

# Flashing ELRS Receiver

Depending on the device you are using, your target may be different.  For all of the DIY version's I've made, I used the HappyModel EP2 Rx.  Other vendors may vary.

## Flashing via Betaflight Passthrough
<https://www.expresslrs.org/software/updating/betaflight-passthrough/>

## Flashing via Wifi
If your receiver is wifi enabled you can also flash it via wifi

<https://www.expresslrs.org/software/updating/wifi-updating/>


# Testing
For a quick test of functionality, I typically go to [GamepadTester](https://hardwaretester.com/gamepad).

Once the Radio is bound to the RX, it should show up in GamePadTester.

<img src="./photos/screenshots/gamepadtester.png">


# Mappings
This was a quick map and is not fully featured.

On link up/down the onboard Pi Pico LED will light indicating connection

*NOTE* Channel 5, 6, 7, and 8 are mapped both to analog axis as well as joystick buttons.

| Channel     | Logical Mapping  | Joystick Mapping |
| ----------- | ---------------- | ---------------- |
| 1           | A                | X                |
| 2           | E                | Y                |
| 3           | T                | Rx               |
| 4           | R                | Ry               |
| 5           | Channel 5 (Full) AND AUX1 (1510-2011) | Z  AND Button 0 |
| 6           | Channel 6 (Full) AND AUX2 (1510-2011) | Rz AND Button 1 |
| 7           | Channel 7 (Full) AND AUX3 (1510-2011) | S0 AND Button 2 |
| 8           | Channel 8 (Full) AND AUX4 (1510-2001) | S1 AND Button 3 |
| 9           | AUX5 (1510-2011) | Button 4         |
| 10          | AUX6 (1510-2011) | Button 5         |
| 11          | AUX7 (1510-2011) | Button 6         |
| 12          | AUX8 (1510-2011) | Button 7         |
| 13          | Not Used         | Not Used         |
| 14          | Not Used         | Not Used         |
| 15          | LQ - Not Used    | Not Used         |
| 16          | RSSI - Not Used  | Not Used         |

*Note additional button mappings can be created in caliration.h*


# Here below is for DIY Builds and may be slightly outdated
# DIY Hardware

In a nutshell, wire the ELRS RX up to a uart on the pipico, 5v, and gnd.

| Raspberry Pico | ELRS/CRSF Receiver |
| -------------- | ------------------ |
| VBUS (PIN 40)  | 5V                 |
| GND  (PIN 38)  | GND
| GP4  (PIN 6)   | RX                 |
| GP5  (PIN 7)   | TX                 |

Other boards are supported, see the [board_defs.h](./include/board_defs.h) file.

| Part  | Link | Approx Cost |
| ----- | ---- | ------------|
| Pi Pico | https://www.pishop.us/product/raspberry-pi-pico/ | $4 (Approx $6 with shipping) |
| Waveshare RP2040 zero | https://www.amazon.com/RP2040-Zero-Development-Microcontroller-Multi-Function-Integration/dp/B09SBCKYSC/ref=sr_1_1_sspa?crid=1NDXW0KFV39DX&keywords=waveshare+rp2040+zero&qid=1697989796&sprefix=waveshare+rp2040+zero%2Caps%2C66&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1| $10|
| Tiny 2040 (alt part) | https://www.pishop.us/product/tiny-2040/ | $10 (Approx $12 with shipping) |
| ELRS RX (any will do) |  https://www.racedayquads.com/products/happymodel-2-4ghz-ep2-tcxo-rx-express-lrs-receiver?keyword=expresslrs | $18 |

Note, price breaks can be had when purchasing at quantity.

Approx part cost for pico hardware (large footprint, cheaper) - $20-$25

- Pi Pico - $4.00
- ELRS RX - $13.50 
- Carrier Board - $1.00 (approx)
- Shipping / Tax from vendors - varies

# Carrier Boards

## ELRSJoystick

This board has an ELRS RX built in, so you don't need to wire any RX on, just plug in and connect to your ELRS TX, then you are ready to go!

![](./photos/ELRSJoystick/1.png)
![](./photos/ELRSJoystick/2.png)
![](./photos/ELRSJoystick/3.png)
![](./photos/ELRSJoystick/4.png)
![](./photos/ELRSJoystick/5.png)
![](./photos/ELRSJoystick/6.png)
![](./photos/ELRSJoystick/7.png)

## Tiny Version

> **_NOTE:_** References to level shifters below are no longer needed as the level shifter can be omitted. You will have to bridge the pads on the level shifter for the TX/RX pins or use a newer version of the carrier board.

I personally use the Waveshare RP2040-Zero version for my ELRS Joystick!

Hardware build files are located in hardware/kicad/CRSFJoystick/output/Rev1.0

I used JLCPCB with Black Soldermask and a board thickness of 1.6mm.

![R1.0 Build Photo](./photos/r1.0_build.jpeg)

Note the different orientation of the ELRS RX's.  The orientation can be flipped.  I installed each RX to ensure the boot pad is exposed should the RX need recovered.

## Waveshare RP2040-Zero

[WaveShare RP2040-Zero Board](https://www.waveshare.com/rp2040-zero.htm)

![WaveShare RP2040-Zero BoardDimensions](./photos/waveshare/board_kicad_dimensions.png)

![WaveShare RP2040 Case lower](./photos/waveshare/WS2040_lower.jpg)

![WaveShare RP2040 Case Upper](./photos/waveshare/WS2040_upper.jpg)

![WaveShare RP2040 Case assembled](./photos/waveshare/WS2040_case.jpg)

## Raspberry Pi Pico (Full Version)

![Pico Build Front](./photos/pico/board_r1.0_front.jpeg)

![Pico Build Back](./photos/pico/board_r1.0_back.jpeg)

![Pi Pico Dimensions](./photos/pico/board_kicad_dimensions.png)

## Tiny2040

![Tiny2040 Build Front](./photos/tiny/board_r1.0_front.jpeg)

![Tiny2040 Build Back](./photos/tiny/board_r1.0_back.jpeg)

![Tiny2040 Dimensions](./photos/tiny/board_kicad_dimensions.png)

## SEEED AXIO 2040

Board files now in the hardware folder.  Not built or tested but should work.

![SEEED XAIO RP2040 Dimensions](./photos/xiao/board_kicad_dimensions.png)

[SEEED XAIO RP2040 Board](https://www.seeedstudio.com/XIAO-RP2040-v1-0-p-5026.html)


## CRSFJoystick2.0

Build a smaller pico by yourself.

![CRSFJoystick2.3 Board Front](./photos/CRSFJoystick2.0/board_v2.3_front.JPG)
![CRSFJoystick2.3 Board Back](./photos/CRSFJoystick2.0/board_v2.3_back.JPG)
![CRSFJoystick2.3 Render Front](./photos/CRSFJoystick2.0/board_v2.3_render_front.png)
![CRSFJoystick2.3 Render Back](./photos/CRSFJoystick2.0/board_v2.3_render_back.png)
![CRSFJoystick2.3 Render Back](./photos/CRSFJoystick2.0/1.png)
![CRSFJoystick2.3 Render Back](./photos/CRSFJoystick2.0/2.png)
![CRSFJoystick2.3 Render Back](./photos/CRSFJoystick2.0/3.png)
![CRSFJoystick2.3 Render Back](./photos/CRSFJoystick2.0/4.png)
![CRSFJoystick2.3 Render Back](./photos/CRSFJoystick2.0/5.png)
![CRSFJoystick2.3 Render Back](./photos/CRSFJoystick2.0/6.png)
![CRSFJoystick2.3 Render Back](./photos/CRSFJoystick2.0/7.png)

# General Assembly

- Print the top and bottom enclosure
- Print 2 of the spacers for the Pi2040, Print 4 of the spacers for the Pi Pico version
- Follow the directions in this video https://youtu.be/Zuhfbobgm5A
