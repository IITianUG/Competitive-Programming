#include <bits/stdc++.h>
using namespace std;
//Morris Traversal
//Space Complexity - O(1)

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

Node *insert(Node *root, int data)
{
    if (root == NULL)
    {
        return new Node(data);
    }
    else
    {
        Node *cur;
        if (data <= root->data)
        {
            cur = insert(root->left, data);
            root->left = cur;
        }
        else
        {
            cur = insert(root->right, data);
            root->right = cur;
        }
        return root;
    }
}

void inOrder(Node *root)
{

    struct Node *current, *pre;

    if (root == NULL)
        return;

    current = root;

    while (current != NULL)
    {
        if (current->left == NULL)
        {
            printf("%d ", current->data);
            current = current->right;
        }
        else
        {

            pre = current->left;
            while (pre->right != NULL && pre->right != current)
                pre = pre->right;

            if (pre->right == NULL)
            {
                pre->right = current;
                current = current->left;
            }
            else
            {
                pre->right = NULL;
                printf("%d ", current->data);
                current = current->right;
            }
        }
    }
}

int main()
{

    Node *root = NULL;

    int n;
    int data;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> data;
        root = insert(root, data);
    }

    inOrder(root);

    return 0;
}
