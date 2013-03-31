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
#include <limits.h>
#include <iostream>
using namespace std;
void print(int A[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
}
/**
 * R[p,q]
 * L[q+1,r]
 */
void Merge(int A[], int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int *L = new int[n1 + 1];
	int *R = new int[n2 + 1];
	int i, j, k;

	for (i = 0; i < n1; i++)
		L[i] = A[p + i];
	L[n1] = INT_MAX;
	for (j = 0; j < n2; j++)
		R[j] = A[q + 1 + j];
	R[n2] = INT_MAX;

	i = 0;
	j = 0;
	for (k = p; k <= r; k++)
	{
		if (i != n1 + 1 && L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
	}
	delete[] L;
	delete[] R;
}

void merge_sort(int *list, int length)
{
	int i, left_min, left_max, right_min, right_max, next;
	int *tmp = (int*) malloc(sizeof(int) * length);
	if (tmp == NULL)
	{
		fputs("Error: out of memory\n", stderr);
		abort();
	}
	for (i = 1; i < length; i *= 2)
	{
		for (left_min = 0; left_min < length - i; left_min = right_max)
		{
			right_min = left_max = left_min + i;
			right_max = left_max + i;
			if (right_max > length)
				right_max = length;
			next = 0;
			while (left_min < left_max && right_min < right_max)
			{
				tmp[next++] =
						list[left_min] > list[right_min] ?
								list[right_min++] : list[left_min++];
			}
			while (left_min < left_max)
				list[--right_min] = list[--left_max];
			while (next > 0)
				list[--right_min] = tmp[--next];

			cout<<"after"<<endl;
			print(list,right_max);
			cout<<"after end"<<endl;
		}
	}
	free(tmp);
}
/**
 * A[p,r]
 */
void MergeSort(int A[], int p, int r)
{
	if (p < r)
	{
		int q = (r + p) / 2;
		MergeSort(A, p, q);
		MergeSort(A, q + 1, r);
		Merge(A, p, q, r);
	}
}
int main(int argc, char* argv[])
{
//cout << numeric_limits<int>::max() << endl; //sentinel card 哨兵牌
	cout << (int) 0x7fffffff << endl;

	int A[] = { 12, 2147483647, 19, 1, 2147483647, 2147483647, 2147483647, 2147483647 };
	print(A, sizeof(A) / sizeof(int));
	merge_sort(A, (sizeof(A) / sizeof(int)));
	//MergeSort(A, 0, (sizeof(A) / sizeof(int)) - 1);
	print(A, sizeof(A) / sizeof(int));
	return 0;
}

