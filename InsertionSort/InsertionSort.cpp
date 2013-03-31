/*
 * InsertionSort.cpp
 * 插入排序，a0<=a1
 *  Created on: 2012-9-13
 *      Author: hf
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>

void InsertionSort(int A[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++)
	{
		key = A[i];
		j = i - 1;
		while (j >= 0 && A[j] > key)
		{
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = key;
	}
}

void print(int A[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	int A[] = { 12, 19, 1, 10, 14, 16, 4, 7, 9, 3, 2, 8, 5 };
	print(A, sizeof(A) / sizeof(int));
	InsertionSort(A, sizeof(A) / sizeof(int));
	print(A, sizeof(A) / sizeof(int));
	return 0;
}

