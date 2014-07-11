FILES = src/rmsvoltage.cpp src/powerspectrum.cpp src/uartread.cpp src/coresettings.cpp src/acquisitiontask.cpp src/opqwebsocket.cpp src/opqpacket.cpp src/powertransformtask.cpp src/pinctl.cpp src/gausianpeak.cpp src/analysistask.cpp src/filtertask.cpp
OBJECTS = $(FILES:src/%.cpp=%.o)
LINK_FLAGS = `pkg-config --libs gsl` -lboost_system -lboost_thread
COMPILE_FLAGS = -I$(shell pwd)/lib/ -I$(shell pwd)/contrib -std=c++0x

CPP = g++

%.o: src/%.cpp
	@echo -n "$@\t\t\t\t"
	@time -f "%E" $(CPP) $(COMPILE_FLAGS) -c -o $@  $<
 
all: $(OBJECTS) easyws.o
	@echo -n "Linking\t\t\t\t"
	@time -f "%E" $(CPP) $(OBJECTS) $(COMPILE_FLAGS) easyws.o src/main.cpp -o opqd $(LINK_FLAGS)

easyws.o: contrib/easywsclient.cpp
	@$(CPP) contrib/easywsclient.cpp -c -o easyws.o
	@echo easyws.o

clean:
	@rm -rf opqd $(OBJECTS) easyws.o

install: all
	mkdir -p /usr/local/opqd
	cp settings.set /usr/local/opqd
	cp opqd.sh /ect/init.d/opqd
	chmod 755 opqd
	update-rc opqd defaults
	cp opqd /usr/local/bin
