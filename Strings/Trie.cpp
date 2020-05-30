#include <bits/stdc++.h>
using namespace std;
const int ALPHABET = 26;

struct trieNode
{
    bool isEndOfWord;
    trieNode *child[ALPHABET];
};

trieNode *getNode()
{
    trieNode *node = new trieNode;
    node->isEndOfWord = false;

    for (int i = 0; i < ALPHABET; i++)
    {
        node->child[i] = NULL;
    }
    return node;
}

void insertKey(trieNode *root, string key)
{
    trieNode *curr = root;

    for (int i = 0; i < key.length(); i++)
    {
        int idx = key[i] - 'a';
        if (curr->child[idx] == NULL)
        {
            curr->child[idx] = getNode();
        }
        curr = curr->child[idx];
    }

    curr->isEndOfWord = true;
}

bool searchKey(trieNode *root, string key)
{
    trieNode *curr = root;

    for (int i = 0; i < key.length(); i++)
    {
        int idx = key[i] - 'a';
        if (curr->child[idx] == NULL)
        {
            return false;
        }
        curr = curr->child[idx];
    }

    if (curr != NULL && curr->isEndOfWord)
    {
        return true;
    }
    return false;
}

bool isEmpty(trieNode *root)
{
    for (int i = 0; i < ALPHABET; i++)
    {
        if (root->child[i])
        {
            return false;
        }
    }
    return true;
}

trieNode *removeKey(trieNode *root, string key, int depth = 0)
{
    if (!root)
    {
        return NULL;
    }

    if (depth == key.length())
    {
        if (root->isEndOfWord)
        {
            root->isEndOfWord = false;
        }

        //if given word is not prefix of any other word
        if (isEmpty(root))
        {
            delete root;
            root = NULL;
        }

        return root;
    }

    int idx = key[depth] - 'a';

    root->child[idx] = removeKey(root->child[idx], key, depth + 1);

    if (isEmpty(root) && root->isEndOfWord == false)
    {
        delete root;
        root = NULL;
    }
    return root;
}

int main()
{
    string s;
    trieNode *root = getNode();

    int q;
    cin >> q;

    int choice;

    while (q--)
    {
        cin >> choice;

        //search
        if (choice == 1)
        {
            cin >> s;

            if (searchKey(root, s))
            {
                cout << "Present" << endl;
            }
            else
            {
                cout << "Not present" << endl;
            }
        }
        //insert new key
        else if (choice == 2)
        {
            cin >> s;
            insertKey(root, s);
        }
        //delete key
        else if (choice == 3)
        {
            cin >> s;
            root = removeKey(root, s);
        }
    }
}
