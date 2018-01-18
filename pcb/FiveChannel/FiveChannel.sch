EESchema Schematic File Version 2
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
LIBS:FiveChannel-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L ATTINY1614 U101
U 1 1 59EF6A42
P 5600 4400
F 0 "U101" H 6150 3600 60  0000 C CNN
F 1 "ATTINY1614" H 5650 4350 60  0000 C CNN
F 2 "SMD_Packages:SOIC-14_N" H 5450 4450 60  0001 C CNN
F 3 "" H 5450 4450 60  0001 C CNN
	1    5600 4400
	1    0    0    -1  
$EndComp
$Comp
L R R102
U 1 1 59EF6A7A
P 4600 4050
F 0 "R102" V 4680 4050 50  0000 C CNN
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
Text Label 7750 4150 0    60   ~ 0
LATCH_PIN
Text Label 7750 4250 0    60   ~ 0
~ENABLE
Text Label 7100 4500 0    60   ~ 0
PA5
Text Label 7100 4600 0    60   ~ 0
PA6
Text Label 7100 4700 0    60   ~ 0
PA7
$Comp
L Conn_01x03_Male J105
U 1 1 59EF8E2B
P 8050 5450
F 0 "J105" H 8000 5650 50  0000 C CNN
F 1 "GPIO_A" H 8200 5300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 8050 5450 50  0001 C CNN
F 3 "" H 8050 5450 50  0001 C CNN
	1    8050 5450
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x04_Male J107
U 1 1 59EF90A2
P 3600 4750
F 0 "J107" H 3600 4950 50  0000 C CNN
F 1 "GPIO_C" H 3600 4450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 3600 4750 50  0001 C CNN
F 3 "" H 3600 4750 50  0001 C CNN
	1    3600 4750
	1    0    0    -1  
$EndComp
Text Label 4250 4500 0    60   ~ 0
PB0
Text Label 4250 4650 0    60   ~ 0
PB1
Text Label 4250 4800 0    60   ~ 0
PB2
Text Label 4250 4950 0    60   ~ 0
PB3
$Comp
L C C103
U 1 1 59EF980D
P 3250 4200
F 0 "C103" H 3275 4300 50  0000 L CNN
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
L GND #PWR04
U 1 1 59EFA048
P 6450 1650
F 0 "#PWR04" H 6450 1400 50  0001 C CNN
F 1 "GND" H 6450 1500 50  0000 C CNN
F 2 "" H 6450 1650 50  0001 C CNN
F 3 "" H 6450 1650 50  0001 C CNN
	1    6450 1650
	1    0    0    -1  
$EndComp
$Comp
L R R101
U 1 1 59EFA380
P 6100 1500
F 0 "R101" V 6180 1500 50  0000 C CNN
F 1 "470Ω" V 6100 1500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6030 1500 50  0001 C CNN
F 3 "" H 6100 1500 50  0001 C CNN
	1    6100 1500
	0    -1   -1   0   
$EndComp
Text Notes 5850 1250 0    60   ~ 0
The NoePixel has JST \nSM type connnectors
$Comp
L Conn_01x02_Male J102
U 1 1 59F0DA81
P 6850 1500
F 0 "J102" H 6850 1600 50  0000 C CNN
F 1 "NeoPixel Data" H 6500 1450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 6850 1500 50  0001 C CNN
F 3 "" H 6850 1500 50  0001 C CNN
	1    6850 1500
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x02_Male J103
U 1 1 59F0DC96
P 6850 2100
F 0 "J103" H 6900 2200 50  0000 C CNN
F 1 "Power Out" H 7050 1900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 6850 2100 50  0001 C CNN
F 3 "" H 6850 2100 50  0001 C CNN
	1    6850 2100
	-1   0    0    -1  
$EndComp
Text Label 6300 1500 0    60   ~ 0
NP_DATA
$Comp
L GND #PWR05
U 1 1 59F0F6AA
P 6350 2600
F 0 "#PWR05" H 6350 2350 50  0001 C CNN
F 1 "GND" H 6350 2450 50  0000 C CNN
F 2 "" H 6350 2600 50  0001 C CNN
F 3 "" H 6350 2600 50  0001 C CNN
	1    6350 2600
	1    0    0    -1  
$EndComp
$Comp
L CP C102
U 1 1 59F0F869
P 1900 4150
F 0 "C102" H 1925 4250 50  0000 L CNN
F 1 "1000μF 25V" H 1925 4050 50  0000 L CNN
F 2 "advent_sternla:CP_Radial_L21.0mm_D13.0mm_P5.00mm_Horizontal" H 1938 4000 50  0001 C CNN
F 3 "" H 1900 4150 50  0001 C CNN
	1    1900 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4300 4600 4300
Wire Wire Line
	4600 4300 4800 4300
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
	6450 4450 7000 4450
Wire Wire Line
	6450 4600 7300 4600
Wire Wire Line
	6450 4750 7000 4750
Wire Wire Line
	1300 3850 1900 3850
Wire Wire Line
	1900 3850 2000 3850
Wire Wire Line
	2000 3850 2500 3850
Wire Wire Line
	4100 4650 4800 4650
Wire Wire Line
	4800 4950 3800 4950
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
	7000 4450 7000 4500
Wire Wire Line
	7000 4500 7300 4500
Wire Wire Line
	4150 4800 4800 4800
Wire Wire Line
	4150 4800 4150 4850
Wire Wire Line
	4150 4850 3800 4850
Wire Wire Line
	4100 4650 4100 4750
Wire Wire Line
	4100 4750 3800 4750
Wire Wire Line
	4800 4500 4050 4500
Wire Wire Line
	4050 4500 4050 4650
Wire Wire Line
	4050 4650 3800 4650
Wire Wire Line
	5400 1500 5950 1500
Wire Wire Line
	6250 1500 6650 1500
Wire Wire Line
	6650 1600 6450 1600
Wire Wire Line
	6450 1600 6450 1650
Wire Wire Line
	5950 2100 6650 2100
Wire Wire Line
	6650 2200 6350 2200
Wire Wire Line
	6350 2200 6350 2600
Wire Wire Line
	1900 3850 1900 4000
Connection ~ 1900 3850
Wire Wire Line
	1900 4300 1900 4700
Wire Wire Line
	1500 4700 1900 4700
Wire Wire Line
	1900 4700 2550 4700
Wire Wire Line
	2550 4700 3250 4700
Wire Wire Line
	2550 4700 2550 4900
Connection ~ 1900 4700
Connection ~ 2550 4700
$Comp
L Jack-DC J104
U 1 1 59F100E4
P 1000 3950
F 0 "J104" H 1000 4160 50  0000 C CNN
F 1 "5V In" H 1000 3775 50  0000 C CNN
F 2 "advent_sternla:CONN_PWR_JACK_1_3X3_5MM_SOLDER" H 1050 3910 50  0001 C CNN
F 3 "http://www.cui.com/product/resource/pj-031dh.pdf" H 1050 3910 50  0001 C CNN
F 4 "PJ-031DH" H 1000 3950 60  0001 C CNN "MPN"
F 5 "https://www.digikey.de/scripts/DkSearch/dksus.dll?Detail&itemSeq=242071905&uq=636445427915242131" H 1000 3950 60  0001 C CNN "Link"
	1    1000 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4700 1500 4050
Wire Wire Line
	1500 4050 1300 4050
NoConn ~ 1300 3950
Wire Wire Line
	2000 3850 2000 3500
Wire Wire Line
	2000 3500 2250 3500
Connection ~ 2000 3850
Text Label 2250 3500 2    60   ~ 0
5V_OUT
Text Label 5950 2100 0    60   ~ 0
5V_OUT
Wire Notes Line
	7600 850  7600 2950
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
Wire Wire Line
	2800 3850 3250 3850
Wire Wire Line
	3250 3850 4600 3850
Wire Wire Line
	4600 3850 4800 3850
Connection ~ 3250 3850
Wire Wire Line
	4600 3900 4600 3850
Connection ~ 4600 3850
Text Notes 1550 6150 0    60   ~ 0
TODO \nVerify, once more, the Diode i.e. the current rating\nDouble check the connection for the UPDI - is there a need for a \nzero Ohm resistor to deal with any issues?
Wire Wire Line
	7000 4750 7000 4700
Wire Wire Line
	7000 4700 7300 4700
$Comp
L 74LS596 U?
U 1 1 5A60F031
P 9300 4100
F 0 "U?" H 9450 4700 70  0000 C CNN
F 1 "74LS596" H 9300 3500 70  0000 C CNN
F 2 "" H 9300 4100 60  0000 C CNN
F 3 "" H 9300 4100 60  0000 C CNN
	1    9300 4100
	1    0    0    -1  
$EndComp
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
NoConn ~ 10000 4150
NoConn ~ 10000 4250
NoConn ~ 10000 4350
NoConn ~ 10000 4550
$Comp
L GND #PWR?
U 1 1 5A60F656
P 9000 5100
F 0 "#PWR?" H 9000 4850 50  0001 C CNN
F 1 "GND" H 9000 4950 50  0000 C CNN
F 2 "" H 9000 5100 50  0001 C CNN
F 3 "" H 9000 5100 50  0001 C CNN
	1    9000 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 4950 9000 5100
Wire Wire Line
	7850 6000 7500 6000
Wire Wire Line
	7850 6100 7500 6100
Wire Wire Line
	7850 6200 7500 6200
Text Label 7500 6000 0    60   ~ 0
PA5
Text Label 7500 6100 0    60   ~ 0
PA6
Text Label 7500 6200 0    60   ~ 0
PA7
Text Label 7750 3650 0    60   ~ 0
DATA_PIN
Wire Wire Line
	6450 3850 6650 3850
Wire Wire Line
	6450 4000 6700 4000
Wire Wire Line
	6700 4000 6700 3850
Text Label 8200 3950 0    60   ~ 0
VDD
Wire Wire Line
	6700 3850 8600 3850
Wire Wire Line
	8200 3950 8600 3950
Wire Wire Line
	6450 4150 8600 4150
Wire Wire Line
	6450 4300 6700 4300
Wire Wire Line
	6700 4300 6700 4250
Wire Wire Line
	6700 4250 8600 4250
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
Text Label 7500 5900 0    60   ~ 0
PA4
Wire Wire Line
	7850 5900 7500 5900
$Comp
L Conn_01x04_Male J106
U 1 1 59EF8DC0
P 8050 6000
F 0 "J106" H 8050 6200 50  0000 C CNN
F 1 "GPIO_B" H 8150 5750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 8050 6000 50  0001 C CNN
F 3 "" H 8050 6000 50  0001 C CNN
	1    8050 6000
	-1   0    0    -1  
$EndComp
Text Label 7500 5550 0    60   ~ 0
PA3
Text Label 7500 5450 0    60   ~ 0
PA2
Text Label 7500 5350 0    60   ~ 0
PA1
Wire Wire Line
	7850 5550 7500 5550
Wire Wire Line
	7850 5450 7500 5450
Wire Wire Line
	7850 5350 7500 5350
Wire Wire Line
	9300 3250 9300 3050
Wire Wire Line
	9300 3050 8850 3050
Text Label 8850 3050 0    60   ~ 0
VDD
Text Label 5400 1500 0    60   ~ 0
CHANNEL_0
$EndSCHEMATC
