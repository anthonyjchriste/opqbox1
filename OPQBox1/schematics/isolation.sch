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
Sheet 2 2
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
L ZENER D?
U 1 1 54050D7B
P 2250 2050
F 0 "D?" H 2250 2150 50  0000 C CNN
F 1 "ZENER" H 2250 1950 40  0000 C CNN
F 2 "" H 2250 2050 60  0000 C CNN
F 3 "" H 2250 2050 60  0000 C CNN
	1    2250 2050
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 54050DA6
P 1050 2250
F 0 "R?" V 1130 2250 40  0000 C CNN
F 1 "R" V 1057 2251 40  0000 C CNN
F 2 "" V 980 2250 30  0000 C CNN
F 3 "" H 1050 2250 30  0000 C CNN
	1    1050 2250
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 54050DBD
P 3400 2050
F 0 "C?" H 3400 2150 40  0000 L CNN
F 1 "C" H 3406 1965 40  0000 L CNN
F 2 "" H 3438 1900 30  0000 C CNN
F 3 "" H 3400 2050 60  0000 C CNN
	1    3400 2050
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 54050DCF
P 1600 2550
F 0 "R?" V 1680 2550 40  0000 C CNN
F 1 "R" V 1607 2551 40  0000 C CNN
F 2 "" V 1530 2550 30  0000 C CNN
F 3 "" H 1600 2550 30  0000 C CNN
	1    1600 2550
	0    1    1    0   
$EndComp
$Comp
L GNDA #PWR?
U 1 1 54050E1A
P 3400 2500
F 0 "#PWR?" H 3400 2500 40  0001 C CNN
F 1 "GNDA" H 3400 2430 40  0000 C CNN
F 2 "" H 3400 2500 60  0000 C CNN
F 3 "" H 3400 2500 60  0000 C CNN
	1    3400 2500
	1    0    0    -1  
$EndComp
Text GLabel 3400 1550 1    60   Input ~ 0
UNISOLATED_5Vdc
Text Notes 2950 3700 0    60   ~ 0
Unisolated Power
$Comp
L amc1100 U?
U 1 1 54050FCC
P 7500 2650
F 0 "U?" H 7500 1900 60  0000 C CNN
F 1 "amc1100" H 7500 3300 60  0000 C CNN
F 2 "" H 8000 1900 60  0000 C CNN
F 3 "" H 8000 1900 60  0000 C CNN
	1    7500 2650
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 54050FE0
P 5800 2350
F 0 "C2" H 5800 2450 40  0000 L CNN
F 1 "0.1u" H 5806 2265 40  0000 L CNN
F 2 "" H 5838 2200 30  0000 C CNN
F 3 "" H 5800 2350 60  0000 C CNN
	1    5800 2350
	1    0    0    -1  
$EndComp
Text HLabel 2250 1500 1    60   Input ~ 0
AC_FUSED
Text GLabel 5800 1850 1    60   Input ~ 0
UNISOLATED_5Vdc
$Comp
L R R1
U 1 1 54051051
P 6150 2800
F 0 "R1" V 6230 2800 40  0000 C CNN
F 1 "12" V 6157 2801 40  0000 C CNN
F 2 "" V 6080 2800 30  0000 C CNN
F 3 "" H 6150 2800 30  0000 C CNN
	1    6150 2800
	0    1    1    0   
$EndComp
$Comp
L C C2
U 1 1 54051555
P 6500 3000
F 0 "C2" H 6500 3100 40  0000 L CNN
F 1 "330pF" H 6506 2915 40  0000 L CNN
F 2 "" H 6538 2850 30  0000 C CNN
F 3 "" H 6500 3000 60  0000 C CNN
	1    6500 3000
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 540515B2
P 6150 3200
F 0 "R2" V 6230 3200 40  0000 C CNN
F 1 "12" V 6157 3201 40  0000 C CNN
F 2 "" V 6080 3200 30  0000 C CNN
F 3 "" H 6150 3200 30  0000 C CNN
	1    6150 3200
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 54051699
P 5450 1650
F 0 "R?" V 5530 1650 40  0000 C CNN
F 1 "R" V 5457 1651 40  0000 C CNN
F 2 "" V 5380 1650 30  0000 C CNN
F 3 "" H 5450 1650 30  0000 C CNN
	1    5450 1650
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 540516AB
P 5450 2250
F 0 "R?" V 5530 2250 40  0000 C CNN
F 1 "R" V 5457 2251 40  0000 C CNN
F 2 "" V 5380 2250 30  0000 C CNN
F 3 "" H 5450 2250 30  0000 C CNN
	1    5450 2250
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 540516B6
P 5450 2850
F 0 "R?" V 5530 2850 40  0000 C CNN
F 1 "R" V 5457 2851 40  0000 C CNN
F 2 "" V 5380 2850 30  0000 C CNN
F 3 "" H 5450 2850 30  0000 C CNN
	1    5450 2850
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 540516C1
P 5450 3450
F 0 "R?" V 5530 3450 40  0000 C CNN
F 1 "R" V 5457 3451 40  0000 C CNN
F 2 "" V 5380 3450 30  0000 C CNN
F 3 "" H 5450 3450 30  0000 C CNN
	1    5450 3450
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 5405177C
P 5800 2950
F 0 "#PWR?" H 5800 2950 40  0001 C CNN
F 1 "GNDA" H 5800 2880 40  0000 C CNN
F 2 "" H 5800 2950 60  0000 C CNN
F 3 "" H 5800 2950 60  0000 C CNN
	1    5800 2950
	1    0    0    -1  
$EndComp
Text HLabel 5050 1400 0    60   Input ~ 0
AC_UNFILTERED
$Comp
L GND #PWR?
U 1 1 540518A2
P 8550 3350
F 0 "#PWR?" H 8550 3350 30  0001 C CNN
F 1 "GND" H 8550 3280 30  0001 C CNN
F 2 "" H 8550 3350 60  0000 C CNN
F 3 "" H 8550 3350 60  0000 C CNN
	1    8550 3350
	1    0    0    -1  
$EndComp
Text HLabel 8550 2850 2    60   Input ~ 0
ISOLATED_P
Text HLabel 8550 2550 2    60   Input ~ 0
ISOLATED_N
$Comp
L +3.3V #PWR?
U 1 1 540518DA
P 8550 2300
F 0 "#PWR?" H 8550 2260 30  0001 C CNN
F 1 "+3.3V" H 8550 2410 30  0000 C CNN
F 2 "" H 8550 2300 60  0000 C CNN
F 3 "" H 8550 2300 60  0000 C CNN
	1    8550 2300
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 54051986
P 10000 2700
F 0 "C1" H 10000 2800 40  0000 L CNN
F 1 "0.1u" H 10006 2615 40  0000 L CNN
F 2 "" H 10038 2550 30  0000 C CNN
F 3 "" H 10000 2700 60  0000 C CNN
	1    10000 2700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 54051998
P 10000 2250
F 0 "#PWR?" H 10000 2210 30  0001 C CNN
F 1 "+3.3V" H 10000 2360 30  0000 C CNN
F 2 "" H 10000 2250 60  0000 C CNN
F 3 "" H 10000 2250 60  0000 C CNN
	1    10000 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 540519A5
P 10000 3300
F 0 "#PWR?" H 10000 3300 30  0001 C CNN
F 1 "GND" H 10000 3230 30  0001 C CNN
F 2 "" H 10000 3300 60  0000 C CNN
F 3 "" H 10000 3300 60  0000 C CNN
	1    10000 3300
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 54051AB2
P 5450 3800
F 0 "#PWR?" H 5450 3800 40  0001 C CNN
F 1 "GNDA" H 5450 3730 40  0000 C CNN
F 2 "" H 5450 3800 60  0000 C CNN
F 3 "" H 5450 3800 60  0000 C CNN
	1    5450 3800
	1    0    0    -1  
$EndComp
$Comp
L DIODE D?
U 1 1 540525AC
P 2850 2250
F 0 "D?" H 2850 2350 40  0000 C CNN
F 1 "DIODE" H 2850 2150 40  0000 C CNN
F 2 "" H 2850 2250 60  0000 C CNN
F 3 "" H 2850 2250 60  0000 C CNN
	1    2850 2250
	-1   0    0    1   
$EndComp
$Comp
L C C?
U 1 1 540526CE
P 1600 2250
F 0 "C?" H 1600 2350 40  0000 L CNN
F 1 "C" H 1606 2165 40  0000 L CNN
F 2 "" H 1638 2100 30  0000 C CNN
F 3 "" H 1600 2250 60  0000 C CNN
	1    1600 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2250 1500 2250 1850
Connection ~ 3400 1850
Wire Notes Line
	3800 500  3800 3750
Wire Notes Line
	3800 3750 450  3750
Wire Wire Line
	5800 2550 6700 2550
Wire Wire Line
	6700 2150 6700 2300
Wire Wire Line
	5800 2150 6700 2150
Wire Wire Line
	2250 1850 3400 1850
Wire Wire Line
	3400 1850 3400 1550
Wire Wire Line
	5800 1850 5800 2150
Connection ~ 5800 2150
Connection ~ 2250 1850
Connection ~ 5800 2800
Wire Wire Line
	6400 2800 6700 2800
Connection ~ 6500 2800
Wire Wire Line
	5900 2800 5800 2800
Wire Wire Line
	6700 3200 6700 3050
Wire Wire Line
	6400 3200 6700 3200
Connection ~ 6500 3200
Wire Wire Line
	5450 1900 5450 2000
Wire Wire Line
	5450 2500 5450 2600
Wire Wire Line
	5450 3100 5450 3200
Wire Wire Line
	5050 1400 5450 1400
Wire Wire Line
	8300 3150 8550 3150
Wire Wire Line
	8550 3150 8550 3350
Wire Wire Line
	8300 2850 8550 2850
Wire Wire Line
	8300 2550 8550 2550
Wire Wire Line
	8300 2300 8550 2300
Connection ~ 5800 2550
Wire Wire Line
	10000 2250 10000 2500
Wire Wire Line
	10000 2900 10000 3300
Wire Wire Line
	5800 2550 5800 2950
Wire Wire Line
	5450 3200 5900 3200
Wire Wire Line
	5450 3700 5450 3800
Connection ~ 2250 2250
Wire Wire Line
	3050 2250 3400 2250
Wire Wire Line
	1800 2250 2650 2250
Wire Wire Line
	1850 2250 1850 2550
Connection ~ 1850 2250
Wire Wire Line
	1400 2250 1300 2250
Wire Wire Line
	1350 2250 1350 2550
Connection ~ 1350 2250
Wire Wire Line
	3400 2250 3400 2500
$EndSCHEMATC
