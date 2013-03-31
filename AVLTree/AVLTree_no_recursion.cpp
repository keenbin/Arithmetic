#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

typedef struct node node;

struct node
{
	node* parent;
	node* left;
	node* right;
	int balance; //左右子树高度之差
	int key;
};

extern void traverseAVL1(node* root); //中序遍历, 下面定义

extern void traverseAVL2(node* root); //前序遍历, 下面定义

int searchNode(int key, node* root, node** parent) //按key查找结点
{
	node* temp;
	assert(root != NULL);
	temp = root;
	*parent = root->parent;
	while (temp != NULL)
	{
		if (temp->key == key)
			return 1;
		else
		{
			*parent = temp;
			if (temp->key > key)
				temp = temp->left;
			else
				temp = temp->right;
		}
	}
	return 0;

}

node* minNode(node* root) //树root的最小结点
{
	if (root == NULL)
		return NULL;
	while (root->left != NULL)
		root = root->left;
	return root;
}

node* maxNode(node* root) //树root的最大结点
{
	if (root == NULL)
		return NULL;
	while (root->right != NULL)
		root = root->right;
	return root;
}

node* preNode(node* target) //求前驱结点
{
	if (target == NULL)
		return NULL;
	if (target->left != NULL)
		return maxNode(target->left);
	else
		while ((target->parent != NULL) && (target != target->parent->right))
			target = target->parent;
	return target->parent;
}

node* nextNode(node* target) //求后继结点
{
	if (target == NULL)
		return NULL;
	if (target->right != NULL)
		return minNode(target->right);
	else
		while ((target->parent != NULL) && (target != target->parent->left))
			target = target->parent;
	return target->parent;
}

node* adjustAVL(node* root, node* parent, node* child)
{
	node *cur;
	assert((parent != NULL)&&(child != NULL));
	switch (parent->balance)
	{
	case 2:
		if (child->balance == -1) //LR型
		{
			cur = child->right;
			cur->parent = parent->parent;
			child->right = cur->left;
			if (cur->left != NULL)
				cur->left->parent = child;
			parent->left = cur->right;
			if (cur->right != NULL)
				cur->right->parent = parent;
			cur->left = child;
			child->parent = cur;
			cur->right = parent;
			if (parent->parent != NULL)
				if (parent->parent->left == parent)
					parent->parent->left = cur;
				else
					parent->parent->right = cur;
			else
				root = cur;
			parent->parent = cur;
			if (cur->balance == 0)
			{
				parent->balance = 0;
				child->balance = 0;
			}
			else if (cur->balance == -1)
			{
				parent->balance = 0;
				child->balance = 1;
			}
			else
			{
				parent->balance = -1;
				child->balance = 0;
			}
			cur->balance = 0;
		}
		else //LL型
		{
			child->parent = parent->parent;
			parent->left = child->right;
			if (child->right != NULL)
				child->right->parent = parent;
			child->right = parent;
			if (parent->parent != NULL)
				if (parent->parent->left == parent)
					parent->parent->left = child;
				else
					parent->parent->right = child;
			else
				root = child;
			parent->parent = child;
			if (child->balance == 1) //插入时
			{
				child->balance = 0;
				parent->balance = 0;
			}
			else //删除时
			{
				child->balance = -1;
				parent->balance = 1;
			}
		}
		break;

	case -2:
		if (child->balance == 1) //RL型
		{
			cur = child->left;
			cur->parent = parent->parent;
			child->left = cur->right;
			if (cur->right != NULL)
				cur->right->parent = child;
			parent->right = cur->left;
			if (cur->left != NULL)
				cur->left->parent = parent;
			cur->left = parent;
			cur->right = child;
			child->parent = cur;
			if (parent->parent != NULL)
				if (parent->parent->left == parent)
					parent->parent->left = cur;
				else
					parent->parent->right = cur;
			else
				root = cur;
			parent->parent = cur;
			if (cur->balance == 0)
			{
				parent->balance = 0;
				child->balance = 0;
			}
			else if (cur->balance == 1)
			{
				parent->balance = 0;
				child->balance = -1;
			}
			else
			{
				parent->balance = 1;
				child->balance = 0;
			}
			cur->balance = 0;
		}
		else //RR型
		{
			child->parent = parent->parent;
			parent->right = child->left;
			if (child->left != NULL)
				child->left->parent = parent;
			child->left = parent;
			if (parent->parent != NULL)
				if (parent->parent->left == parent)
					parent->parent->left = child;
				else
					parent->parent->right = child;
			else
				root = child;
			parent->parent = child;
			if (child->balance == -1) //插入时
			{
				child->balance = 0;
				parent->balance = 0;
			}
			else //删除时
			{
				child->balance = 1;
				parent->balance = -1;
			}
		}
		break;
	}
	return root;
}

node* insertNode(int key, node* root)
{
	node *parent, *cur, *child;
	assert(root != NULL);
	if (searchNode(key, root, &parent)) //结点已存在
		return root;
	else
	{
		cur = (node*) malloc(sizeof(node));
		cur->parent = parent;
		cur->key = key;
		cur->left = NULL;
		cur->right = NULL;
		cur->balance = 0;
		if (key < parent->key)
		{
			parent->left = cur;
			child = parent->left;
		}
		else
		{
			parent->right = cur;
			child = parent->right;
		}

		while ((parent != NULL)) //查找需要调整的最小子树
		{
			if (child == parent->left)
				if (parent->balance == -1)
				{
					parent->balance = 0;
					return root;
				}
				else if (parent->balance == 1)
				{
					parent->balance = 2;
					break;
				}
				else
				{
					parent->balance = 1;
					child = parent;
					parent = parent->parent;
				}
			else if (parent->balance == 1)
			{
				parent->balance = 0;
				return root;
			}
			else if (parent->balance == -1)
			{
				parent->balance = -2;
				break;
			}
			else
			{
				parent->balance = -1;
				child = parent;
				parent = parent->parent;
			}
		}

		if (parent == NULL)
			return root;
		return adjustAVL(root, parent, child);
	}
}

node* deleteNode(int key, node* root)
{
	node *dNode, *parent, *child, *tp;
	int temp, tc;
	assert(root!=NULL);
	if (!searchNode(key, root, &parent))
		return root;
	else
	{
		if (parent == NULL)
			dNode = root;
		else if ((parent->left != NULL) && (parent->left->key == key))
			dNode = parent->left;
		else
			dNode = parent->right;

		child = dNode;
		while ((child->left != NULL) || (child->right != NULL)) //确定需要删除的结点
		{
			if (child->balance == 1)
				child = preNode(dNode);
			else
				child = nextNode(dNode);
			temp = child->key;
			child->key = dNode->key;
			dNode->key = temp;
			dNode = child;
		}

		child = dNode;
		parent = dNode->parent;

		while ((parent != NULL)) //查找需要调整的最小子树
		{
			if (child == parent->left)
				if (parent->balance == 1)
				{
					parent->balance = 0;
					child = parent;
					parent = parent->parent;
				}
				else if (parent->balance == -1)
				{
					parent->balance = -2;
					child = parent->right;
					temp = parent->right->balance; //临时变量保存
					tp = parent->parent; //临时变量保存
					if (tp != NULL)
						if (parent == tp->left)
							tc = 1;
						else
							tc = -1;
					else
						tc = 0;

					root = adjustAVL(root, parent, child);

					if (temp == 0)
						break;
					else
					{
						if (tc == 1)
							child = tp->left;
						else if (tc == -1)
							child = tp->right;
						parent = tp;
					}

				}
				else
				{
					parent->balance = -1;
					break;
				}
			else if (parent->balance == -1)
			{
				parent->balance = 0;
				child = parent;
				parent = parent->parent;
			}
			else if (parent->balance == 1)
			{
				parent->balance = 2;
				child = parent->left;
				temp = parent->left->balance; //临时变量保存
				tp = parent->parent; //临时变量保存
				if (tp != NULL)
					if (parent == tp->left)
						tc = 1;
					else
						tc = -1;
				else
					tc = 0;

				root = adjustAVL(root, parent, child);

				if (temp == 0)
					break;
				else
				{
					if (tc == 1)
						child = tp->left;
					else if (tc == -1)
						child = tp->right;
					parent = tp;
				}
			}
			else
			{
				parent->balance = 1;
				break;
			}
		}

		if (dNode->parent != NULL)
		{
			if (dNode == dNode->parent->left)
				dNode->parent->left = NULL;
			else
				dNode->parent->right = NULL;
		}
		free(dNode);
		if (root == dNode)
			root = NULL; //root被删除, 避免野指针
		dNode = NULL;

		return root;
	}
}

node* createAVL(int *data, int size)
{
	int i;
	node *root;
	if (size < 1)
		return NULL;
	root = (node*) malloc(sizeof(node));
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
	root->key = data[0];
	root->balance = 0;

	for (i = 1; i < size; i++)
		root = insertNode(data[i], root);
	return root;
}

void destroyAVL(node* root)
{
	if (root != NULL)
	{
		destroyAVL(root->left);
		destroyAVL(root->right);
		free(root);
		root = NULL;
	}

}

void traverseAVL1(node* root) //中序遍历
{
	if (root != NULL)
	{
		traverseAVL1(root->left);
		printf("%d, %d\n", root->key, root->balance);
		traverseAVL1(root->right);
	}
}

void traverseAVL2(node* root) //先序遍历
{
	if (root != NULL)
	{
		printf("%d, %d\n", root->key, root->balance);
		traverseAVL2(root->left);
		traverseAVL2(root->right);
	}
}

int main(int argc, char *argv[])
{
	int data[] = { 1, 5, 7, 4, 3, 2, 11, 9, 10 };
	node* root;
	root = createAVL(data, sizeof(data) / sizeof(data[0]));

	printf("++++++++++++++++++++++++++++\n");
	traverseAVL1(root);
	printf("\n");
	traverseAVL2(root);

	root = deleteNode(5, root);
	printf("++++++++++++++++++++++++++++\n");
	traverseAVL1(root);
	printf("\n");
	traverseAVL2(root);

	root = deleteNode(3, root);
	printf("++++++++++++++++++++++++++++\n");
	traverseAVL1(root);
	printf("\n");
	traverseAVL2(root);

	root = deleteNode(1, root);
	printf("++++++++++++++++++++++++++++\n");
	traverseAVL1(root);
	printf("\n");
	traverseAVL2(root);

	root = deleteNode(7, root);
	printf("++++++++++++++++++++++++++++\n");
	traverseAVL1(root);
	printf("\n");
	traverseAVL2(root);

	root = deleteNode(4, root);
	printf("++++++++++++++++++++++++++++\n");
	traverseAVL1(root);
	printf("\n");
	traverseAVL2(root);

	root = deleteNode(2, root);
	printf("++++++++++++++++++++++++++++\n");
	traverseAVL1(root);
	printf("\n");
	traverseAVL2(root);

	destroyAVL(root);
}
