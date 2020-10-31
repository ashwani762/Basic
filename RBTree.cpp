#include "header.h"

#define RED 1
#define BLACK 0

U_NS_STD

struct Node {
	int data;
	bool color; // 0 for Black, 1 for Red
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

void left_rotate(Tree* T, Node* x)
{
	Node* y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		T->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void right_rotate(Tree* T, Node* x)
{
	Node* y = x->left;
	x->left = y->right;
	if (y->right != NULL)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		T->root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;
	y->right = x;
	x->parent = y;
}

void rb_insert_fixup(Tree* T, Node* z)
{
	while (z->parent != NULL && z->parent->color == RED)
	{
		if (z->parent == z->parent->parent->left)
		{
			Node* y = z->parent->parent->right;
			if (y != NULL && y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->right)
				{
					z = z->parent;
					left_rotate(T, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(T, z->parent->parent);
			}
		}
		else
		{
			Node* y = z->parent->parent->left;
			if (y != NULL && y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->left)
				{
					z = z->parent;
					right_rotate(T, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(T, z->parent->parent);
			}
		}
	}
	T->root->color = BLACK;
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

	z->left = NULL;
	z->right = NULL;
	z->color = RED;

	rb_insert_fixup(T, z);
}

void transplant(Tree* T, Node* u, Node* v)
{
	if (u->parent == NULL)
		T->root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if(v != nullptr)
		v->parent = u->parent;
}

void rb_del_fixup(Tree* T, Node* x)
{
	while (x != NULL && x->color == BLACK)
	{
		if (x == x->parent->left)
		{
			Node* w = x->parent->right;
			if (w != NULL && w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate(T, x->parent);
				w = x->parent->right;
			}
			if (w != NULL && w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w != NULL)
				{
					if (w->right->color == BLACK)
					{
						w->left->color = BLACK;
						w->color = RED;
						right_rotate(T, w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					left_rotate(T, x->parent);
					x = T->root;
				}
			}
		}
		else
		{
			Node* w = x->parent->left;
			if (w != NULL && w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				right_rotate(T, x->parent);
				w = x->parent->left;
			}
			if (w != NULL && w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w != NULL)
				{
					if (w->left->color == BLACK)
					{
						w->right->color = BLACK;
						w->color = RED;
						left_rotate(T, w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					right_rotate(T, x->parent);
					x = T->root;
				}
			}
		}
	}
	if(x != NULL)
		x->color = BLACK;

}

void del(Tree* T, Node* z)
{
	Node* x = NULL;
	Node* y = z;
	bool y_orig_color = y->color;

	if (z->left == NULL) {
		x = z->right;
		transplant(T, z, z->right);
	}
	else if (z->right == NULL)
	{
		x = z->left;
		transplant(T, z, z->left);
	}
	else
	{
		y = min(z->right);
		y_orig_color = y->color;
		x = y->right;
		if (y->parent != NULL && y->parent != z)
		{
			transplant(T, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		else
		{
			x->parent = y;
		}
		transplant(T, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_orig_color == BLACK)
		rb_del_fixup(T, x);

	delete z;
}

int main()
{
	int choice = 0, value;
	Tree* tree = new Tree();

	do {
		cout << "\n\n";
		cout << "\n====== RB-Tree ======";
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