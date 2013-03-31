CXXFLAGS =	 -g -Wall -fmessage-length=0

LIBS =


all:	crc16

TARGET = crc16


CRC16_Objs = crc16.o

crc16:	$(CRC16_Objs)
	$(CXX) -o $@ $(CRC16_Objs) $(LIBS)

clean:
	rm -f *.o $(TARGET)
