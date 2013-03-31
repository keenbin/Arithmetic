CXXFLAGS =	 -g -Wall -fmessage-length=0

LIBS =


all:	avltree avltree_no_recursion

TARGET = avltree avltree_no_recursion 


AVLTree_Objs = AVLTree.o

AVLTree_no_recursion_Objs = AVLTree_no_recursion.o

avltree:	$(AVLTree_Objs)
	$(CXX) -o $@ $(AVLTree_Objs) $(LIBS)
	
avltree_no_recursion:	$(AVLTree_no_recursion_Objs)
	$(CXX) -o $@ $(AVLTree_no_recursion_Objs) $(LIBS)

clean:
	rm -f *.o $(TARGET)
