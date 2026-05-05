#include <iostream>
#include <vector>

using namespace std;

class Heap {
private:
    vector<int> heap;

public:
    void swap(int& a, int&b){
        int temp = a;
        a = b;
        b = temp;
    }
    bool hasParent(int k) {
        return k > 0;
    }

    bool hasLeftChild(int k) {
        return (2*k + 1) < heap.size();
    }

    bool hasRightChild(int k) {
        return (2*k + 2) < heap.size();
    }

    int getLeftChild(int k) {
        if (!hasLeftChild(k)) throw runtime_error("Sem filho esquerdo");
        return 2*k + 1;
    }

    int getRightChild(int k) {
        if (!hasRightChild(k)) throw runtime_error("Sem filho direito");
        return 2*k + 2;
    }

    int getParent(int k) {
        if (!hasParent(k)) throw runtime_error("Sem pai");
        return heap[(k - 1) / 2];
    }
    void heapifyDown(int k) {
        while (hasLeftChild(k)) {
            int left = 2*k + 1;
            int right = 2*k + 2;

            int menor = left;

            if (hasRightChild(k) && heap[right] < heap[left]) {
                menor = right;
            }

            if (heap[k] <= heap[menor]) break;

            swap(heap[k], heap[menor]);
            k = menor;
        }
    }
};