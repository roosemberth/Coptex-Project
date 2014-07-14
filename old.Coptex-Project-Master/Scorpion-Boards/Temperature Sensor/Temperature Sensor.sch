EESchema Schematic File Version 2  date dim. 02 juin 2013 13:49:18 CST
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
LIBS:special
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
LIBS:AT91SAM7X ADAPTOP-cache
LIBS:Coptex-cache
LIBS:Coptex Mainboard-cache
LIBS:Coptex MCU Brain Board-cache
LIBS:Coptex Motherboard-cache
LIBS:Coptex Project-cache
LIBS:DM9161AEP Network Adapter-cache
LIBS:PCA9698 ADAPTER-cache
LIBS:wiz610wi
LIBS:Coptex Project-cache
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "2 jun 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 5450 3400
Wire Wire Line
	5450 3400 4950 3400
Wire Wire Line
	4950 3400 4950 3750
Wire Wire Line
	4950 3750 4900 3750
Connection ~ 5350 3350
Wire Wire Line
	5350 3350 5550 3350
Wire Wire Line
	5550 3350 5550 3750
Wire Wire Line
	5550 3750 5600 3750
Wire Wire Line
	5900 3650 5950 3650
Wire Wire Line
	5950 3650 5950 3000
Wire Wire Line
	5950 3000 5850 3000
Wire Wire Line
	5150 3450 5150 3300
Wire Wire Line
	5150 3300 4600 3300
Wire Wire Line
	4600 3300 4600 2900
Wire Wire Line
	4600 2900 4700 2900
Wire Wire Line
	4700 3000 4650 3000
Wire Wire Line
	4650 3000 4650 3250
Wire Wire Line
	4650 3250 5350 3250
Wire Wire Line
	5350 3250 5350 3450
Wire Wire Line
	5450 3450 5450 3250
Wire Wire Line
	5450 3250 5850 3250
Wire Wire Line
	5850 3250 5850 3100
Wire Wire Line
	5250 3450 5250 3300
Wire Wire Line
	5250 3300 5900 3300
Wire Wire Line
	5900 3300 5900 2900
Wire Wire Line
	5900 2900 5850 2900
Wire Wire Line
	4700 3100 4550 3100
Wire Wire Line
	4550 3100 4550 3650
Wire Wire Line
	4550 3650 4600 3650
Wire Wire Line
	5600 3550 5600 3250
Connection ~ 5600 3250
Wire Wire Line
	4900 3550 4900 3250
Connection ~ 4900 3250
$Comp
L GS3 GS1
U 1 1 51ABA111
P 4750 3650
F 0 "GS1" H 4800 3850 50  0000 C CNN
F 1 "GS3" H 4800 3451 40  0000 C CNN
	1    4750 3650
	-1   0    0    1   
$EndComp
$Comp
L GS3 GS2
U 1 1 51ABA102
P 5750 3650
F 0 "GS2" H 5800 3850 50  0000 C CNN
F 1 "GS3" H 5800 3451 40  0000 C CNN
	1    5750 3650
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P1
U 1 1 51AB9F93
P 5300 3800
F 0 "P1" V 5250 3800 50  0000 C CNN
F 1 "CONN_4" V 5350 3800 50  0000 C CNN
	1    5300 3800
	0    1    1    0   
$EndComp
$Comp
L TMP100 TMP1
U 1 1 51AB9F1D
P 5300 3000
F 0 "TMP1" H 5150 3200 60  0000 C CNN
F 1 "TMP100" H 5350 2800 60  0000 C CNN
	1    5300 3000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
