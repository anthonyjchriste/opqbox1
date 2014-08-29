EESchema Schematic File Version 2
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
LIBS:OPQBox1
LIBS:OPQBox1-cache
EELAYER 24 0
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
L PBK-1 U?
U 1 1 53FEEAF4
P 5150 3000
F 0 "U?" H 5150 3550 60  0000 C CNN
F 1 "PBK-1" H 5150 2100 60  0000 C CNN
F 2 "" H 5150 3000 60  0000 C CNN
F 3 "" H 5150 3000 60  0000 C CNN
	1    5150 3000
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 53FFD1AF
P 3900 3500
F 0 "C?" H 3950 3600 50  0000 L CNN
F 1 "CP1" H 3950 3400 50  0000 L CNN
F 2 "" H 3900 3500 60  0000 C CNN
F 3 "" H 3900 3500 60  0000 C CNN
	1    3900 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3300 3900 3300
Wire Wire Line
	4500 3450 4500 3700
Wire Wire Line
	4500 3700 3900 3700
$Comp
L INDUCTOR_SMALL L?
U 1 1 53FFD1DA
P 3950 2850
F 0 "L?" H 3950 2950 50  0000 C CNN
F 1 "INDUCTOR_SMALL" H 3950 2800 50  0000 C CNN
F 2 "" H 3950 2850 60  0000 C CNN
F 3 "" H 3950 2850 60  0000 C CNN
	1    3950 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2850 4200 2850
Wire Wire Line
	4500 3000 3700 3000
Wire Wire Line
	3700 3600 3700 3000
Wire Wire Line
	2850 3600 3700 3600
Wire Wire Line
	2850 2850 3700 2850
$Comp
L MOV U?
U 1 1 53FFD2B8
P 2600 3250
F 0 "U?" H 2600 3550 60  0000 C CNN
F 1 "MOV" H 2600 3050 60  0000 C CNN
F 2 "" H 2600 3250 60  0000 C CNN
F 3 "" H 2600 3250 60  0000 C CNN
	1    2600 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	2850 2850 2850 2750
Wire Wire Line
	2850 2750 2650 2750
Wire Wire Line
	2850 3600 2850 3800
Wire Wire Line
	2850 3800 2650 3800
$EndSCHEMATC
