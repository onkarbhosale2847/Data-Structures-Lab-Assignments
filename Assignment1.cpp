#include <iostream>
using namespace std;
class tree;

// class node for the creating nodes in for the tree
class node
{
    int data;
    node *left;
    node *right;

public:
    node(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
    }
    friend class tree;
};

// class stackNode for non-recursive post-order
class stackNode
{
public:
    node *address;
    int flag;
};

// class stack for stack usage
template <typename T> // stack using class template
class stack
{
    int top;
    T stk[100];

public:
    stack()
    {
        top = -1;
    }
    void push(T x)
    {
        top++;
        stk[top] = x;
    }
    int empty()
    {
        if (top == -1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    T pop()
    {
        T x;
        if (!empty())
        {

            x = stk[top];
            top--;
        }
        return x;
    }
    void print()
    {
        for (int i = top; i >= 0; i--)
        {
            cout << stk[i] << " ";
        }
    }
};

// class tree for creation of binary tree and its operation
class tree
{
    node *root;

public:
    tree()
    {
        root = NULL;
    }

    //<<-----------ADT OF THE TREE------------>>
    node *rec_create();
    void inorder(node *p);
    void preorder(node *p);
    void postorder(node *p);
    int rec_leaves_count(node *p);
    int rec_inter_count(node *p);
    void rec_deleteNode(node *p);
    node *copy(node *p);
    node *rec_reverse(node *p);
    int rec_height(node *p);
    void non_rec_preorder();
    void non_rec_inorder();
    void non_rec_postorder();
    //<<-----------ADT OF THE TREE------------>>

    // Exrta Functions..............
    void create()
    {
        root = rec_create();
    }

    void show()
    {
        cout << "\n<<---------------tree traversal by three methods by recursion :----------------------->>" << endl;

        if (root != NULL)
        {
            cout << "\nThe inorder traversal of the given tree is :";
            inorder(root);
            cout << endl;

            cout << "\nThe preorder traversal of the given tree is :";
            preorder(root);
            cout << endl;

            cout << "\nThe postorder traversal of the given tree is :";
            postorder(root);
            cout << endl;
        }
        else
        {
            cout << "\nYour tree empty....pls create a tree before show function ...!!" << endl;
        }
    }

    void count_leaves()
    {
        cout << "\n<<----------nodes attached to the tree are :------------------>>";
        int ans1;
        ans1 = rec_leaves_count(root);
        cout << "\nno of leaves nodes attached to the tree are :" << ans1 << endl;
        int ans2;
        ans2 = rec_inter_count(root);
        cout << "\nno of Internal  nodes attached to the tree are :" << (ans2 - ans1 - 1) << endl;
    }

    void operator=(tree &T) // operator ovrloading "="
    {
        root = copy(T.root);
        cout << "\n<-------- copy of the tree is produced by operator overloading successfully....!!!---------->" << endl;
        // return ;
    }

    void reverse()
    {
        cout << "\nReverse of left and right node at every node is done sucessfully ...!!!!: " << endl;
        root = rec_reverse(root);
    }

    void eraseAllNodes()
    {
        cout << "\nDeletion of all nodes is sucessfully done.......!!!!" << endl;
        // node *q=NULL;
        rec_deleteNode(root);
        root = NULL;
    }

    void height()
    {
        int ans;
        ans = rec_height(root);
        cout << "\nThe height of the tree is :" << ans << endl;
    }
};

// actual main functions of the tree
node *tree::rec_create()
{
    int x;
    cout << "Enter the no. or enter the -1 to stop... : ";
    cin >> x;
    if (x == -1)
    {
        return NULL;
    }
    else
    {
        node *p;
        p = new node(x);
        cout << "\nEnter the left of"
             << " " << x << " :" << endl;
        p->left = rec_create();
        cout << "\nEnter the right of"
             << " " << x << " :" << endl;
        p->right = rec_create();
        return p;
    }
}

void tree::inorder(node *p)
{
    if (p == NULL)
    {
        return;
    }
    else
    {
        inorder(p->left);
        cout << p->data << " ";
        inorder(p->right);
    }
}

void tree::preorder(node *p)
{
    if (p == NULL)
    {
        return;
    }
    else
    {
        cout << p->data << " ";
        preorder(p->left);
        preorder(p->right);
    }
}

void tree::postorder(node *p)
{
    if (p == NULL)
    {
        return;
    }
    else
    {
        postorder(p->left);
        postorder(p->right);
        cout << p->data << " ";
    }
}

int tree ::rec_leaves_count(node *p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        int a, b;
        a = rec_leaves_count(p->left);
        b = rec_leaves_count(p->right);
        if (a + b == 0)
        {
            return a + b + 1;
        }
        else
        {
            return a + b;
        }
    }
}

int tree::rec_inter_count(node *p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        int a, b;
        a = rec_inter_count(p->left);
        b = rec_inter_count(p->right);
        return a + b + 1;
    }
}
node *tree::copy(node *p)
{
    if (p == NULL)
    {
        return NULL;
    }
    else
    {
        node *q;
        q = new node(p->data);
        q->left = copy(p->left);
        q->right = copy(p->right);
        return q;
    }
}

node *tree::rec_reverse(node *p)
{
    if (p == NULL)
    {
        return NULL;
    }
    else
    {
        node *q;
        q = new node(p->data);
        q->right = rec_reverse(p->left);
        q->left = rec_reverse(p->right);
        return q;
    }
}

void tree::rec_deleteNode(node *p)
{
    if (p == NULL)
    {
        return;
    }
    else
    {
        rec_deleteNode(p->left);
        rec_deleteNode(p->right);
        delete p;
    }
}

// max function for the finding max of two no.s
int max(int a, int b)
{
    if (a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int tree::rec_height(node *p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        int a, b;
        a = rec_height(p->left);
        b = rec_height(p->right);
        return (max(a, b) + 1);
    }
}

void tree::non_rec_preorder()
{
    stack<node *> s;
    if (root == NULL)
    {
        cout << "\nYour tree is empty ....insert the elements in your tree....!";
    }
    else
    {
        node *p;
        p = root;
        while (p != NULL)
        {
            cout << p->data << " ";
            s.push(p);
            p = p->left;
        }

        while (!s.empty())
        {
            p = s.pop();
            p = p->right;
            while (p != NULL)
            {
                cout << p->data << " ";
                s.push(p);
                p = p->left;
            }
        }
    }
}

void tree::non_rec_inorder()
{
    stack<node *> s;
    if (root == NULL)
    {
        cout << "\nYour tree is empty ....insert the elements in your tree....!";
    }
    else
    {
        node *p;
        p = root;
        while (p != NULL)
        {
            // cout<<p->data<<" ";
            s.push(p);
            p = p->left;
        }

        while (!s.empty())
        {
            p = s.pop();
            cout << p->data << " ";
            p = p->right;
            // cout<<p->data<<" ";
            while (p != NULL)
            {
                s.push(p);
                p = p->left;
            }
        }
    }
}

void tree::non_rec_postorder()
{
    stack<stackNode> s;
    stackNode st;
    node *p;
    p = root;
    while (p != NULL)
    {
        st.address = p;
        st.flag = 0;
        s.push(st);
        p = p->left;
    }
    while (!s.empty())
    {
        st = s.pop();
        p = st.address;
        if (st.flag == 0)
        {
            st.flag = 1;
            s.push(st);
            p = p->right;
            while (p != NULL)
            {
                st.address = p;
                st.flag = 0;
                s.push(st);
                p = p->left;
            }
        }
        else if (st.flag == 1)
        {
            cout << p->data << " ";
        }
    }
}
//------------------------------------------------------------------------------------  done with class treee

// exicution of the main programe...........
int main()
{
    cout << "\n<--------------Welcome------------->" << endl;
    cout << "Enter the elements to the binary tree : " << endl;
    tree T1, T2;
    int choice;
    do
    {
        cout << "\nMenu" << endl;
        cout << "1.To create Binary Tree" << endl;
        cout << "2.To perform recursive inorder,preorder,postorder traversal " << endl;
        cout << "3.To perform non-recursive inorder traversal " << endl;
        cout << "4.To perform non-recursive preorder traversal " << endl;
        cout << "5.To perform non-recursive postorder traversal " << endl;
        cout << "6.The height the binary tree...." << endl;
        cout << "7.Copy tree to another tree " << endl;
        cout << "8.cout the no. of leaves nodes and no. of the internal nodes " << endl;
        cout << "9.To inter change the left and right of the tree " << endl;
        cout << "10.Erase all nodes in binary tree.." << endl;
        cout << "11.Exit" << endl;
        cout << "\nEnter the choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            T1.create();
            break;
        }
        case 2:
        {
            T1.show();
            break;
        }
        case 3:
        {
            cout << "Inorder traversal of the tree is :";
            T1.non_rec_inorder();
            cout << endl;
            break;
        }
        case 4:
        {
            cout << "Preorder traversal of the tree is :";
            T1.non_rec_preorder();
            cout << endl;
            break;
        }
        case 5:
        {
            cout << "Postorder traversal of the tree is :";
            T1.non_rec_postorder();
            cout << endl;
            break;
        }
        case 6:
        {
            T1.height();
            break;
        }
        case 7:
        {
            T2 = T1;
            cout << "Preorder traversal of the Copied tree is :";
            T2.non_rec_preorder();
            cout << endl;
            break;
        }
        case 8:
        {
            T1.count_leaves();
            break;
        }
        case 9:
        {
            T1.reverse();
            cout << "Preorder traversal of the REVERSE tree is :";
            T1.non_rec_preorder();
            cout << endl;
            break;
        }
        case 10:
        {
            T1.eraseAllNodes();
            break;
        }
        default:
        {
            cout << "\nThank you ....." << endl;
            cout << "End Of the Programe.....!!!!" << endl;
            cout << endl;
            break;
        }
        }

    } while (choice <= 10);
    return 0;
}
