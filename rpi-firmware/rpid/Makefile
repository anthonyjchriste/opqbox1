FILES = src/rmsVoltage.cpp src/powerSpectrum.cpp src/main.cpp src/uartread.cpp src/coresettings.cpp src/acquisitiontask.cpp src/opqwebsocket.cpp
OBJECTS = $(FILES:src/%.cpp=%.o)
LINK_FLAGS = `pkg-config --libs gsl` -lboost_system -lboost_thread
COMPILE_FLAGS = -I$(shell pwd)/lib/ -I$(shell pwd)/contrib

CPP = g++ -std=c++0x

%.o: src/%.cpp
	$(CPP) $(COMPILE_FLAGS) -c -o $@  $<

all: $(OBJECTS) easyws.o
	g++ $(OBJECTS) easyws.o -o opqd -g $(LINK_FLAGS)

easyws.o: contrib/easywsclient.cpp
	g++ contrib/easywsclient.cpp -c -o easyws.o

clean:
	rm -rf opqd *.o
