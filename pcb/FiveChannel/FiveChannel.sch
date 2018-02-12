EESchema Schematic File Version 2
LIBS:FiveChannel-rescue
LIBS:advent_sternla_attiny1614_symbols
LIBS:SensorBoard
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title "Advent Sternal - NeoPixel Driver"
Date "2017-10-25"
Rev "2L_1"
Comp "SM"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATTINY1614 U102
U 1 1 59EF6A42
P 5600 4400
F 0 "U102" H 6150 3600 60  0000 C CNN
F 1 "ATTINY1614" H 5650 4350 60  0000 C CNN
F 2 "SMD_Packages:SOIC-14_N" H 5450 4450 60  0001 C CNN
F 3 "" H 5450 4450 60  0001 C CNN
	1    5600 4400
	1    0    0    -1  
$EndComp
$Comp
L R R101
U 1 1 59EF6A7A
P 4600 4050
F 0 "R101" V 4680 4050 50  0000 C CNN
F 1 "47kΩ" V 4600 4050 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4530 4050 50  0001 C CNN
F 3 "" H 4600 4050 50  0001 C CNN
F 4 "Value" H 4600 4050 60  0001 C CNN "Link"
	1    4600 4050
	-1   0    0    1   
$EndComp
Text Label 4000 3850 0    60   ~ 0
VDD
$Comp
L GND #PWR01
U 1 1 59EF6C0B
P 5600 5550
F 0 "#PWR01" H 5600 5300 50  0001 C CNN
F 1 "GND" H 5600 5400 50  0000 C CNN
F 2 "" H 5600 5550 50  0001 C CNN
F 3 "" H 5600 5550 50  0001 C CNN
	1    5600 5550
	1    0    0    -1  
$EndComp
Text Label 3800 4300 0    60   ~ 0
PDI_DATA
Text Label 1050 1350 0    60   ~ 0
PDI_DATA
$Comp
L GND #PWR02
U 1 1 59EF6D08
P 2250 1750
F 0 "#PWR02" H 2250 1500 50  0001 C CNN
F 1 "GND" H 2250 1600 50  0000 C CNN
F 2 "" H 2250 1750 50  0001 C CNN
F 3 "" H 2250 1750 50  0001 C CNN
	1    2250 1750
	1    0    0    -1  
$EndComp
Text Label 2450 1350 2    60   ~ 0
VDD
$Comp
L GND #PWR03
U 1 1 59EF8502
P 2550 4900
F 0 "#PWR03" H 2550 4650 50  0001 C CNN
F 1 "GND" H 2550 4750 50  0000 C CNN
F 2 "" H 2550 4900 50  0001 C CNN
F 3 "" H 2550 4900 50  0001 C CNN
	1    2550 4900
	1    0    0    -1  
$EndComp
$Comp
L Conn_02x03_Odd_Even J101
U 1 1 59EF854F
P 1700 1450
F 0 "J101" H 1750 1650 50  0000 C CNN
F 1 "UPDI" H 1750 1250 50  0000 C CNN
F 2 "advent_sternla:PRG_TC2030-IDC-NL" H 1700 1450 50  0001 C CNN
F 3 "" H 1700 1450 50  0001 C CNN
	1    1700 1450
	1    0    0    -1  
$EndComp
NoConn ~ 1500 1450
NoConn ~ 1500 1550
NoConn ~ 2000 1450
Text Label 7750 3850 0    60   ~ 0
CLK_PIN
Text Label 8150 4150 0    60   ~ 0
LATCH_PIN
Text Label 7150 4300 2    60   ~ 0
~ENABLE
$Comp
L C C102
U 1 1 59EF980D
P 3250 4200
F 0 "C102" H 3275 4300 50  0000 L CNN
F 1 "1μF 16V" H 3100 4100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3288 4050 50  0001 C CNN
F 3 "" H 3250 4200 50  0001 C CNN
F 4 "Value" H 3250 4200 60  0001 C CNN "Link"
	1    3250 4200
	1    0    0    -1  
$EndComp
Text Notes 750  850  0    100  ~ 0
In System Programming Header - UPDI
Text Label 2100 3850 0    60   ~ 0
5V
$Comp
L Jack-DC J102
U 1 1 59F100E4
P 1000 3950
F 0 "J102" H 1000 4160 50  0000 C CNN
F 1 "5V In" H 1000 3775 50  0000 C CNN
F 2 "advent_sternla:CONN_PWR_JACK_1_3X3_5MM_SOLDER" H 1050 3910 50  0001 C CNN
F 3 "http://www.cui.com/product/resource/pj-031dh.pdf" H 1050 3910 50  0001 C CNN
F 4 "PJ-031DH" H 1000 3950 60  0001 C CNN "MPN"
F 5 "https://www.digikey.de/scripts/DkSearch/dksus.dll?Detail&itemSeq=242071905&uq=636445427915242131" H 1000 3950 60  0001 C CNN "Link"
	1    1000 3950
	1    0    0    -1  
$EndComp
NoConn ~ 1300 3950
Text Label 2250 3500 2    60   ~ 0
5V_OUT
Text Notes 5450 800  0    100  ~ 0
NeoPixel
$Comp
L D D101
U 1 1 59F5F260
P 2650 3850
F 0 "D101" H 2650 3950 50  0000 C CNN
F 1 "1N4148WSTR" H 2650 3750 50  0000 C CNN
F 2 "Diodes_SMD:D_SOD-123F" H 2650 3850 50  0001 C CNN
F 3 "http://www.smc-diodes.com/propdf/1N4148WS%20N0572%20REV.B.pdf" H 2650 3850 50  0001 C CNN
F 4 "1N4148WSTR" H 2650 3850 60  0001 C CNN "MPN"
F 5 "Value" H 2650 3850 60  0001 C CNN "ConradPN"
F 6 "Value" H 2650 3850 60  0001 C CNN "Label"
	1    2650 3850
	-1   0    0    1   
$EndComp
Text Notes 1550 6150 0    60   ~ 0
TODO \nVerify, once more, the Diode i.e. the current rating\nDouble check the connection for the UPDI - is there a need for a \nzero Ohm resistor to deal with any issues?
$Comp
L 74LS596-RESCUE-FiveChannel U101
U 1 1 5A60F031
P 9300 4100
F 0 "U101" H 9450 4700 70  0000 C CNN
F 1 "74LS595" H 9300 3500 70  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 9300 4100 60  0001 C CNN
F 3 "" H 9300 4100 60  0000 C CNN
F 4 "Value" H 9300 4100 60  0001 C CNN "MPN"
F 5 "Value" H 9300 4100 60  0001 C CNN "Link"
F 6 "Value" H 9300 4100 60  0000 C CNN "Comp_Name"
F 7 "Value" H 9300 4100 60  0001 C CNN "ConradPN"
F 8 "Value" H 9300 4100 60  0000 C CNN "Label"
	1    9300 4100
	1    0    0    -1  
$EndComp
NoConn ~ 10000 4150
NoConn ~ 10000 4250
NoConn ~ 10000 4350
NoConn ~ 10000 4550
$Comp
L GND #PWR04
U 1 1 5A60F656
P 9000 5100
F 0 "#PWR04" H 9000 4850 50  0001 C CNN
F 1 "GND" H 9000 4950 50  0000 C CNN
F 2 "" H 9000 5100 50  0001 C CNN
F 3 "" H 9000 5100 50  0001 C CNN
	1    9000 5100
	1    0    0    -1  
$EndComp
Text Label 7750 3650 0    60   ~ 0
DATA_PIN
Text Label 8200 3950 0    60   ~ 0
VDD
Text Label 10600 3650 2    60   ~ 0
CHANNEL_0
Text Label 10600 3750 2    60   ~ 0
CHANNEL_1
Text Label 10600 3850 2    60   ~ 0
CHANNEL_2
Text Label 10600 3950 2    60   ~ 0
CHANNEL_3
Text Label 10600 4050 2    60   ~ 0
CHANNEL_4
Text Label 8850 3050 0    60   ~ 0
VDD
$Sheet
S 5250 1100 1100 1750
U 5A6111EA
F0 "Channels" 60
F1 "Channels.sch" 60
F2 "CHANNEL_0" I L 5250 1450 60 
F3 "5V_OUT" I L 5250 2750 60 
F4 "CHANNEL_1" I L 5250 1700 60 
F5 "CHANNEL_2" I L 5250 1950 60 
F6 "CHANNEL_3" I L 5250 2250 60 
F7 "CHANNEL_4" I L 5250 2500 60 
$EndSheet
Text Label 4650 2500 0    60   ~ 0
CHANNEL_4
Text Label 4650 2250 0    60   ~ 0
CHANNEL_3
Text Label 4650 1450 0    60   ~ 0
CHANNEL_0
Text Label 4650 1700 0    60   ~ 0
CHANNEL_1
Text Label 4650 1950 0    60   ~ 0
CHANNEL_2
Text Label 8150 4250 0    60   ~ 0
~ENABLE
$Comp
L C C103
U 1 1 5A613301
P 7950 4600
F 0 "C103" H 7975 4700 50  0000 L CNN
F 1 "0.1μF 16V" H 7700 4500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7988 4450 50  0001 C CNN
F 3 "" H 7950 4600 50  0001 C CNN
F 4 "Value" H 7950 4600 60  0001 C CNN "Link"
	1    7950 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5A61342B
P 7950 4900
F 0 "#PWR05" H 7950 4650 50  0001 C CNN
F 1 "GND" H 7950 4750 50  0000 C CNN
F 2 "" H 7950 4900 50  0001 C CNN
F 3 "" H 7950 4900 50  0001 C CNN
	1    7950 4900
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04_Male J103
U 1 1 5A64D382
P 6750 5650
F 0 "J103" H 6750 5850 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6750 5350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x04_Pitch2.54mm" H 6750 5650 50  0001 C CNN
F 3 "" H 6750 5650 50  0001 C CNN
	1    6750 5650
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x07_Male J104
U 1 1 5A64D42F
P 8100 5800
F 0 "J104" H 8100 6200 50  0000 C CNN
F 1 "Conn_01x07_Male" H 8100 5400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x07_Pitch2.54mm" H 8100 5800 50  0001 C CNN
F 3 "" H 8100 5800 50  0001 C CNN
	1    8100 5800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3800 4300 4800 4300
Wire Wire Line
	4600 4300 4600 4200
Wire Wire Line
	5600 5550 5600 5250
Connection ~ 4600 4300
Wire Wire Line
	1500 1350 1050 1350
Wire Wire Line
	2000 1550 2250 1550
Wire Wire Line
	2250 1550 2250 1750
Wire Wire Line
	2000 1350 2450 1350
Wire Wire Line
	1300 3850 2500 3850
Wire Wire Line
	3250 3850 3250 4050
Wire Wire Line
	3250 4700 3250 4350
Wire Notes Line
	700  900  3000 900 
Wire Notes Line
	3000 900  3000 2100
Wire Notes Line
	3000 2100 700  2100
Wire Notes Line
	700  2100 700  900 
Wire Wire Line
	1500 4700 3250 4700
Wire Wire Line
	2550 4700 2550 4900
Connection ~ 2550 4700
Wire Wire Line
	1500 4700 1500 4050
Wire Wire Line
	1500 4050 1300 4050
Wire Wire Line
	2000 3850 2000 3500
Wire Wire Line
	2000 3500 2250 3500
Connection ~ 2000 3850
Wire Wire Line
	2800 3850 4800 3850
Connection ~ 3250 3850
Wire Wire Line
	4600 3900 4600 3850
Connection ~ 4600 3850
Wire Wire Line
	6650 3850 6650 3650
Wire Wire Line
	6650 3650 8600 3650
Wire Wire Line
	10000 3650 10600 3650
Wire Wire Line
	10000 3750 10600 3750
Wire Wire Line
	10000 3850 10600 3850
Wire Wire Line
	10000 3950 10600 3950
Wire Wire Line
	10000 4050 10600 4050
Wire Wire Line
	9000 4950 9000 5100
Wire Wire Line
	6450 3850 6650 3850
Wire Wire Line
	6450 4000 6700 4000
Wire Wire Line
	6700 4000 6700 3850
Wire Wire Line
	6700 3850 8600 3850
Wire Wire Line
	8200 3950 8600 3950
Wire Wire Line
	6450 4150 8600 4150
Wire Wire Line
	6450 4300 7150 4300
Wire Wire Line
	9300 3250 9300 3050
Wire Wire Line
	9300 3050 8850 3050
Wire Wire Line
	5250 1450 4650 1450
Wire Wire Line
	5250 1700 4650 1700
Wire Wire Line
	5250 1950 4650 1950
Wire Wire Line
	5250 2250 4650 2250
Wire Wire Line
	5250 2500 4650 2500
Wire Wire Line
	5250 2750 4650 2750
Wire Wire Line
	8600 4250 8150 4250
Wire Wire Line
	7950 4150 7950 4450
Connection ~ 7950 4150
Wire Wire Line
	7950 4900 7950 4750
Wire Wire Line
	4800 4500 4100 4500
Wire Wire Line
	4800 4650 4100 4650
Wire Wire Line
	4800 4800 4100 4800
Wire Wire Line
	4800 4950 4100 4950
Wire Wire Line
	6550 5550 6150 5550
Wire Wire Line
	6550 5650 6150 5650
Wire Wire Line
	6550 5750 6150 5750
Wire Wire Line
	6550 5850 6150 5850
Wire Wire Line
	7900 5500 7300 5500
Wire Wire Line
	7900 5600 7300 5600
Wire Wire Line
	7900 5700 7300 5700
Wire Wire Line
	7900 5800 7300 5800
Wire Wire Line
	7900 5900 7300 5900
Wire Wire Line
	7900 6000 7300 6000
Wire Wire Line
	7900 6100 7300 6100
Text Label 4100 4500 0    60   ~ 0
PB0
Text Label 6150 5650 0    60   ~ 0
PB0
Text Label 4100 4650 0    60   ~ 0
PB1
Text Label 6150 5550 0    60   ~ 0
PB1
Text Label 4100 4800 0    60   ~ 0
PB2
Text Label 4100 4950 0    60   ~ 0
PB3
Text Label 6150 5850 0    60   ~ 0
PB2
Text Label 6150 5750 0    60   ~ 0
PB3
Text Label 7300 5900 0    60   ~ 0
PA5
Text Label 7300 6000 0    60   ~ 0
PA6
Text Label 7300 6100 0    60   ~ 0
PA7
Wire Wire Line
	6450 4450 7150 4450
Wire Wire Line
	6450 4600 7150 4600
Wire Wire Line
	6450 4750 7150 4750
Text Label 7150 4750 2    60   ~ 0
PA7
Text Label 7150 4600 2    60   ~ 0
PA6
Text Label 7150 4450 2    60   ~ 0
PA5
Text Label 7300 5800 0    60   ~ 0
~ENABLE
Text Label 7000 5100 0    60   ~ 0
LATCH_PIN
Text Label 7300 5500 0    60   ~ 0
LATCH_PIN
Text Label 7300 5600 0    60   ~ 0
CLK_PIN
Text Label 7300 5700 0    60   ~ 0
DATA_PIN
$Comp
L C C101
U 1 1 5A64D305
P 1850 4200
F 0 "C101" H 1875 4300 50  0000 L CNN
F 1 "1000μF 25V" H 1700 4100 50  0000 L CNN
F 2 "advent_sternla:CP_Radial_L21.0mm_D13.0mm_P5.00mm_Horizontal" H 1888 4050 50  0001 C CNN
F 3 "" H 1850 4200 50  0001 C CNN
F 4 "Value" H 1850 4200 60  0001 C CNN "Link"
F 5 "Value" H 1850 4200 60  0000 C CNN "Comp_Name"
	1    1850 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 3850 1850 4050
Connection ~ 1850 3850
Wire Wire Line
	1850 4350 1850 4700
Connection ~ 1850 4700
Text Label 4650 2750 0    60   ~ 0
5V_OUT
$EndSCHEMATC
