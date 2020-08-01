#include <bits/stdc++.h>
using namespace std;

class MinHeapNode
{
public:
    int data;
    MinHeapNode(int data) : data(data) {}
};

class MinHeap
{
private:
    vector<MinHeapNode *> heap_arr;
    int capacity;
    int heap_size;

public:
    MinHeap(int cap)
    {
        this->capacity = cap;
        this->heap_size = 0;
        heap_arr.resize(capacity);
    }

    int Parent(int v)
    {
        return (v - 1) / 2;
    }

    int LeftChild(int v)
    {
        return 2 * v + 1;
    }

    int RightChild(int v)
    {
        return 2 * v + 2;
    }

    MinHeapNode *GetMin()
    {
        return heap_arr[0];
    }

    void MinHeapify(int v);
    MinHeapNode *ExtractMin();
    void InsertKey(MinHeapNode *val);
    void DeleteKey(int v);

    void ModifyKey(int v, MinHeapNode *new_val);
    void DecreaseKey(int v, MinHeapNode *new_val);
    void IncreaseKey(int v, MinHeapNode *new_val);

    void PrintHeap()
    {
        for (int i = 0; i < heap_size; i++)
        {
            cout << heap_arr[i]->data << " ";
        }
        cout << endl;
    }
};

MinHeapNode *MinHeap::ExtractMin()
{

    if (heap_size == 0)
    {
        return new MinHeapNode(INT_MAX);
    }
    if (heap_size == 1)
    {
        heap_size--;
        return heap_arr[0];
    }

    MinHeapNode *root = heap_arr[0];
    heap_arr[0] = heap_arr[heap_size - 1];
    heap_size--;
    MinHeapify(0);

    return root;
}

void MinHeap::InsertKey(MinHeapNode *val)
{
    if (heap_size == capacity)
    {
        return;
    }
    heap_size++;
    int v = heap_size - 1;
    heap_arr[v] = val;

    //fix heap property - bottom up
    while (v != 0 && heap_arr[Parent(v)]->data > heap_arr[v]->data)
    {
        swap(heap_arr[v], heap_arr[Parent(v)]);
        v = Parent(v);
    }
}

void MinHeap::DeleteKey(int v)
{
    DecreaseKey(v, new MinHeapNode(INT_MIN));
    ExtractMin();
}

void MinHeap::ModifyKey(int v, MinHeapNode *new_val)
{
    int cur_data = heap_arr[v]->data;

    if (new_val->data > cur_data)
    {
        IncreaseKey(v, new_val);
    }
    else if (new_val->data < cur_data)
    {
        DecreaseKey(v, new_val);
    }
}

void MinHeap::IncreaseKey(int v, MinHeapNode *new_val)
{
    heap_arr[v] = new_val;
    MinHeapify(v);
}

void MinHeap::DecreaseKey(int v, MinHeapNode *new_val)
{
    heap_arr[v] = new_val;
    //fix heap property - bottom up
    while (v != 0 && heap_arr[Parent(v)]->data > heap_arr[v]->data)
    {
        swap(heap_arr[v], heap_arr[Parent(v)]);
        v = Parent(v);
    }
}

void MinHeap::MinHeapify(int v)
{
    //fix heap property - top down
    int l = LeftChild(v);
    int r = RightChild(v);
    int smallest = v;
    if (l < heap_size && heap_arr[l]->data < heap_arr[v]->data)
    {
        smallest = l;
    }
    if (r < heap_size && heap_arr[r]->data < heap_arr[smallest]->data)
    {
        smallest = r;
    }
    if (smallest != v)
    {
        swap(heap_arr[v], heap_arr[smallest]);
        MinHeapify(smallest);
    }
}

int main()
{
    MinHeap *min_heap = new MinHeap(100);
    int q;
    cin >> q;

    int choice;
    int index, data;

    while (q--)
    {
        cin >> choice;

        //insert new data
        if (choice == 1)
        {
            cin >> data;
            min_heap->InsertKey(new MinHeapNode(data));
        }
        //delete key at particular index
        else if (choice == 2)
        {
            cin >> index;
            min_heap->DeleteKey(index);
        }
        //extract min
        else if (choice == 3)
        {
            cout << min_heap->ExtractMin()->data << endl;
        }
        //modify data at a particular index
        else if (choice == 4)
        {
            cin >> index >> data;
            min_heap->ModifyKey(index, new MinHeapNode(data));
        }
        //print heap
        else if (choice == 5)
        {
            min_heap->PrintHeap();
        }
    }
}
