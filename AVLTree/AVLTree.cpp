/*
 * AVLTree.cpp
 * AVLTree操作
 *  Created on: 2013-3-26
 *      Author: keenbin
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
using namespace std;
typedef struct Node* Tree;
typedef struct Node* Node_t;

typedef int Type;

struct Node
{
	Node_t left;
	Node_t right;
	int height;
	Type data;
};
int Height(Node_t node)
{
	if (node)
		return node->height;
	return 0;
}

int Max(int n, int m)
{
	if (n > m)
		return n;
	return m;
}

//右旋
Node_t RightRotate(Node_t a)
{
	Node_t b = a->left;
	a->left = b->right;
	b->right = a;
	a->height = Max(Height(a->left), Height(a->right));
	b->height = Max(Height(b->left), Height(b->right));
	return b;
}
//左旋
Node_t LeftRotate(Node_t a)
{
	Node_t b = a->right;
	a->right = b->left;
	b->left = a;
	a->height = Max(Height(a->left), Height(a->right));
	b->height = Max(Height(b->left), Height(b->right));
	return b;
}
//左右旋
Node_t LeftRightRotate(Node_t a)
{
	a->left = LeftRotate(a->left);
	return RightRotate(a);
}
//右左旋
Node_t RightLeftRotate(Node_t a)
{
	a->right = RightRotate(a->right);
	return LeftRotate(a);
}

Node_t NewNode(Type t)
{
	Node_t pn = (Node_t) malloc(sizeof(Node));
	if (!pn)
		return NULL;
	pn->left = pn->right = NULL;
	pn->data = t;
	pn->height = 1;
	return pn;
}
//插入节点
Node_t Insert(Type x, Tree t)
{
	if (t == NULL)
	{
		t = NewNode(x);
	}
	else if (x < t->data)
	{
		t->left = Insert(x, t->left);
		if (Height(t->left) - Height(t->right) == 2)
		{
			if (x < t->left->data)
			{
				t = RightRotate(t);
			}
			else
			{
				t = LeftRightRotate(t);
			}
		}
	}
	else
	{
		t->right = Insert(x, t->right);
		if (Height(t->right) - Height(t->left) == 2)
		{
			if (x > t->right->data)
			{
				t = LeftRotate(t);
			}
			else
			{
				t = RightLeftRotate(t);
			}
		}
	}
	t->height = Max(Height(t->left), Height(t->right)) + 1;
	return t;
}

Node_t Rotate(Type x, Node_t t)
{
	if (t == NULL)
	{
		return NULL;
	}
	else if (x < t->data)
	{
		if (Height(t->left) - Height(t->right) == 2)
		{
			if (x < t->left->data)
			{
				t = LeftRightRotate(t);
			}
			else
			{
				t = RightRotate(t);
			}
		}
	}
	else
	{
		if (Height(t->right) - Height(t->left) == 2)
		{
			if (x > t->right->data)
			{
				t = RightLeftRotate(t);
			}
			else
			{
				t = LeftRotate(t);
			}
		}
	}
	t->height = Max(Height(t->left), Height(t->right)) + 1;
	return t;
}

Node_t Delete(Type x, Tree t)
{
	if (t == NULL)
		return NULL;
	if (t->data == x)
	{
		if (t->right == NULL)
		{
			Node_t temp = t;
			t = t->left;
			free(temp);
		}
		else
		{
			Node_t head = t->right;
			while (head->left)
			{
				head = head->left;
			}
			t->data = head->data; //just copy data
			t->right = Delete(t->data, t->right);
			t->height = Max(Height(t->left), Height(t->right)) + 1;
		}
	}
	else if (t->data < x)
	{
		t->right = Delete(x, t->right);
		if (t->right)
			t->right = Rotate(x, t->right);
	}
	else
	{
		t->left = Delete(x, t->left);
		if (t->left)
			t->left = Rotate(x, t->left);
	}
	if (t)
		t = Rotate(x, t);

	return t;
}

Node_t createAVL(int data[], int len)
{
	Node_t root = NULL;
	;
	for (int i = 0; i < len; i++)
	{
		root = Insert(data[i], root);
	}
	return root;
}
void traverseAVL1(Tree root) //中序遍历
{
	if (root != NULL)
	{
		traverseAVL1(root->left);
		printf("%d,\t%d,\t%d\n", root->data, root->height,
				Height(root->left) - Height(root->right));
		traverseAVL1(root->right);
	}
}

void traverseAVL2(Tree root) //先序遍历
{
	if (root != NULL)
	{
		printf("%d,\t%d,\t%d\n", root->data, root->height,
				Height(root->left) - Height(root->right));
		traverseAVL2(root->left);
		traverseAVL2(root->right);
	}
}

void destroyAVL(Tree root)
{
	if (root != NULL)
	{
		destroyAVL(root->left);
		destroyAVL(root->right);
		free(root);
		root = NULL;
	}

}
int main()
{
	int data[] = { 1, 5, 7, 4, 3, 2, 11, 9, 10 };
	Tree root;
	root = createAVL(data, sizeof(data) / sizeof(data[0]));

	traverseAVL1(root);
	printf("+++++++++++++++++++++++++++++++++++++++\n");

	root = Delete(5, root);
	traverseAVL1(root);
	printf("+++++++++++++++++++++++++++++++++++++++\n");
	root = Delete(9, root);
	traverseAVL1(root);

	destroyAVL(root);
}
