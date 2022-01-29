EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L pico:pico U1
U 1 1 61F24CE6
P 2750 2450
F 0 "U1" H 2750 3665 50  0000 C CNN
F 1 "pico" H 2750 3574 50  0000 C CNN
F 2 "pico:pico_no_swd" H 2550 3550 50  0001 C CNN
F 3 "" H 2550 3550 50  0001 C CNN
	1    2750 2450
	1    0    0    -1  
$EndComp
$Comp
L pico:level_converter U2
U 1 1 61F26C7D
P 3900 1750
F 0 "U2" H 3900 2265 50  0000 C CNN
F 1 "level_converter" H 3900 2174 50  0000 C CNN
F 2 "pico:level_converter" H 3900 2200 50  0001 C CNN
F 3 "" H 3900 2200 50  0001 C CNN
	1    3900 1750
	1    0    0    -1  
$EndComp
$Comp
L pico:CRSF_RX U3
U 1 1 61F27D36
P 5400 1600
F 0 "U3" H 5528 1651 50  0000 L CNN
F 1 "CRSF_RX" H 5528 1560 50  0000 L CNN
F 2 "pico:ELRS_EP2" H 5350 1850 50  0001 C CNN
F 3 "" H 5350 1850 50  0001 C CNN
	1    5400 1600
	1    0    0    -1  
$EndComp
Text GLabel 3100 1500 2    50   Input ~ 0
5V
Text GLabel 4200 1700 2    50   Input ~ 0
5V
Text GLabel 5200 1550 0    50   Input ~ 0
5V
Text GLabel 5200 1450 0    50   Input ~ 0
GND
Text GLabel 3100 1700 2    50   Input ~ 0
GND
Text GLabel 3600 1800 0    50   Input ~ 0
GND
Text GLabel 4200 1800 2    50   Input ~ 0
GND
Text GLabel 3100 2200 2    50   Input ~ 0
GND
Text GLabel 3100 2700 2    50   Input ~ 0
GND
Text GLabel 3100 3200 2    50   Input ~ 0
GND
Text GLabel 2400 3200 0    50   Input ~ 0
GND
Text GLabel 2400 2700 0    50   Input ~ 0
GND
Text GLabel 2400 2200 0    50   Input ~ 0
GND
Text GLabel 2400 1700 0    50   Input ~ 0
GND
Text GLabel 3100 1900 2    50   Input ~ 0
3v3
Text GLabel 3600 1700 0    50   Input ~ 0
3v3
Text GLabel 2400 2000 0    50   Input ~ 0
TX
Text GLabel 2400 2100 0    50   Input ~ 0
RX
Text GLabel 3600 1500 0    50   Input ~ 0
TX
Text GLabel 3600 1600 0    50   Input ~ 0
RX
Text GLabel 4200 1500 2    50   Input ~ 0
CRSF_RX
Text GLabel 5200 1750 0    50   Input ~ 0
CRSF_RX
Text GLabel 5200 1650 0    50   Input ~ 0
CRSF_TX
Text GLabel 4200 1600 2    50   Input ~ 0
CRSF_TX
$Comp
L pico:CRSF_RX U4
U 1 1 61F31356
P 5400 2100
F 0 "U4" H 5528 2151 50  0000 L CNN
F 1 "CRSF_RX" H 5528 2060 50  0000 L CNN
F 2 "pico:ELRS_EP2" H 5350 2350 50  0001 C CNN
F 3 "" H 5350 2350 50  0001 C CNN
	1    5400 2100
	1    0    0    -1  
$EndComp
Text GLabel 5200 1950 0    50   Input ~ 0
GND
Text GLabel 5200 2050 0    50   Input ~ 0
5V
Text GLabel 5200 2150 0    50   Input ~ 0
CRSF_TX
Text GLabel 5200 2250 0    50   Input ~ 0
CRSF_RX
$Comp
L Mechanical:MountingHole H1
U 1 1 61F325CD
P 850 1750
F 0 "H1" H 950 1796 50  0000 L CNN
F 1 "MountingHole" H 950 1705 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 850 1750 50  0001 C CNN
F 3 "~" H 850 1750 50  0001 C CNN
	1    850  1750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 61F328A9
P 850 1950
F 0 "H2" H 950 1996 50  0000 L CNN
F 1 "MountingHole" H 950 1905 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 850 1950 50  0001 C CNN
F 3 "~" H 850 1950 50  0001 C CNN
	1    850  1950
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 61F32A3B
P 850 2150
F 0 "H3" H 950 2196 50  0000 L CNN
F 1 "MountingHole" H 950 2105 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 850 2150 50  0001 C CNN
F 3 "~" H 850 2150 50  0001 C CNN
	1    850  2150
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 61F32C8A
P 850 2350
F 0 "H4" H 950 2396 50  0000 L CNN
F 1 "MountingHole" H 950 2305 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 850 2350 50  0001 C CNN
F 3 "~" H 850 2350 50  0001 C CNN
	1    850  2350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
