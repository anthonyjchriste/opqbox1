FILES= rmsVoltage.cpp powerSpectrum.cpp main.cpp uartread.cpp
all:
	g++ $(FILES) -o opqd -g `pkg-config --libs gsl`

clean:
	rm -rf opqd
