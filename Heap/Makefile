CXXFLAGS =	 -g -Wall -fmessage-length=0

LIBS =


HeapSort =	HeapSort

HeapSort_Objs = HeapSort.o

$(HeapSort):	$(HeapSort_Objs)
	$(CXX) -o $(HeapSort) $(HeapSort_Objs) $(LIBS)

all:	$(HeapSort)

TARGET = $(HeapSort)

clean:
	rm -f *.o $(TARGET)
