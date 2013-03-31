/*
 * HeapSort.cpp
 * 大根堆排序
 *  Created on: 2012-9-13
 *      Author: hf
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>

const int HEAP_SIZE = 13;  //堆大小

inline int parent(int);
inline int left(int);
inline int right(int);
void Max_Heapify(int[], int, int);
void Build_Max_Heap(int[]);
void print(int[]);
void HeapSort(int[], int);

int parent(int i)
{
	return (int) floor(i / 2);
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return (2 * i + 2);
}

//将堆的末端子结点作调整，使得子结点永远小于父结点
void Max_Heapify(int A[], int i, int heap_size)
{
	if (i > heap_size / 2 - 1)
		return;
	int l = left(i);
	int r = right(i);
	int largest;
	int temp;

	if (l < heap_size && A[l] > A[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	if (r < heap_size && A[r] > A[largest])
	{
		largest = r;
	}
	if (largest != i)
	{
		temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;
		Max_Heapify(A, largest, heap_size);
	}
}

//将堆所有数据重新排序
void Build_Max_Heap(int A[])
{
	for (int i = (HEAP_SIZE) / 2 - 1; i >= 0; i--)
	{
		Max_Heapify(A, i, HEAP_SIZE);
	}
}

void print(int A[])
{
	for (int i = 0; i < HEAP_SIZE; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
}

//堆排序
void HeapSort(int A[], int heap_size)
{
	Build_Max_Heap(A);
	print(A);
	int temp;
	for (int i = heap_size - 1; i > 0; i--)
	{
		temp = A[0];
		A[0] = A[i];
		A[i] = temp;
		Max_Heapify(A, 0, i);
		print(A);
	}
	print(A);
}

int main(int argc, char* argv[])
{
	int A[HEAP_SIZE] =
	{ 12, 19, 1, 10, 14, 16, 4, 7, 9, 3, 2, 8, 5 };
	print(A);
	HeapSort(A, HEAP_SIZE);
	print(A);
	return 0;
}

