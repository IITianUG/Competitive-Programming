#include <bits/stdc++.h>
using namespace std;

class KDTreeNode
{
public:
    static const int k = 2;
    vector<int> point;
    KDTreeNode *left;
    KDTreeNode *right;

    KDTreeNode(const vector<int> &p) : point(p), left(NULL), right(NULL) {}
};

class KDTree
{
private:
    KDTreeNode *root;

public:
    KDTree() : root(NULL) {}
    void InsertPoint(const vector<int> &p)
    {
        this->root = InsertPointHelper(this->root, p, 0);
    }
    KDTreeNode *InsertPointHelper(KDTreeNode *node, const vector<int> &p, int depth);

    void DeletePoint(const vector<int> &p)
    {
        this->root = DeletePointHelper(this->root, p, 0);
    }
    KDTreeNode *DeletePointHelper(KDTreeNode *node, const vector<int> &p, int depth);

    bool SearchPoint(const vector<int> &p)
    {
        return SearchPointHelper(this->root, p, 0);
    }
    bool SearchPointHelper(KDTreeNode *node, const vector<int> &p, int depth);

    KDTreeNode *FindMinInDimensionD(int D)
    {
        return FindMinInDimensionDHelper(this->root, D, 0);
    }
    KDTreeNode *FindMinInDimensionDHelper(KDTreeNode *node, int D, int depth);

    KDTreeNode *MinNode(KDTreeNode *node1, KDTreeNode *node2, int D);
};

KDTreeNode *KDTree::InsertPointHelper(KDTreeNode *node, const vector<int> &p, int depth)
{
    if (node == NULL)
    {
        return new KDTreeNode(p);
    }
    int cur_dimension = depth % (KDTreeNode::k);

    if (p[cur_dimension] < (node->point[cur_dimension]))
    {
        node->left = InsertPointHelper(node->left, p, depth + 1);
    }
    else
    {
        node->right = InsertPointHelper(node->right, p, depth + 1);
    }
    return node;
}

KDTreeNode *KDTree::DeletePointHelper(KDTreeNode *node, const vector<int> &p, int depth)
{
    if (node == NULL)
    {
        return NULL;
    }
    int cur_dimension = depth % (KDTreeNode::k);

    if (node->point == p)
    {
        if (node->right != NULL)
        {
            KDTreeNode *min_node = FindMinInDimensionDHelper(node->right, cur_dimension, 0);
            node->point = min_node->point;

            // Recursively delete the minimum
            node->right = DeletePointHelper(node->right, min_node->point, depth + 1);
        }
        else if (node->left != NULL)
        {
            KDTreeNode *min_node = FindMinInDimensionDHelper(node->left, cur_dimension, 0);
            node->point = min_node->point;

            node->right = DeletePointHelper(node->left, min_node->point, depth + 1);
        }
        else
        {
            delete node;
            return NULL;
        }
        return node;
    }

    //If current node does not contain point, search downward
    if (p[cur_dimension] < node->point[cur_dimension])
        node->left = DeletePointHelper(node->left, p, depth + 1);
    else
        node->right = DeletePointHelper(node->right, p, depth + 1);
    return node;
}

bool KDTree::SearchPointHelper(KDTreeNode *node, const vector<int> &p, int depth)
{
    if (node == NULL)
    {
        return false;
    }
    if ((node->point) == p)
    {
        return true;
    }

    int cur_dimension = depth % (KDTreeNode::k);

    if (p[cur_dimension] < node->point[cur_dimension])
    {
        return SearchPointHelper(node->left, p, depth + 1);
    }
    return SearchPointHelper(node->right, p, depth + 1);
}

KDTreeNode *KDTree::MinNode(KDTreeNode *node1, KDTreeNode *node2, int D)
{
    KDTreeNode *res = node1;

    if (node2 != NULL && node2->point[D] < res->point[D])
    {
        res = node2;
    }
    return res;
}

KDTreeNode *KDTree::FindMinInDimensionDHelper(KDTreeNode *node, int D, int depth)
{

    if (node == NULL)
    {
        return NULL;
    }
    int cur_dimension = depth % (KDTreeNode::k);

    if (cur_dimension == D)
    {
        if (node->left == NULL)
        {
            return node;
        }
        return FindMinInDimensionDHelper(node->left, D, depth + 1);
    }

    return MinNode(node,
                   MinNode(FindMinInDimensionDHelper(node->left, D, depth + 1), FindMinInDimensionDHelper(node->right, D, depth + 1), D), D);
}

int main()
{
    KDTree *kd_tree = new KDTree();
    int q;
    cin >> q;

    int choice;
    vector<int> p(KDTreeNode::k);
    int D;

    while (q--)
    {
        cin >> choice;

        //search
        if (choice == 1)
        {
            for (int i = 0; i < (KDTreeNode::k); i++)
            {
                cin >> p[i];
            }
            if (kd_tree->SearchPoint(p))
            {
                cout << "Found" << endl;
            }
            else
            {
                cout << "Not found" << endl;
            }
        }
        //insert
        else if (choice == 2)
        {
            for (int i = 0; i < (KDTreeNode::k); i++)
            {
                cin >> p[i];
            }
            kd_tree->InsertPoint(p);
        }
        //find min
        else if (choice == 3)
        {
            cin >> D;
            cout << kd_tree->FindMinInDimensionD(D)->point[D] << endl;
        }
        //delete
        else if (choice == 4)
        {
            for (int i = 0; i < (KDTreeNode::k); i++)
            {
                cin >> p[i];
            }
            kd_tree->DeletePoint(p);
        }
    }
}
