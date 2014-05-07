FILES= rmsVoltage.cpp powerSpectrum.cpp main.cpp uartread.cpp coresettings.cpp acquisitiontask.cpp
all:
	g++ $(FILES) -o opqd -g `pkg-config --libs gsl` -lboost_system -lboost_thread

clean:
	rm -rf opqd
