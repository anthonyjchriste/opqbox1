FILES = rmsVoltage.cpp powerSpectrum.cpp main.cpp uartread.cpp coresettings.cpp acquisitiontask.cpp opqwebsocket.cpp opqwebsocket.cpp
OBJECTS = $(FILES:%.cpp=%.o)
LINK_FLAGS = `pkg-config --libs gsl` -lboost_system -lboost_thread
CPP = g++

%.o: %.cpp
	$(CPP) -c -o $@  $<

all: $(OBJECTS) easyws.o
	g++ $(OBJECTS) easyws.o -o opqd -g $(LINK_FLAGS)

easyws.o: contrib/easywsclient.cpp
	g++ contrib/easywsclient.cpp -c -o easyws.o

clean:
	rm -rf opqd *.o
