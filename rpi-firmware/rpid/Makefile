FILES = src/rmsVoltage.cpp src/powerSpectrum.cpp src/uartread.cpp src/coresettings.cpp src/acquisitiontask.cpp src/opqwebsocket.cpp src/opqpacket.cpp src/powertransformtask.cpp src/pinctl.cpp src/gausianpeak.cpp src/analysistask.cpp src/filtertask.cpp
OBJECTS = $(FILES:src/%.cpp=%.o)
LINK_FLAGS = `pkg-config --libs gsl` -lboost_system -lboost_thread
COMPILE_FLAGS = -I$(shell pwd)/lib/ -I$(shell pwd)/contrib -std=gnu++11

CPP = g++ -std=c++0x

%.o: src/%.cpp
	@$(CPP) $(COMPILE_FLAGS) -c -o $@  $<
	@echo $@
 
all: $(OBJECTS) easyws.o
	@g++ $(OBJECTS) $(COMPILE_FLAGS) easyws.o src/main.cpp -o opqd $(LINK_FLAGS)
	@echo Linking

anthony: $(OBJECTS) easyws.o
	@g++ $(OBJECTS) $(COMPILE_FLAGS) easyws.o src/main.cpp -o opqd $(LINK_FLAGS) -DANTHONY_MAIN
	@echo Linking
	

easyws.o: contrib/easywsclient.cpp
	@g++ contrib/easywsclient.cpp -c -o easyws.o
	@echo easyws.o

clean:
	@rm -rf opqd $(OBJECTS) easyws.o
