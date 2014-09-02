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
Sheet 1 2
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
P 3600 1450
F 0 "U?" H 3600 2000 60  0000 C CNN
F 1 "PBK-1" H 3600 550 60  0000 C CNN
F 2 "" H 3600 1450 60  0000 C CNN
F 3 "" H 3600 1450 60  0000 C CNN
	1    3600 1450
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 53FFD1AF
P 2350 1950
F 0 "C?" H 2400 2050 50  0000 L CNN
F 1 "CP1" H 2400 1850 50  0000 L CNN
F 2 "" H 2350 1950 60  0000 C CNN
F 3 "" H 2350 1950 60  0000 C CNN
	1    2350 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 1750 2350 1750
Wire Wire Line
	2950 1900 2950 2150
Wire Wire Line
	2950 2150 2350 2150
$Comp
L INDUCTOR_SMALL L?
U 1 1 53FFD1DA
P 2400 1300
F 0 "L?" H 2400 1400 50  0000 C CNN
F 1 "INDUCTOR_SMALL" H 2400 1250 50  0000 C CNN
F 2 "" H 2400 1300 60  0000 C CNN
F 3 "" H 2400 1300 60  0000 C CNN
	1    2400 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 1300 2650 1300
Wire Wire Line
	2950 1450 2150 1450
Wire Wire Line
	2150 2050 2150 1450
Wire Wire Line
	1300 2050 2150 2050
Wire Wire Line
	1300 1300 2150 1300
$Comp
L MOV U?
U 1 1 53FFD2B8
P 1050 1700
F 0 "U?" H 1050 2000 60  0000 C CNN
F 1 "MOV" H 1050 1500 60  0000 C CNN
F 2 "" H 1050 1700 60  0000 C CNN
F 3 "" H 1050 1700 60  0000 C CNN
	1    1050 1700
	0    1    1    0   
$EndComp
Wire Wire Line
	1300 1300 1300 1200
Wire Wire Line
	1300 1200 1100 1200
Wire Wire Line
	1300 2050 1300 2250
Wire Wire Line
	1300 2250 1100 2250
$Sheet
S 6550 1400 2350 2450
U 540507FD
F0 "Isolation" 50
F1 "isolation.sch" 50
F2 "AC_FUSED" I L 6550 1800 60 
F3 "AC_UNFILTERED" I L 6550 2100 60 
F4 "ISOLATED_P" I L 6550 2450 60 
F5 "ISOLATED_N" I L 6550 2700 60 
$EndSheet
$EndSCHEMATC
