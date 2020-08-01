#include <bits/stdc++.h>
using namespace std;

class BSTNode
{
public:
	int key;
	BSTNode *left;
	BSTNode *right;

	BSTNode(int k) : key(k), left(NULL), right(NULL) {}
};

class BST
{
private:
	BSTNode *root;

public:
	BST() : root(NULL) {}
	void InsertKey(int key)
	{
		this->root = InsertKeyHelper(this->root, key);
	}
	BSTNode *InsertKeyHelper(BSTNode *node, int key);

	void DeleteKey(int key)
	{
		this->root = DeleteKeyHelper(this->root, key);
	}
	BSTNode *DeleteKeyHelper(BSTNode *node, int key);

	void PrintInorder()
	{
		PrintInorderHelper(this->root);
	}
	void PrintInorderHelper(BSTNode *node);
};

void BST::PrintInorderHelper(BSTNode *node)
{
	if (node != NULL)
	{
		PrintInorderHelper(node->left);
		cout << (node->key) << " ";
		PrintInorderHelper(node->right);
	}
}

BSTNode *BST::InsertKeyHelper(BSTNode *node, int key)
{
	if (node == NULL)
	{
		return new BSTNode(key);
	}

	if (key < node->key)
	{
		node->left = InsertKeyHelper(node->left, key);
	}
	else
	{
		node->right = InsertKeyHelper(node->right, key);
	}
	return node;
}

BSTNode *BST::DeleteKeyHelper(BSTNode *node, int key)
{
	if (node == NULL)
	{
		return node;
	}

	if (node->key > key)
	{
		node->left = DeleteKeyHelper(node->left, key);
		return node;
	}
	else if (node->key < key)
	{
		node->right = DeleteKeyHelper(node->right, key);
		return node;
	}

	// If one of the children is empty
	if (node->left == NULL)
	{
		BSTNode *temp = node->right;
		delete node;
		return temp;
	}
	else if (node->right == NULL)
	{
		BSTNode *temp = node->left;
		delete node;
		return temp;
	}

	// If both children exist
	else
	{

		BSTNode *succParent = node;

		//find successor
		BSTNode *succ = node->right;
		while (succ->left != NULL)
		{
			succParent = succ;
			succ = succ->left;
		}

		if (succParent != node)
		{
			succParent->left = succ->right;
		}
		else
		{
			succParent->right = succ->right;
		}

		node->key = succ->key;
		delete succ;
		return node;
	}
}

int main()
{
	BST *bst = new BST();

	int q;
	cin >> q;

	int choice;
	int k;

	while (q--)
	{
		cin >> choice;

		//insert
		if (choice == 1)
		{
			cin >> k;
			bst->InsertKey(k);
		}
		//delete
		else if (choice == 2)
		{
			cin >> k;
			bst->DeleteKey(k);
		}
		//print BST
		else if (choice == 3)
		{
			bst->PrintInorder();
			cout << endl;
		}
	}
}
