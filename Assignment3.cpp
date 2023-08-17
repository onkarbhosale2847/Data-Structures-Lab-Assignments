#include <iostream>
using namespace std;

class Node
{
	int data;
	Node *lchild;
	Node *rchild;
	bool rtbit;
	bool ltbit;

public:
	bool find = false;
	friend class TBT;
	Node()
	{
		data = 0;
		lchild = NULL;
		rchild = NULL;
		rtbit = 0;
		ltbit = 0;
	}
	Node(int a)
	{
		data = a;
		lchild = NULL;
		rchild = NULL;
		rtbit = 0;
		ltbit = 0;
	}
};

class TBT
{
	Node *root;
	Node *header;

public:
	TBT()
	{
		root = NULL;
	}
	void insertTBT(int key)
	{
		if (root == NULL)
		{
			header = new Node(-1);
			header->rchild = header;
			root = new Node(key);
			root->lchild = header;
			root->rchild = header;
			header->lchild = root;
			header->ltbit = 1;
			header->rtbit = 1;
		}
		else
		{
			Node *ptr = root;
			Node *temp = new Node(key);
			while (1)
			{
				if (ptr->data > key)
				{
					if (ptr->ltbit != 0)
					{
						ptr = ptr->lchild;
					}
					else
					{
						temp->lchild = ptr->lchild;
						temp->rchild = ptr;
						ptr->ltbit = 1;
						ptr->lchild = temp;
						return;
					}
				}
				else
				{
					if (ptr->rtbit != 0)
					{
						ptr = ptr->rchild;
					}
					else
					{
						temp->lchild = ptr;
						temp->rchild = ptr->rchild;
						ptr->rtbit = 1;
						ptr->rchild = temp;
						return;
					}
				}
			}
		}
	}
	void inorder()
	{
		Node *t = root;
		cout << "In-order :";
		while (t->ltbit != 0)
		{
			t = t->lchild;
		}
		while (t != header)
		{
			cout << t->data << " ";
			if (t->rtbit != 0)
			{
				t = t->rchild;
				while (t->ltbit != 0)
				{
					t = t->lchild;
				} // Going down the tree via links
			}
			else
			{
				t = t->rchild;
			} // Going up the tree via threads
		}
	}
	void preorder()
	{
		int flag = 0;
		cout << "Pre-order :";
		Node *t = root;
		while (t != header)
		{
			if (flag == 0)
			{
				cout << t->data << " ";
			}
			if (flag == 0 && t->ltbit == 1)
			{
				t = t->lchild;
			}
			else
			{
				if (t->rtbit == 1)
				{
					flag = 0;
				}
				else
				{
					flag = 1;
				}
				t = t->rchild;
			}
		}
	}

	void searchTBT(int key, Node *&loc, Node *&par, int flag)
	{
		int counter = 0;
		if (root == NULL)
		{
			if (flag == 1)
			{
				cout << "Empty BST" << endl;
			}
			loc = NULL;
			par = NULL;
			return;
		}
		Node *ptr = root;

		while (ptr != header)
		{
			if (key == ptr->data)
			{
				ptr->find = true;
				counter++;
				loc = ptr;
				if (flag == 1)
				{
					cout << "Parent:" << par->data << endl;
					cout << "Location:" << loc->data << endl;
					cout << "Comparisons:" << counter << endl;
				}
				loc->find = true;
				return;
			}
			else if (key < ptr->data)
			{
				if (ptr->ltbit == 1)
				{
					par = ptr;
					ptr = ptr->lchild;
				}
				else
				{
					break;
				}
			}
			else if (key > ptr->data)
			{
				if (ptr->rtbit == 1)
				{
					par = ptr;
					ptr = ptr->rchild;
				}
				else
				{
					break;
				}
			}
			counter++;
		}
		if (!ptr->find)
		{
			cout << "Element Not Found" << endl;
			loc = par = NULL;
		}
	}

	void delTBT(Node *&p, Node *&t)
	{
		if (t->rtbit == 1 && t->ltbit == 1)
		{
			Node *succ = t->rchild;
			while (succ->ltbit != 0)
			{
				p = succ;
				succ = succ->lchild;
			}
			t->data = succ->data;
			t = succ;
		}
		else if (t->rtbit == 0 && t->ltbit == 0)
		{
			if (p->lchild == t)
			{
				p->lchild = t->lchild;
				p->ltbit = 0;
			}
			else
			{
				p->rchild = t->rchild;
				p->rtbit = 0;
			}
		}
		else
		{
			if (t->ltbit == 1 && t->rtbit == 0)
			{
				Node *temp = t->lchild;
				if (p->lchild == t)
				{
					p->lchild = temp;
				}
				else
				{
					p->rchild = temp;
				}
				while (temp->rtbit == 1)
				{
					temp = temp->rchild;
				}
				temp->rchild = t->rchild;
				delete (t);
			}
			else if (t->ltbit == 0 && t->rtbit == 1)
			{
				Node *temp = t->rchild;
				if (p->lchild == t)
				{
					p->lchild = temp;
				}
				else
				{
					p->rchild = temp;
				}
				while (temp->ltbit == 1)
				{
					temp = temp->lchild;
				}
				temp->lchild = t->lchild;
				delete (t);
			}
		}
	}
};

int main()
{

	TBT t1;
	/*-------INSERTION-------*/
	char ch;
	cout << "INSERTION" << endl;
	do
	{
		int input;
		cout << "Enter Data" << endl;
		cin >> input;
		t1.insertTBT(input);
		cout << "Continue Inserting? (y/n)" << endl;
		cin >> ch;
	} while (ch == 'y');

	t1.inorder();
	cout << endl;

	t1.preorder();
	cout << endl;

	/*-------SEARCHING-------*/
	cout << "SEARCHING" << endl;
	char c;
	do
	{
		Node *par, *loc;
		cout << "Enter Number to be Searched :" << endl;
		int k;
		cin >> k;
		t1.searchTBT(k, loc, par, 1);
		cout << "Continue? (y/n)" << endl;
		cin >> c;
	} while (c == 'y');

	/*-------DELETION-------*/
	cout << "DELETION" << endl;
	char l;
	do
	{
		cout << "Enter key to be deleted" << endl;
		int key;
		cin >> key;
		Node *p1, *tp;
		t1.searchTBT(key, tp, p1, 0);
		if (tp != NULL)
		{
			t1.delTBT(p1, tp);
			t1.inorder();
			cout << endl;
		}

		cout << "Continue? (y/n)" << endl;
		cin >> l;
	} while (l == 'y');

	return 0;
}
