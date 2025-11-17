#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_SIZE 100

class MaxHeap {
private:
    int heap[MAX_SIZE];
    int size;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void MaxHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < size && heap[l] > heap[i]) {
            largest = l;
        }
        if (r < size && heap[r] > heap[largest]) {
            largest = r;
        }

        if (largest != i) {
            swap(heap[i], heap[largest]);
            MaxHeapify(largest);
        }
    }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    MaxHeap(int arr[], int initial_size) {
        if (initial_size > MAX_SIZE) {
            cout << "Error: Initial size exceeds MAX_SIZE." << endl;
            size = 0;
            return;
        }
        size = initial_size;
        for (int i = 0; i < size; ++i) {
            heap[i] = arr[i];
        }
    }
    
    void update_key(int i, int new_val) {
        if (i < 0 || i >= size) {
            cout << "Error: Invalid index." << endl;
            return;
        }

        int old_val = heap[i];
        heap[i] = new_val;

        if (new_val > old_val) {
            heapifyUp(i);
        } else if (new_val < old_val) {
            MaxHeapify(i);
        }
        cout << "Key at index " << i << " updated from " << old_val << " to " << new_val << endl;
    }

    void deleteMax() {
        if (size <= 0) {
            cout << "Error: Heap is empty." << endl;
            return;
        }

        int max_val = heap[0];
        heap[0] = heap[size - 1];
        size--;
        MaxHeapify(0);
        
        cout << "Deleted Max Element (Root): " << max_val << endl;
    }

    void display() const {
        cout << "Heap Array: [";
        for (int i = 0; i < size; ++i) {
            cout << heap[i] << (i == size - 1 ? "" : ", ");
        }
        cout << "]" << endl;
    }
};

int main() {
    int initial_arr[] = {8, 7, 6, 5, 4};
    int initial_size = 5;
    MaxHeap myHeap(initial_arr, initial_size);

    cout << "--- Initial State ---" << endl;
    myHeap.display();

    cout << "\n--- update_key Demo ---" << endl;
    myHeap.update_key(3, 10);
    cout << "After update (HeapifyUp):" << endl;
    myHeap.display();

    myHeap.update_key(0, 1);
    cout << "After update (MaxHeapify):" << endl;
    myHeap.display();

    cout << "\n--- deleteMax Demo ---" << endl;
    myHeap.deleteMax();
    cout << "After deleteMax:" << endl;
    myHeap.display();

    return 0;
}
