CXXFLAGS =	 -g -Wall -fmessage-length=0

LIBS =


all:	InsertionSort

TARGET = $(InsertionSort)

InsertionSort =	InsertionSort

InsertionSort_Objs = InsertionSort.o

$(InsertionSort):	$(InsertionSort_Objs)
	$(CXX) -o $(InsertionSort) $(InsertionSort_Objs) $(LIBS)

clean:
	rm -f *.o $(TARGET)
