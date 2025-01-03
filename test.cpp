#include <iostream>
using namespace std;

const int MAX_SIZE = 100; // Maximum size of the heap

class MaxHeap {
    int heap[MAX_SIZE];
    int size;

    void heapifyUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
            // Swap parent and current node
            int temp = heap[(index - 1) / 2];
            heap[(index - 1) / 2] = heap[index];
            heap[index] = temp;

            index = (index - 1) / 2; // Move up to parent
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size && heap[left] > heap[largest])
                largest = left;
            if (right < size && heap[right] > heap[largest])
                largest = right;

            if (largest == index) break;

            // Swap current node with the largest
            int temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;

            index = largest; // Move down to the largest child
        }
    }

public:
    MaxHeap() : size(0) {}

    void insert(int value) {
        if (size == MAX_SIZE) {
            cout << "Heap overflow!" << endl;
            return;
        }
        heap[size] = value;
        heapifyUp(size);
        size++;
    }

    int extractMax() {
        if (size <= 0) {
            cout << "Heap underflow!" << endl;
            return -1;
        }

        int maxValue = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return maxValue;
    }

    void display() {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};











class MinHeap {
    int heap[MAX_SIZE];
    int size;

    void heapifyUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] > heap[index]) {
            // Swap parent and current node
            int temp = heap[(index - 1) / 2];
            heap[(index - 1) / 2] = heap[index];
            heap[index] = temp;

            index = (index - 1) / 2; // Move up to parent
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size && heap[left] < heap[smallest])
                smallest = left;
            if (right < size && heap[right] < heap[smallest])
                smallest = right;

            if (smallest == index) break;

            // Swap current node with the smallest
            int temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;

            index = smallest; // Move down to the smallest child
        }
    }

public:
    MinHeap() : size(0) {}

    void insert(int value) {
        if (size == MAX_SIZE) {
            cout << "Heap overflow!" << endl;
            return;
        }
        heap[size] = value;
        heapifyUp(size);
        size++;
    }

    int extractMin() {
        if (size <= 0) {
            cout << "Heap underflow!" << endl;
            return -1;
        }

        int minValue = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return minValue;
    }

    void display() {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};




const int maxx=100;



int graph[maxx][maxx]; // Adjacency matrix
int dist[maxx];            // Distance from the source
bool visited[maxx];        // Visited nodes
int n;                          // Number of nodes

int findMinDistanceNode() {
    int minDistance = 0, minIndex = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < minDistance) {
            minDistance = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int source) {
    // Initialize distances and visited array
    for (int i = 0; i < n; i++) {
        dist[i] = 999999;
        visited[i] = false;
    }
    dist[source] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = findMinDistanceNode(); // Find the unvisited node with the smallest distance
        if (u == -1) break; // All reachable nodes have been visited
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the shortest distances
    cout << "Node\tDistance from Source" << endl;
    for (int i = 0; i < n; i++) {
        cout << i << "\t" << dist[i] << endl;
    }
}




int main() {
    MaxHeap heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(30);

    cout << "Max Heap: ";
    heap.display();

    cout << "Extracted Max: " << heap.extractMax() << endl;

    cout << "Max Heap after extraction: ";
    heap.display();

    return 0;
}

