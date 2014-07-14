EESchema Schematic File Version 2  date 20/01/2013 22:20:17
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
LIBS:PCA9698 ADAPTER-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title "noname.sch"
Date "18 jan 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	6850 3600 6750 3600
Wire Wire Line
	6850 3400 6750 3400
Wire Wire Line
	6850 3200 6750 3200
Wire Wire Line
	6850 3000 6750 3000
Wire Wire Line
	6750 2900 6850 2900
Wire Wire Line
	6750 3100 6850 3100
Wire Wire Line
	6750 3300 6850 3300
Wire Wire Line
	6750 3500 6850 3500
Wire Wire Line
	6750 4400 6850 4400
Wire Wire Line
	6750 4200 6850 4200
Wire Wire Line
	6750 4000 6850 4000
Wire Wire Line
	6750 3800 6850 3800
Wire Wire Line
	6850 3900 6750 3900
Wire Wire Line
	6850 4100 6750 4100
Wire Wire Line
	6850 4300 6750 4300
Wire Wire Line
	6850 4500 6750 4500
Wire Wire Line
	6850 5400 6750 5400
Wire Wire Line
	6850 5200 6750 5200
Wire Wire Line
	6850 5000 6750 5000
Wire Wire Line
	6850 4800 6750 4800
Wire Wire Line
	6750 4700 6850 4700
Wire Wire Line
	6750 4900 6850 4900
Wire Wire Line
	6750 5100 6850 5100
Wire Wire Line
	6750 5300 6850 5300
Wire Wire Line
	4850 5300 4950 5300
Wire Wire Line
	4850 5100 4950 5100
Wire Wire Line
	4850 4900 4950 4900
Wire Wire Line
	4850 4700 4950 4700
Wire Wire Line
	4950 4800 4850 4800
Wire Wire Line
	4950 5000 4850 5000
Wire Wire Line
	4950 5200 4850 5200
Wire Wire Line
	4950 5400 4850 5400
$Comp
L CONN_8 P6
U 1 1 50F99D74
P 7200 5050
F 0 "P6" V 7150 5050 60  0000 C CNN
F 1 "PORT 4" V 7250 5050 60  0000 C CNN
	1    7200 5050
	1    0    0    -1  
$EndComp
$Comp
L CONN_8 P5
U 1 1 50F99D6F
P 7200 4150
F 0 "P5" V 7150 4150 60  0000 C CNN
F 1 "PORT 3" V 7250 4150 60  0000 C CNN
	1    7200 4150
	1    0    0    -1  
$EndComp
$Comp
L CONN_8 P4
U 1 1 50F99D64
P 7200 3250
F 0 "P4" V 7150 3250 60  0000 C CNN
F 1 "PORT 2" V 7250 3250 60  0000 C CNN
	1    7200 3250
	1    0    0    -1  
$EndComp
$Comp
L CONN_8 P3
U 1 1 50F99D49
P 4500 5050
F 0 "P3" V 4450 5050 60  0000 C CNN
F 1 "PORT1" V 4550 5050 60  0000 C CNN
	1    4500 5050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4950 4500 4850 4500
Wire Wire Line
	4950 4300 4850 4300
Wire Wire Line
	4950 4100 4850 4100
Wire Wire Line
	4950 3900 4850 3900
Wire Wire Line
	5850 5950 5850 5800
Wire Wire Line
	4950 3300 4650 3300
Wire Wire Line
	4950 3500 4450 3500
Connection ~ 5850 5800
Connection ~ 5700 5800
Connection ~ 5800 5800
Wire Wire Line
	4000 3100 4150 3100
Connection ~ 5850 2500
Wire Wire Line
	5850 2450 5850 2500
Connection ~ 4100 3300
Connection ~ 4050 3100
Wire Wire Line
	5900 2500 5800 2500
Wire Wire Line
	4150 2800 4050 2800
Wire Wire Line
	4050 2800 4050 3400
Wire Wire Line
	4050 3400 4150 3400
Wire Wire Line
	4150 3000 4100 3000
Wire Wire Line
	4100 3000 4100 3600
Wire Wire Line
	4100 3600 4150 3600
Wire Wire Line
	4000 3300 4150 3300
Wire Wire Line
	6100 5800 5600 5800
Connection ~ 6000 5800
Connection ~ 5900 5800
Wire Wire Line
	4950 3600 4950 3650
Wire Wire Line
	4950 3650 4900 3650
Wire Wire Line
	4950 3400 4550 3400
Wire Wire Line
	4550 3400 4550 3200
Wire Wire Line
	4550 3200 4450 3200
Wire Wire Line
	4450 2900 4550 2900
Wire Wire Line
	4550 2900 4550 3100
Wire Wire Line
	4550 3100 4650 3100
Wire Wire Line
	4650 3100 4650 3300
Wire Wire Line
	4850 3800 4950 3800
Wire Wire Line
	4850 4000 4950 4000
Wire Wire Line
	4850 4200 4950 4200
Wire Wire Line
	4850 4400 4950 4400
$Comp
L CONN_8 P2
U 1 1 50F99CF5
P 4500 4150
F 0 "P2" V 4450 4150 60  0000 C CNN
F 1 "PORT 0" V 4550 4150 60  0000 C CNN
	1    4500 4150
	-1   0    0    -1  
$EndComp
Text Label 4000 3300 2    60   ~ 0
GND
Text Label 4000 3100 2    60   ~ 0
VDD
$Comp
L GS3 GS3
U 1 1 50F99B7F
P 4300 3500
F 0 "GS3" H 4425 3600 50  0000 C CNN
F 1 "GS3" H 4425 3400 40  0000 C CNN
	1    4300 3500
	1    0    0    -1  
$EndComp
$Comp
L GS3 GS2
U 1 1 50F99B7A
P 4300 3200
F 0 "GS2" H 4425 3300 50  0000 C CNN
F 1 "GS3" H 4425 3100 40  0000 C CNN
	1    4300 3200
	1    0    0    -1  
$EndComp
$Comp
L GS3 GS1
U 1 1 50F99B4E
P 4300 2900
F 0 "GS1" H 4425 3000 50  0000 C CNN
F 1 "GS3" H 4425 2800 40  0000 C CNN
	1    4300 2900
	1    0    0    -1  
$EndComp
Text Label 5850 2450 0    60   ~ 0
VDD
Text Label 5850 5950 0    60   ~ 0
GND
Text Label 4950 2900 2    60   ~ 0
TWD
Text Label 4950 3000 2    60   ~ 0
TWCK
Text Label 4950 3100 2    60   ~ 0
~RESET
Text Label 4950 3200 2    60   ~ 0
~INT
Text Label 4900 3650 2    60   ~ 0
~OE
Text Label 3500 3550 0    60   ~ 0
~OE
Text Label 3500 3450 0    60   ~ 0
~INT
Text Label 3500 3350 0    60   ~ 0
~RESET
Text Label 3500 3250 0    60   ~ 0
TWCK
Text Label 3500 3150 0    60   ~ 0
TWD
Text Label 3500 3050 0    60   ~ 0
GND
Text Label 3500 2950 0    60   ~ 0
VDD
$Comp
L CONN_7 P1
U 1 1 50F99AA9
P 3150 3250
F 0 "P1" V 3120 3250 60  0000 C CNN
F 1 "System IN" V 3220 3250 60  0000 C CNN
	1    3150 3250
	-1   0    0    -1  
$EndComp
$Comp
L PCA9698 U1
U 1 1 50F99056
P 5850 4150
F 0 "U1" H 5300 5550 50  0000 C CNN
F 1 "PCA9698" H 5850 4150 40  0000 C CNN
	1    5850 4150
	1    0    0    -1  
$EndComp
$EndSCHEMATC
