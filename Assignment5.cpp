#include <bits/stdc++.h>
using namespace std;
#define MAX 6
class node{
public:
	string key;
	string value;
	node* next;
	node()
	{
		key = "";
		value = "";
		next = NULL;
	}
	node(string key, string value)
	{
		this->key = key;
		this->value = value;
		this->next = NULL;
	}
};

class HashTable
{
private:
	node* arr[MAX];
public:
	HashTable()
	{
		for(int i = 0; i<MAX; i++)
		{
			arr[i] = NULL;
		}
	}
	int HashFunc(string key)
	{
		int ans = 0;
		for(int i = 0; i < key.length(); i++)
		{
			ans += (tolower(key[i]) - 'a');
		}
		return ans%MAX;
	}		int ch;
	void insert(string key, string value)
	{
		int code = HashFunc(key);
		node* temp = new node(key, value);
		if(arr[code] == NULL)
		{
			arr[code] = temp;
		}
		else
		{
			node* tp = arr[code];
			if(tp->key == key)
			{
				cout<<"Key already exists in dictionary."<<endl;
				delete(temp);
				return;
			}
			while(tp->next != NULL)
			{
				if(tp->key == key)
				{
					cout<<"Key already exists in dictionary."<<endl;
					delete(temp);
					return;
				}
				tp = tp->next;
			}
			tp->next = temp;
		}
	}
	void print(void)
	{
		for(int i = 0; i<MAX; i++)
		{
			cout<<i<<" ";
			if(arr[i] == NULL)
			{
				cout<<-1<<endl;
			}
			else
			{
				node* tp = arr[i];
				while(tp != NULL)
				{
					if(tp->next != NULL)
					{
						cout<<"("<<tp->key<<" : "<<tp->value<<") ----> ";
					}
					else
					{
						cout<<"("<<tp->key<<" : "<<tp->value<<")";
					}
					tp = tp->next;
				}
				cout<<endl;
			}
		}
	}
	void find(string key)
	{
		int code = HashFunc(key);
		node* tp = arr[code];
		if(tp==NULL)
		{
			cout<<"NOT FOUND"<<endl;
			return;
		}
		while(tp!=NULL)
		{
			if(tp->key == key)
			{
				cout<<"KEY FOUND"<<endl;
				cout<<tp->key<<" : "<<tp->value<<endl;
				return;
			}
			tp = tp->next;
		}
		cout<<"NOT FOUND"<<endl;
		return;
	}
	void deletekey(string key)
	{
		int code = HashFunc(key);
		node* tp = arr[code];
		if(tp==NULL)
		{
			cout<<"NOT FOUND"<<endl;
			return;
		}
		if(tp->key == key)
		{
			arr[code] = tp->next;
			tp->next = NULL;
			delete(tp);
			return;
		}
		node* prev = arr[code];
		while(tp != NULL)
		{
			if(tp->key == key)
			{
				prev->next = tp->next;
				tp->next = NULL;
				delete(tp);
				return;
			}
			prev = tp;
			tp = tp->next;
		}
		cout<<"NOT FOUND"<<endl;
		return;
	}
};


int main()
{
	HashTable HT;
	int ch;
	do{
		cout<<"-------MENU-------"<<endl;
		cout<<"1. Insert key and value."<<endl;
		cout<<"2. Find given key."<<endl;
		cout<<"3. Delete a key."<<endl;
		cout<<"4. Print all entries."<<endl;
		cout<<"5. EXIT."<<endl;
		cout<<"Enter the choice to be performed: ";
		cin>>ch;
		string key, value;
		if(ch==1)
		{
			cout<<"Enter the key: ";
			cin>>key;
			cout<<"Enter the meaning: ";
			cin.ignore();
			getline(cin, value);
			HT.insert(key, value);
		}
		else if(ch==2)
		{
			cout<<"Enter the key to find: ";
			cin>>key;
			HT.find(key);
		}
		else if(ch==3)
		{
			cout<<"Enter the key to delete: ";
			cin>>key;
			HT.deletekey(key);
		}
		else if(ch==4)
		{
			cout<<"The dictionary is : "<<endl;
			HT.print();
			cout<<endl;
		}
		else
		{
			return 0;
		}
	}while(ch!=5);
//	HT.insert("abc", "tp");
//	HT.insert("a", "tp2");
//	HT.insert("a", "tp3");
//	HT.insert("bs", "tp");
//	HT.insert("ec", "pt");
//	HT.insert("hh", "pt");
//	HT.print();
//	cout<<endl;
//	HT.find("b");
//	HT.deletekey("a");
//	HT.print();
	return 0;
}
