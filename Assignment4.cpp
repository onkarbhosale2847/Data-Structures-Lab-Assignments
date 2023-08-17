#include <iostream>
using namespace std;
#define SIZE 13

class HashEntry
{
    friend class HT;
    string name;
    int tele;
    int chain;

public:
    HashEntry(string n = "", int t = 0)
    {
        name = n;
        tele = t;
        chain = -1;
    }
};

class HT
{
    friend class HashEntry;
    HashEntry arr[SIZE];

public:
    HT()
    {
        for (int i = 0; i < SIZE; i++)
        {
            arr[i].name = "";
            arr[i].tele = 0;
            arr[i].chain = -1;
        }
    }

    void print()
    {
        cout << "--------------------------------------------" << endl;
        cout << "INDEX\tKEY\t\tVALUE" << endl;
        cout << "--------------------------------------------" << endl;
        for (int i = 0; i < SIZE; i++)
        {
            cout << i << ":\t" << arr[i].name << "\t\t" << arr[i].tele << "\t" << endl;
        }
        cout << "--------------------------------------------" << endl;
    }

    int getsum(string key)
    {
        int sum = 0;
        for (int i = 0; i < key.length(); i++)
        {
            sum += key[i];
        }
        return sum;
    }

    int hash(string k)
    {
        int inp = getsum(k);
        return inp % SIZE;
    }

    void insert_wor(string k, int t)
    {
        HashEntry temp(k, t);
        int baseindex = hash(k);
        if (arr[baseindex].name == "")
        {
            arr[baseindex] = temp;
            return;
        }
        else
        {
            // probe w/o replacement
            int index = baseindex;
            int i = index;
            i = (i + 1) % SIZE;
            while (i != baseindex)
            {
                if (arr[i].name == "")
                {
                    arr[i] = temp;
                    arr[index].chain = i;
                    return;
                }
                else
                {
                    while (arr[index].chain != -1)
                    {
                        index = arr[index].chain;
                    }
                    i = (i + 1) % SIZE;
                }
            }
            cout << "TABLE FULL" << endl;
        }
    }
    void insert_wr(string k, int t)
    {
        HashEntry temp(k, t);
        int baseindex = hash(k);
        if (arr[baseindex].name == "")
        {
            arr[baseindex] = temp;
        }
        else
        {
            // probe with replacement
            int  tpp = hash(arr[baseindex].name);
            if (tpp!=baseindex)
            {
                // replace and probe linearly for the replaced entry
                HashEntry n = arr[baseindex];
                arr[baseindex]= temp;
                insert_wor(n.name,n.tele);
            }
            else{
                // probe linearly
                insert_wor(temp.name,temp.tele);
            }
        }
    }
    void del(string k)
	{
		int f = find(k, 1);
		if (f == -1)
		{
			cout << "Key Not Present" << endl;
			return;
		}
		else
		{
			arr[f].name = "";
			arr[f].tele = 0;
			arr[f].chain = -1;
		}
	}
	int find(string k, int flag)
	{
		int inp = hash(k);
		int tp = inp;
		if (arr[tp].name == k)
		{
			if (flag == 0)
			{
				cout << "Name: " << arr[inp].name << endl;
				cout << "Phone No.: " << arr[inp].tele << endl;
			}
			return tp;
		}
		else
		{
			// traverse chains and if still not found print "NOT FOUND"
			while (tp != -1)
			{
				tp = arr[tp].chain;
				if (arr[tp].name == k)
				{
					if (flag == 0)
					{
						cout << "Name: " << arr[tp].name << endl;
						cout << "Phone No.: " << arr[tp].tele << endl;
					}
					return tp;
				}
			}
			if (flag == 0)
			{
				cout << "NOT FOUND" << endl;
			}
			return -1;
		}
	}
    };

    int main()
    {
        HT t1;
        HT t2;
        t1.insert_wor("A", 5);
        t1.insert_wor("A", 10);
        t1.insert_wor("A", 15);
        t1.insert_wor("A", 50);
        t1.insert_wor("C", 100);
        t1.print();
        t2.insert_wr("A", 5);
		t2.insert_wr("A", 10);
		t2.insert_wr("A", 15);
		t2.insert_wr("A", 50);
		t2.insert_wr("C", 100);
		t2.print();
        return 0;
    }
