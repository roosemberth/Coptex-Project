EESchema Schematic File Version 2  date 23/01/2013 23:02:35
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
LIBS:Coptex Project-cache
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "24 jan 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 2350 4700
Wire Wire Line
	2350 4600 2650 4600
Wire Wire Line
	2650 4600 2650 4700
Wire Wire Line
	2650 4700 2800 4700
Wire Wire Line
	2700 4150 2600 4150
Wire Wire Line
	5700 4450 5700 4900
Wire Wire Line
	5700 4900 5400 4900
Wire Wire Line
	5500 4450 5500 4700
Wire Wire Line
	5500 4700 5400 4700
Wire Wire Line
	6100 4800 5900 4800
Wire Wire Line
	5900 4800 5900 4450
Wire Wire Line
	6200 4450 6300 4450
Wire Wire Line
	4900 4950 4800 4950
Wire Wire Line
	4000 4650 3250 4650
Wire Wire Line
	3250 4450 4000 4450
Connection ~ 3650 4250
Wire Wire Line
	3250 4250 4000 4250
Wire Wire Line
	3650 4250 3650 4150
Connection ~ 4400 3650
Wire Wire Line
	4400 3600 4400 3900
Connection ~ 3650 3650
Connection ~ 3500 3650
Wire Wire Line
	4800 4050 4800 3900
Wire Wire Line
	4800 3900 4000 3900
Wire Wire Line
	4000 3900 4000 4050
Connection ~ 4800 4350
Connection ~ 4800 4250
Wire Wire Line
	4800 4950 4800 4150
Connection ~ 4800 4750
Connection ~ 4800 4650
Wire Wire Line
	5300 4450 5200 4450
Wire Wire Line
	5200 4550 5400 4550
Wire Wire Line
	5400 4550 5400 4450
Connection ~ 4800 4850
Connection ~ 4800 4450
Connection ~ 4800 4550
Connection ~ 4400 3900
Wire Wire Line
	4400 3650 3350 3650
Connection ~ 3800 3650
Wire Wire Line
	3800 4150 4000 4150
Wire Wire Line
	3500 4350 3500 4150
Wire Wire Line
	4000 4550 3350 4550
Wire Wire Line
	3350 4550 3350 4150
Connection ~ 3350 4450
Wire Wire Line
	3250 4350 4000 4350
Connection ~ 3500 4350
Wire Wire Line
	4000 4750 3750 4750
Wire Wire Line
	3350 4750 3250 4750
Wire Wire Line
	6300 4550 6100 4550
Wire Wire Line
	6100 4550 6100 4450
Wire Wire Line
	6100 4700 6000 4700
Wire Wire Line
	6000 4700 6000 4450
Wire Wire Line
	6100 4900 5800 4900
Wire Wire Line
	5800 4900 5800 4450
Wire Wire Line
	5600 4450 5600 4800
Wire Wire Line
	5600 4800 5400 4800
Wire Wire Line
	2300 4150 2400 4150
Text Label 2800 4300 2    60   ~ 0
3.3
$Comp
L DIODESCH D1
U 1 1 51008FAA
P 2800 4500
F 0 "D1" H 2800 4600 40  0000 C CNN
F 1 "DIODESCH" H 2800 4400 40  0000 C CNN
	1    2800 4500
	0    1    1    0   
$EndComp
Text Label 2350 4500 0    60   ~ 0
GND
$Comp
L CONN_5 P1
U 1 1 51008F63
P 2050 4500
F 0 "P1" V 2000 4500 50  0000 C CNN
F 1 "CONN_5" V 2100 4500 50  0000 C CNN
	1    2050 4500
	-1   0    0    -1  
$EndComp
Text Label 2350 4300 0    60   ~ 0
DTXD
Text Label 2350 4400 0    60   ~ 0
DRXD
Text Label 2700 4150 0    60   ~ 0
3.3
$Comp
L CONN_2 P2
U 1 1 5100867F
P 2500 3800
F 0 "P2" V 2450 3800 40  0000 C CNN
F 1 "JTAGSEL" V 2550 3800 40  0000 C CNN
	1    2500 3800
	0    -1   -1   0   
$EndComp
Text Label 3250 4650 2    60   ~ 0
TDO
Text Label 2300 4150 2    60   ~ 0
JTAGSEL
Text Label 3250 4750 2    60   ~ 0
~RESET
Text Label 3250 4250 2    60   ~ 0
TDI
Text Label 3250 4350 2    60   ~ 0
TMS
Text Label 3250 4450 2    60   ~ 0
TCK
Text Label 6300 4450 0    60   ~ 0
DRXD
Text Label 6300 4550 0    60   ~ 0
DTXD
Text Label 6100 4700 0    60   ~ 0
~RESET
Text Label 6100 4800 0    60   ~ 0
JTAGSEL
Text Label 6100 4900 0    60   ~ 0
TDO
Text Label 5400 4900 2    60   ~ 0
TCK
Text Label 5400 4800 2    60   ~ 0
TMS
Text Label 5400 4700 2    60   ~ 0
TDI
Text Label 4900 4950 0    60   ~ 0
GND
NoConn ~ 4000 4950
NoConn ~ 4000 4850
$Comp
L GS2 GS1
U 1 1 51008355
P 3550 4750
F 0 "GS1" H 3650 4900 50  0000 C CNN
F 1 "GS2" H 3650 4601 40  0000 C CNN
	1    3550 4750
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 510081F8
P 3500 3900
F 0 "R2" V 3580 3900 50  0000 C CNN
F 1 "100K" V 3500 3900 50  0000 C CNN
	1    3500 3900
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 510081F7
P 3350 3900
F 0 "R1" V 3430 3900 50  0000 C CNN
F 1 "100K" V 3350 3900 50  0000 C CNN
	1    3350 3900
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 510081C8
P 3650 3900
F 0 "R3" V 3730 3900 50  0000 C CNN
F 1 "100K" V 3650 3900 50  0000 C CNN
	1    3650 3900
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 510081AB
P 3800 3900
F 0 "R4" V 3880 3900 50  0000 C CNN
F 1 "100K" V 3800 3900 50  0000 C CNN
	1    3800 3900
	1    0    0    -1  
$EndComp
Text Label 4400 3600 2    60   ~ 0
3.3
$Comp
L CONN_10X2 P3
U 1 1 51008096
P 4400 4500
F 0 "P3" H 4400 5050 60  0000 C CNN
F 1 "JTAG CONNECTOR" V 4400 4500 50  0000 C CNN
	1    4400 4500
	1    0    0    -1  
$EndComp
Text Label 5200 4550 2    60   ~ 0
GND
Text Label 5200 4450 2    60   ~ 0
3.3
$Comp
L CONN_10 P4
U 1 1 51007D72
P 5750 4100
F 0 "P4" V 5700 4100 60  0000 C CNN
F 1 "CONN_10" V 5800 4100 60  0000 C CNN
	1    5750 4100
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
