#include <bits/stdc++.h>
using namespace std;

class TrieNode
{
public:
    static const int ALPHABET = 26;
    TrieNode *child[ALPHABET];
    bool isEndOfWord;

    TrieNode()
    {
        this->isEndOfWord = false;
        for (int i = 0; i < ALPHABET; i++)
        {
            this->child[i] = NULL;
        }
    }

    bool IsEmptyNode()
    {
        for (int i = 0; i < ALPHABET; i++)
        {
            if (this->child[i])
            {
                return false;
            }
        }
        return true;
    }
};

class Trie
{
private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }
    void InsertWord(const string &word);
    void RemoveWord(const string &word)
    {
        this->root = RemoveWordHelper(this->root, word, 0);
    }
    TrieNode *RemoveWordHelper(TrieNode *cur, const string &word, int depth);
    bool SearchWord(const string &word);
    bool StartsWith(const string &prefix);
};

void Trie::InsertWord(const string &word)
{
    TrieNode *curr = root;

    for (int i = 0; i < word.length(); i++)
    {
        int idx = word[i] - 'a';
        if (curr->child[idx] == NULL)
        {
            curr->child[idx] = new TrieNode();
        }
        curr = curr->child[idx];
    }

    curr->isEndOfWord = true;
}

bool Trie::SearchWord(const string &word)
{
    TrieNode *curr = root;

    for (int i = 0; i < word.length(); i++)
    {
        int idx = word[i] - 'a';
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

bool Trie::StartsWith(const string &prefix)
{
    TrieNode *curr = root;

    for (int i = 0; i < prefix.length(); i++)
    {
        int idx = prefix[i] - 'a';
        if (curr->child[idx] == NULL)
        {
            return false;
        }
        curr = curr->child[idx];
    }

    return true;
}

TrieNode *Trie::RemoveWordHelper(TrieNode *cur, const string &word, int depth)
{

    if (cur == NULL)
    {
        return NULL;
    }

    if (depth == word.length())
    {

        if (cur->isEndOfWord)
        {
            cur->isEndOfWord = false;
        }

        //if given word is not prefix of any other word
        if (cur->IsEmptyNode())
        {
            delete cur;
            cur = NULL;
        }
        return cur;
    }

    int index = word[depth] - 'a';
    cur->child[index] = RemoveWordHelper(cur->child[index], word, depth + 1);

    if (cur->IsEmptyNode() && cur->isEndOfWord == false)
    {
        delete cur;
        cur = NULL;
    }
    return cur;
}

int main()
{
    string s;
    Trie *trie = new Trie();

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

            if (trie->SearchWord(s))
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
            trie->InsertWord(s);
        }
        //delete key
        else if (choice == 3)
        {
            cin >> s;
            trie->RemoveWord(s);
        }
    }
}
