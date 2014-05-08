FILES = src/rmsVoltage.cpp src/powerSpectrum.cpp src/main.cpp src/uartread.cpp src/coresettings.cpp src/acquisitiontask.cpp src/opqwebsocket.cpp src/opqpacket.cpp src/powertransformtask.cpp src/pinctl.cpp
OBJECTS = $(FILES:src/%.cpp=%.o)
LINK_FLAGS = `pkg-config --libs gsl` -lboost_system -lboost_thread
COMPILE_FLAGS = -I$(shell pwd)/lib/ -I$(shell pwd)/contrib

CPP = g++ -std=c++0x

%.o: src/%.cpp
	@$(CPP) $(COMPILE_FLAGS) -c -o $@  $<
	@echo $@
 
all: $(OBJECTS) base64de.o base64en.o easyws.o
	@g++ $(OBJECTS) easyws.o base64en.o base64de.o -o opqd -g $(LINK_FLAGS)
	@echo Linking

easyws.o: contrib/easywsclient.cpp
	@g++ contrib/easywsclient.cpp -c -o easyws.o
	@echo easyws.o

base64en.o: 
	@g++ contrib/base64/cencode.c -c -o base64en.o
	@echo base64en.o
base64de.o: contrib/base64/cencode.c contrib/base64/cdecode.c
	@g++ contrib/base64/cdecode.c -c -o base64de.o
	@echo base64de.o
clean:
	@rm -rf opqd $(OBJECTS) easyws.o base64de.o base64en.o
