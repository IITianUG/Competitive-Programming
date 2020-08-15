#include<bits/stdc++.h>
using namespace std;

class Node {
protected:
    string name;
public:
    map<string, Node*> next;

    Node(const string &name) {
        this->name=name;
    }
    string getName() {
        return name;
    }

    virtual bool isDirectory()=0;
    virtual vector<string> ls()=0;
};

class File : public Node {
private:
    string data;
public:
    File(const string &name) : Node(name) {};

    bool isDirectory() override {
        return false;
    }

    vector<string> ls() override {
        return { name };
    }

    void append(const string &str) {
        data+=str;
    }

    string read() {
        return data;
    }
};

class Directory : public Node {
public:
    Directory(const string &name) : Node(name) {}

    bool isDirectory() override {
        return true;
    }

    vector<string> ls() override {
        vector<string> ret;

        for (auto entry: next) {
            ret.push_back(entry.first);
        }
        return ret;
    }
};

class FileSystem {
private:
    Node* root;

    vector<string> tokenize(const string &path) {
        vector<string> ret;
        //first character is always /
        int pos=1;
        string token;

        while (pos<path.length()) {
            if (path[pos]=='/') {
                ret.push_back(token);
                token="";
            }
            else {
                token+=path[pos];
            }
            ++pos;
        }

        if (token.length()>0) {
            ret.push_back(token);
        }
        return ret;
    }

public:
    FileSystem() {
        root=new Directory("");
    }

    vector<string> ls(string path) {
        vector<string> tokens = tokenize(path);
        Node* cur = root;

        for (auto token: tokens) {
            cur = cur->next[token];
        }

        vector<string> ans = cur->ls();
        sort(ans.begin(), ans.end());
        return ans;
    }

    void mkdir(string path) {
        vector<string> tokens = tokenize(path);
        Node* cur = root;

        for (auto token: tokens) {

            if (cur->next.count(token)==0) {
                cur->next[token] = new Directory(token);
            }
            cur = cur->next[token];
        }
    }

    void addContentToFile(string filePath, string content) {
        vector<string> tokens = tokenize(filePath);
        Node* cur = root;

        for (auto token: tokens) {

            if (cur->next.count(token)==0) {
                cur->next[token] = new File(token);
            }
            cur = cur->next[token];
        }

        ((File*)cur)->append(content);
    }

    string readContentFromFile(string filePath) {
        vector<string> tokens = tokenize(filePath);

        Node* cur = root;

        for (auto token: tokens) {
            cur = cur->next[token];
        }

        return ((File*)cur)->read();
    }
};

int main() {
    FileSystem* fs = new FileSystem();
    int q;
    cin>>q;

    int choice;
    string path;
    string content;

    while (q--) {
        cin>>choice;
        if (choice==1) {
            //ls
            cin>>path;
            vector<string> ans = fs->ls(path);

            for (auto entry: ans) {
                cout<<entry<<" ";
            }
            cout<<endl;
        }
        else if (choice==2) {
            //mkdir
            cin>>path;
            fs->mkdir(path);
        }
        else if (choice==3) {
            //add content to file
            cin>>path>>content;
            fs->addContentToFile(path, content);
        }
        else if (choice==4) {
            //read content from file
            cin>>path;
            cout<<fs->readContentFromFile(path)<<endl;
        }
    }
}
