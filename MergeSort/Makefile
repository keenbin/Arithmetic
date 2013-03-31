CXXFLAGS =	 -g -Wall -fmessage-length=0

LIBS =


all:	MergeSort

TARGET = MergeSort


MergeSort_Objs = MergeSort.o

MergeSort:	$(MergeSort_Objs)
	$(CXX) -o $@ $(MergeSort_Objs) $(LIBS)

clean:
	rm -f *.o $(TARGET)
