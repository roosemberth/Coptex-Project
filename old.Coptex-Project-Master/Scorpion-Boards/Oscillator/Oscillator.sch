EESchema Schematic File Version 2  date ven. 31 mai 2013 18:42:13 CST
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
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "1 jun 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 5950 4950
Wire Wire Line
	6600 4950 6700 4950
Wire Wire Line
	6700 4950 6700 4350
Wire Wire Line
	6700 4350 5450 4350
Connection ~ 5950 4350
Wire Wire Line
	5950 5100 5800 5100
Wire Wire Line
	5800 5100 5800 4800
Wire Wire Line
	5800 4800 6850 4800
Wire Wire Line
	6850 4800 6850 3200
Connection ~ 6500 3200
Wire Wire Line
	6850 3200 6500 3200
Wire Wire Line
	5000 3500 5000 2850
Wire Wire Line
	5000 2850 6500 2850
Wire Wire Line
	6500 2850 6500 3500
Connection ~ 5050 4450
Wire Wire Line
	5050 4450 5050 4750
Wire Wire Line
	5400 3800 5400 4350
Wire Wire Line
	5400 4350 5250 4350
Wire Wire Line
	5250 4350 5250 4450
Wire Wire Line
	5250 4450 3900 4450
Wire Wire Line
	3900 4450 3900 3800
Wire Wire Line
	5600 5300 5600 5350
Wire Wire Line
	5600 5350 4850 5350
Wire Wire Line
	4450 5350 4450 4750
Wire Wire Line
	5050 4750 4850 4750
Connection ~ 5000 4750
Connection ~ 5000 5350
Wire Wire Line
	5600 4750 5550 4750
Wire Wire Line
	5600 4750 5600 4800
Wire Wire Line
	4450 5050 4300 5050
Connection ~ 4450 5050
Wire Wire Line
	4300 5050 4300 4350
Wire Wire Line
	5000 3800 5200 3800
Wire Wire Line
	5200 3800 5200 4400
Wire Wire Line
	5200 4400 5350 4400
Wire Wire Line
	5350 4400 5350 4450
Wire Wire Line
	5350 4450 6750 4450
Wire Wire Line
	6750 4450 6750 3800
Wire Wire Line
	6750 3800 6500 3800
Wire Wire Line
	5550 4750 5550 4450
Connection ~ 5550 4450
Wire Wire Line
	4300 4350 5150 4350
Wire Wire Line
	5150 4350 5150 4300
Wire Wire Line
	5150 4300 5450 4300
Wire Wire Line
	5450 4300 5450 4350
Connection ~ 4450 4350
Wire Wire Line
	4450 3000 6800 3000
Wire Wire Line
	6800 3000 6800 5100
Wire Wire Line
	6800 5100 6600 5100
Connection ~ 5950 3000
$Comp
L OSCILATOR OSC1
U 1 1 51A9418D
P 6050 5150
F 0 "OSC1" H 6450 5425 30  0000 C CNN
F 1 "OSCILATOR" H 6275 5275 20  0000 C CNN
	1    6050 5150
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 51A94016
P 5600 5050
F 0 "R2" V 5680 5050 50  0000 C CNN
F 1 "Rs" V 5600 5050 50  0000 C CNN
	1    5600 5050
	1    0    0    1   
$EndComp
$Comp
L R R1
U 1 1 51A9400D
P 5300 4750
F 0 "R1" V 5380 4750 50  0000 C CNN
F 1 "Rf" V 5300 4750 50  0000 C CNN
	1    5300 4750
	0    -1   1    0   
$EndComp
$Comp
L C C1
U 1 1 51A93FE8
P 4650 4750
F 0 "C1" H 4700 4850 50  0000 L CNN
F 1 "32pF" H 4700 4650 50  0000 L CNN
	1    4650 4750
	0    1    -1   0   
$EndComp
$Comp
L C C2
U 1 1 51A93FD6
P 4650 5350
F 0 "C2" H 4700 5450 50  0000 L CNN
F 1 "32pF" H 4700 5250 50  0000 L CNN
	1    4650 5350
	0    1    -1   0   
$EndComp
$Comp
L CRYSTAL X1
U 1 1 51A93FCC
P 5000 5050
F 0 "X1" H 5000 5200 60  0000 C CNN
F 1 "CRYSTAL" H 5000 4900 60  0000 C CNN
	1    5000 5050
	0    1    -1   0   
$EndComp
$Comp
L SN74LVC1GX04 CLK-OSC2
U 1 1 51A93F9B
P 5950 3700
F 0 "CLK-OSC2" H 5600 4200 60  0000 C CNN
F 1 "SN74LVC1GX04" H 6350 3200 60  0000 C CNN
	1    5950 3700
	1    0    0    -1  
$EndComp
$Comp
L SN74LVC1GX04 CLK-OSC1
U 1 1 51A93F95
P 4450 3700
F 0 "CLK-OSC1" H 4100 4200 60  0000 C CNN
F 1 "SN74LVC1GX04" H 4850 3200 60  0000 C CNN
	1    4450 3700
	1    0    0    -1  
$EndComp
$EndSCHEMATC
