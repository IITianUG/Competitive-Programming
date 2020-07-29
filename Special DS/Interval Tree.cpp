#include <bits/stdc++.h>
using namespace std;

struct Interval
{
    int low;
    int high;
};

struct ITreeNode
{
    Interval *i;
    int max_right;
    ITreeNode *left, *right;
};

ITreeNode *NewNode(Interval i)
{
    ITreeNode *temp = new ITreeNode;
    temp->i = new Interval(i);
    temp->max_right = i.high;
    temp->left = temp->right = NULL;
    return temp;
}

ITreeNode *Insert(ITreeNode *root, Interval i)
{
    //insert based on left endpoint
    if (root == NULL)
    {
        return NewNode(i);
    }

    int l = root->i->low;

    if (i.low < l)
    {
        root->left = Insert(root->left, i);
    }
    else
    {
        root->right = Insert(root->right, i);
    }

    if (i.high > root->max_right)
    {
        root->max_right = i.high;
    }

    return root;
}

bool AreOverlapping(Interval i1, Interval i2)
{
    if (i1.low <= i2.high && i2.low <= i1.high)
    {
        return true;
    }
    return false;
}

Interval *OverlapSearch(ITreeNode *root, Interval i)
{

    if (root == NULL)
    {
        return NULL;
    }

    if (AreOverlapping(*(root->i), i))
    {
        return root->i;
    }

    if (root->left != NULL && root->left->max_right >= i.low)
    {
        return OverlapSearch(root->left, i);
    }

    return OverlapSearch(root->right, i);
}

void Inorder(ITreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    Inorder(root->left);

    cout << "[" << root->i->low << ", " << root->i->high << "]"
         << " max = " << root->max_right << endl;

    Inorder(root->right);
}

int main()
{
    ITreeNode *root = NULL;
    int choice;
    int l, r;

    while (true)
    {
        cin >> choice;

        //Insert
        if (choice == 1)
        {
            cin >> l >> r;
            Interval x = {l, r};
            root = Insert(root, x);
        }
        //Overlap search
        else if (choice == 2)
        {
            cin >> l >> r;

            Interval x = {l, r};
            Interval *res = OverlapSearch(root, x);

            if (res == NULL)
            {
                cout << "No Overlapping Interval\n";
            }
            else
            {
                cout << "Overlaps with [" << res->low << ", " << res->high << "]\n";
            }
        }
        //Inorder traversal
        else
        {
            Inorder(root);
        }
    }
}
