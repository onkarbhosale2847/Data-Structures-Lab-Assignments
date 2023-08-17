#include <iostream>
using namespace std;
class BST;
class node
{
	string keyword;
	string defination;
	node *right;
	node *left;

public:
	node()
	{
		keyword = "";
		defination = "";
		right = NULL;
		left = NULL;
	}
	node(string x, string y)
	{
		keyword = x;
		defination = y;
		right = NULL;
		left = NULL;
	}
	friend class BST;
};
class BST
{
	node *root;

public:
	BST()
	{
		root = NULL;
	}
	bool search(string key, node *&cur, node *&par)
	{
		par = NULL;
		cur = root;
		while (cur != NULL)
		{
			if (key == cur->keyword)
			{
				return true;
			}
			else if (key < cur->keyword)
			{
				par = cur;
				cur = cur->left;
			}
			else
			{
				par = cur;
				cur = cur->right;
			}
		}
		return false;
	}
	void insert(string key, string meaning)
	{
		if (root == NULL)
		{
			root = new node(key, meaning);
			cout << "Key inserted successfully." << endl;
			return;
		}
		node *loc = NULL;
		node *par = NULL;
		bool found = search(key, loc, par);
		if (found)
		{
			cout << "Word already in dictionary." << endl;
		}
		else
		{
			node *temp = new node(key, meaning);
			if (par->keyword < temp->keyword)
			{
				par->right = temp;
			}
			else
			{
				par->left = temp;
			}
			cout << "Key inserted successfully." << endl;
		}
	}
	void del1(node *par, node *loc)
	{
		if (loc->left == NULL && loc->right == NULL)
		{
			if (par->right == loc)
			{
				par->right = NULL;
				delete (loc);
				return;
			}
			else
			{
				par->left = NULL;
				delete (loc);
				return;
			}
		}
		node *child = NULL;
		if (loc->left == NULL)
		{
			child = loc->right;
		}
		else
		{
			child = loc->left;
		}
		if (par->left == loc)
		{
			par->left = child;
		}
		else
		{
			par->right = child;
		}
	}
	void deleteBST(string key, node *&loc)
	{
		node *par = NULL;
		search(key, loc, par);
		if (loc == NULL)
		{
			cout << "Key not found.\n";
			return;
		}
		if (loc->left != NULL && loc->right != NULL)
		{
			node *inordsuc = loc->right;
			node *temppar = loc;
			while (inordsuc->left != NULL)
			{
				temppar = inordsuc;
				inordsuc = inordsuc->left;
			}
			loc->keyword = inordsuc->keyword;
			del1(temppar, inordsuc);
		}
		else
		{
			del1(par, loc);
		}
	}
	void inorder(node *p)
	{
		if (p == NULL)
		{
			return;
		}
		else
		{
			inorder(p->left);
			cout << p->keyword << "      " << p->defination << "\n";
			inorder(p->right);
		}
	}
	void postorder(node *p)
	{
		if (p == NULL)
		{
			return;
		}
		else
		{
			postorder(p->right);
			cout << p->keyword << "      " << p->defination << "\n";
			postorder(p->left);
		}
	}
	void ascending()
	{
		inorder(root);
	}
	void descending()
	{
		postorder(root);
	}
};

int main()
{
	// BST t1;
	// t1.insert("Deval");
	// t1.insert("Avishkar");
	// t1.insert("Aa");
	// t1.insert("Zebra");
	// t1.ascending();
	// t1.deleteBST("Deval");
	// cout << endl;
	// t1.ascending();
	int c;
	BST t1;
	do
	{
		cout << "------------MENU------------\n";
		cout << "1. Insert new keyword.\n";
		cout << "2. Delete a keyword.\n";
		cout << "3. Update a keyword.\n";
		cout << "4. Display in ascending order.\n";
		cout << "5. Display in descending order.\n";
		cout << "6. Exit.\n";
		cout << "Enter the choice : ";
		cin >> c;
		if (c == 1)
		{
			string key, meaning;
			cout << "Enter the keyword to be inserted : ";
			cin >> key;
			cout << "Enter the meaning of given keyword : ";
			cin >> meaning;
			t1.insert(key, meaning);
		}
		else if (c == 2)
		{
			string key;
			cout << "Enter the keyword to be deleted : ";
			cin >> key;
			node *temp = NULL;
			t1.deleteBST(key, temp);
			if (temp == NULL)
			{
				cout << "Key not found.";
			}
			else
			{
				cout << "Key deleted successfully.\n";
			}
		}
		else if (c == 3)
		{
			string key, meaning;
			cout << "Enter the keyword to be updated : ";
			cin >> key;
			cout << "Enter the meaning of given keyword : ";
			cin >> meaning;
			node *temp = NULL;
			t1.deleteBST(key, temp);
			if (temp == NULL)
			{
				cout << "Key not found.";
			}
			else
			{
				cout << "Key updated successfully.\n";
			}
			t1.insert(key, meaning);
		}
		else if (c == 4)
		{
			cout << "Ascending order :\n";
			cout << "KEY   Meaning\n";
			t1.ascending();
		}
		else if (c == 5)
		{
			cout << "Descending order :\n";
			cout << "KEY   Meaning\n";
			t1.descending();
		}
	} while (c != 6);
	cout << "THANKYOU\n";
	return 0;
}
