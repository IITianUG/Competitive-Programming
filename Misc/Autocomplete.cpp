#include <bits/stdc++.h>
using namespace std;
//Assumption: only lower case alphabets

class TrieNode
{
public:
    static const int ALPHABET = 26;
    TrieNode *child[ALPHABET];
    bool isEndOfWord;
    vector<string> candidates;

    TrieNode() {
        this->isEndOfWord = false;
        for (int i = 0; i < ALPHABET; i++)
        {
            this->child[i] = NULL;
        }
        candidates.clear();
    }
};

class Trie
{
private:
    TrieNode *root;

public:
    Trie() {
        root = new TrieNode();
    }
    void InsertWord(const string &word);
    TrieNode* StartsWith(const string &prefix);
};

void Trie::InsertWord(const string &word) {
    TrieNode *curr = root;

    for (int i = 0; i < word.length(); i++) {
        int idx = word[i] - 'a';
        if (curr->child[idx] == NULL) {
            curr->child[idx] = new TrieNode();
        }
        curr->child[idx]->candidates.push_back(word);
        curr = curr->child[idx];
    }
    curr->isEndOfWord = true;
}

TrieNode* Trie::StartsWith(const string &prefix) {
    TrieNode *curr = root;

    for (int i = 0; i < prefix.length(); i++) {
        int idx = prefix[i] - 'a';
        if (curr->child[idx] == NULL) {
            return NULL;
        }
        curr = curr->child[idx];
    }
    return curr;
}

class AutocompleteSystem {
private:
    unordered_map<string, int> word_count;
    static const int MAX_RESULTS=3;
    Trie* trie;
    string curr_word;
public:
    AutocompleteSystem(const vector<string> &sentences, const vector<int> &times) {
        word_count.clear();
        trie= new Trie();
        curr_word="";

        for (int i=0;i<sentences.size();i++) {
            word_count[sentences[i]]=times[i];
            trie->InsertWord(sentences[i]);
        }
    }
    vector<string> InputChar(char c);
    vector<string> GetSuggestions();
};

vector<string> AutocompleteSystem::InputChar(char c) {
    vector<string> res;
    if (c=='#') {
        if (word_count.find(curr_word)==word_count.end()) {
            trie->InsertWord(curr_word);
            word_count[curr_word]++;
        }
        else {
            word_count[curr_word]++;
        }
        curr_word="";
    }
    else {
        curr_word+=c;
        res = GetSuggestions();
    }
    return GetSuggestions();
}

vector<string> AutocompleteSystem::GetSuggestions() {
    vector<string> res;
    TrieNode* node = trie->StartsWith(curr_word);
    if (node==NULL) {
        return res;
    }
    vector<string> cands = node->candidates;
    sort(cands.begin(), cands.end(), [&](const string &s1, const string &s2) {
        if (word_count[s1]!=word_count[s2]) {
            return word_count[s1]>word_count[s2];
        }
        return s1<s2;
        });

    int added=0;
    for (string s: cands) {
        res.push_back(s);
        added++;
        if (added==AutocompleteSystem::MAX_RESULTS) {
            break;
        }
    }
    return res;
}

int main() {
    vector<string> sentences{ "apple", "arnold", "are", "and" };
    vector<int> times{ 5, 3, 2, 2 };

    AutocompleteSystem* auto_complete = new AutocompleteSystem(sentences, times);
    int q;
    cin>>q;
    char ch;

    while (q--) {
        cin>>ch;
        vector<string> suggestions = auto_complete->InputChar(ch);

        if (suggestions.size()==0) {
            cout<<"No suggestions\n";
            continue;
        }

        for (string s: suggestions) {
            cout<<s<<" ";
        }
        cout<<endl;
    }

}
