#include "header.h"

U_NS_STD

struct Node {
	int data;
	Node* left;
	Node* right;
	Node* parent;
};

struct Tree {
	Node* root;
};

void inorder(Node* x)
{
	if (x != NULL)
	{
		inorder(x->left);
		cout << x->data << " ";
		inorder(x->right);
	}
}

void preorder(Node* x)
{
	if (x != NULL)
	{
		cout << x->data << " ";
		preorder(x->left);
		preorder(x->right);
	}
}

void postorder(Node* x)
{
	if (x != NULL)
	{
		postorder(x->left);
		postorder(x->right);
		cout << x->data << " ";
	}
}

int maxDepth(Node* T)
{
	if (T == NULL)
		return 0;
	else
	{
		int lDepth = maxDepth(T->left);
		int rDepth = maxDepth(T->right);

		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}

Node* search(Node* x, int k)
{
	if (x == NULL || k == x->data)
		return x;
	if (k < x->data)
		return search(x->left, k);
	else
		return search(x->right, k);
}

Node* min(Node* x)
{
	if (x == NULL)
		return NULL;
	while (x->left != NULL)
		x = x->left;
	return x;
}

Node* max(Node* x)
{
	if (x == NULL)
		return NULL;
	while (x->right != NULL)
		x = x->right;
	return x;
}

Node* successor(Node* x)
{
	if (x == NULL)
		return NULL;
	if (x->right != NULL)
	{
		return min(x->right);
	}
	Node* y = x->parent;
	while (y != NULL && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

Node* predecessor(Node* x)
{
	if (x == NULL)
		return NULL;
	if (x->left != NULL)
	{
		return max(x->left);
	}
	Node* y = x->parent;
	while (y != NULL && x == y->left)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

void insert(Tree* T, Node* z)
{
	Node* y = NULL;
	Node* x = T->root;
	while (x != NULL)
	{
		y = x;
		if (z->data < x->data)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;
	if (y == NULL)
	{
		T->root = z;
	}
	else if (z->data < y->data)
		y->left = z;
	else
		y->right = z;
}

void transplant(Tree* T, Node* u, Node* v)
{
	if (u->parent == NULL)
		T->root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != NULL)
		v->parent = u->parent;
}

void del(Tree* T, Node* z)
{
	if (z->left == NULL)
		transplant(T, z, z->right);
	else if (z->right == NULL)
		transplant(T, z, z->left);
	else
	{
		Node* y = min(z->right);
		if (y->parent != z)
		{
			transplant(T, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(T, z, y);
		y->left = z->left;
		y->left->parent = y;
	}

	delete z;
}

int main()
{
	int choice = 0, value;
	Tree* tree = new Tree();

	do {
		cout << "\n\n";
		cout << "\n====== BST ======";
		cout << "\n [1] Insertion";
		cout << "\n [2] Deletion";
		cout << "\n [3] Search";
		cout << "\n [4] Minimum Value";
		cout << "\n [5] Maximium Value";
		cout << "\n [6] Successor";
		cout << "\n [7] Predecessor";
		cout << "\n [8] Traversals";
		cout << "\n [9] Depth";
		cout << "\n [0] Exit";

		cout << "\nEnter Choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			{
				cout << "\nEnter value: ";
				cin >> value;
				Node* z = new Node();
				z->data = value;
				insert(tree, z);
				break;
			}
		case 2:
			{
				cout << "\nEnter value: ";
				cin >> value;
				Node* e = search(tree->root, value);
				del(tree, e);
				break;
			}
		case 3:
			{
				cout << "\nEnter value: ";
				cin >> value;
				Node* e = search(tree->root, value);
				if (e != NULL) cout << "Value exists";
				else cout << "Value does not exists";
				break;
			}
		case 4:
			{
				Node* e = min(tree->root);
				if (e != NULL) cout << e->data << " ";
				else cout << "Minimum Value not present";
				break;
			}
		case 5:
			{
				Node* e = max(tree->root);
				if (e != NULL) cout << e->data << " ";
				else cout << "Maximum Value not present";
				break;
			}
		case 6:
		{
			cout << "\nEnter value: ";
			cin >> value;
			Node* e = search(tree->root, value);
			e = successor(e);
			if (e != NULL) cout << e->data << " ";
			else cout << "Successor does not exists";
			break;
		}
		case 7:
		{
			cout << "\nEnter value:";
			cin >> value;
			Node* e = search(tree->root, value);
			e = predecessor(e);
			if (e != NULL) cout << e->data << " ";
			else cout << "Predecessor does not exists";
			break;
		}
		case 8:
		{
			cout << "\nInorder is: \n";
			inorder(tree->root);
			cout << "\nPreorder is: \n";
			preorder(tree->root);
			cout << "\nPostorder is: \n";
			postorder(tree->root);
			break;
		}
		case 9:
		{
			cout << "\nDepth is: " << maxDepth(tree->root);
			break;
		}
		case 0:
		{
			return 0;
		}
		default:
			break;
		}
	} while (choice != 0);

	return 0;
}