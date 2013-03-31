CXXFLAGS =	 -g -Wall -fmessage-length=0

LIBS =



TARGET = serv client

all:	$(TARGET)


serv_obj = Serv.o

serv:	$(serv_obj)
	$(CXX) -o $@ $(serv_obj) $(LIBS)

cli_obj = Client.o
client:	$(cli_obj)
	$(CXX) -o $@ $(cli_obj) $(LIBS)

clean:
	rm -f *.o $(TARGET)
