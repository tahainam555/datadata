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


#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        data = value;
        left = right = nullptr;
        height = 1; // Height of a new node is initially 1
    }
};

class AVLTree {
private:
    Node* root;

    // Get the height of a node
    int height(Node* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    // Get the balance factor of a node
    int getBalanceFactor(Node* node) {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }

    // Right rotation
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x; // New root
    }

    // Left rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y; // New root
    }

    // Insert a node into the AVL tree
    Node* insertNode(Node* node, int data) {
        if (node == nullptr)
            return new Node(data);

        if (data < node->data)
            node->left = insertNode(node->left, data);
        else if (data > node->data)
            node->right = insertNode(node->right, data);
        else
            return node; // Duplicate keys are not allowed

        // Update height of the current node
        node->height = max(height(node->left), height(node->right)) + 1;

        // Get the balance factor
        int balance = getBalanceFactor(node);

        // Balance the tree
        // Left Left Case
        if (balance > 1 && data < node->left->data)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && data > node->right->data)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // Return the unchanged node
    }

    // Inorder traversal
    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

public:
    // Constructor
    AVLTree() {
        root = nullptr;
    }

    // Public insert function
    void insert(int data) {
        root = insertNode(root, data);
    }

    // Public inorder traversal
    void inorder() {
        inorderTraversal(root);
        cout << endl;
    }
};








#include <iostream>
using namespace std;

class Node {
public:
    int height;
    string id;
    Node* left;
    Node* right;

    Node(string id) {
        this->id = id;
        height = 0;
        left = NULL;
        right = NULL;
    }
};

class AVL {
public:
    Node* root;

    AVL() {
        root = NULL;
    }

    int Height(Node* node) {
        if (node == NULL) {
            return -1;  
        }
        return node->height;
    }

    int balance(Node* node) {
        if (node == NULL) {
            return 0;  
        }
        return Height(node->left) - Height(node->right);
    }

    Node* insert(Node* node, string id) {
        if (node == NULL) {
            return new Node(id);
        }

        if (id > node->id) {
            node->right = insert(node->right, id);
        }
        else if (id < node->id) {
            node->left = insert(node->left, id);
        }
        else {
            return node; 
        }

        node->height = max(Height(node->left), Height(node->right)) + 1;
        return checker(node);
    }

    Node* RotateRight(Node* k1) {
        Node* k2 = k1->left;
        k1->left = k2->right;
        k2->right = k1;
        k1->height = max(Height(k1->left), Height(k1->right)) + 1;
        k2->height = max(Height(k2->left), Height(k2->right)) + 1;
        return k2;
    }

    Node* RotateLeft(Node* k1) {
        Node* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(Height(k1->left), Height(k1->right)) + 1;
        k2->height = max(Height(k2->left), Height(k2->right)) + 1;
        return k2;
    }

    Node* rightLeft(Node* k1) {
        k1->right = RotateRight(k1->right);
        return RotateLeft(k1);
    }

    Node* leftRight(Node* k1) {
        k1->left = RotateLeft(k1->left);
        return RotateRight(k1);
    }

    Node* checker(Node* node) {
        int bal = balance(node);
        if (bal == 2) {
            if (balance(node->left) >= 0) {
                return RotateRight(node);
            }
            else {
                return leftRight(node);
            }
        }
        else if (bal == -2) {
            if (balance(node->right) <= 0) {
                return RotateLeft(node);
            }
            else {
                return rightLeft(node);
            }
        }
        return node;  
    }

    void preOrder(Node* node) {
        if (node != nullptr) {
            cout << node->id << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    Node* Min1(Node* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    Node* deleter2(Node* root, string id) {
        if (root==NULL) {
            return root;
        }
        if (id < root->id) {
            root->left = deleter2(root->left, id);
        }
        else if (id > root->id) {
            root->right = deleter2(root->right, id);
        }
        else {
            if (root->left == NULL && root->right == NULL) {
                delete root;
                return NULL;
            }
            else if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = Min1(root->right);
            root->id = temp->id;
            root->right = deleter2(root->right, temp->id);
        }
        root->height = max(Height(root->left), Height(root->right)) + 1;
        return checker(root);
    }

    void insert(string id) {
        root = insert(root, id);
    }

    void deleter(string id) {
        root = deleter2(root, id);
    }
};





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


#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// BST class
class BST {
private:
    Node* root;

    // Helper function for insertion
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    // Helper function for preorder traversal
    void preorder(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // Helper function for inorder traversal
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Helper function for postorder traversal
    void postorder(Node* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    // Custom BFS using a simple array as a queue
    void bfs(Node* root) {
        if (root == nullptr) return;

        Node* queue[100];  // Static array to simulate a queue
        int front = 0, rear = 0;

        // Enqueue root
        queue[rear++] = root;

        while (front < rear) {
            // Dequeue a node
            Node* current = queue[front++];

            // Process the node
            cout << current->data << " ";

            // Enqueue left child
            if (current->left != nullptr) {
                queue[rear++] = current->left;
            }

            // Enqueue right child
            if (current->right != nullptr) {
                queue[rear++] = current->right;
            }
        }
    }

public:
    // Constructor
    BST() {
        root = nullptr;
    }

    // Insert value into BST
    void insert(int value) {
        root = insert(root, value);
    }

    // BFS (Level Order Traversal)
    void bfs() {
        bfs(root);
        cout << endl;
    }

    // DFS Traversals
    void preorder() {
        preorder(root);
        cout << endl;
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    void postorder() {
        postorder(root);
        cout << endl;
    }
};

// Main function
int main() {
    BST tree;

    // Insert values
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);

    // Perform traversals
    cout << "BFS (Level Order): ";
    tree.bfs();

    cout << "DFS Preorder: ";
    tree.preorder();

    cout << "DFS Inorder: ";
    tree.inorder();

    cout << "DFS Postorder: ";
    tree.postorder();

    return 0;
}











struct priorityQNode 
{
    int time;         
    char intersection; 
};

class priorityQ 
{
    private:
        priorityQNode *data;
        int size;
        int capacity;
    public:
        priorityQ(int num) 
        {
            data = new priorityQNode[num+1];
            size = 1;
            capacity = num;
        }

        int getSize() 
        {
            return size;
        }

        void enqueue(int time, char intersection) 
        {
            if (size == capacity) 
            {
                cout<<"Queue is full"<<endl;
                return;
            }
            data[size].time = time;
            data[size].intersection = intersection;
            int i = size;
            size++;
            while (i > 1) 
            {
                int parent = i / 2;
                if (data[parent].time > data[i].time) 
                {
                    priorityQNode temp = data[parent];
                    data[parent] = data[i];
                    data[i] = temp;
                    i = parent;
                }
                else {
                    break;
                }
            }
        }

        void dequeue() 
        {
            if (size == 1) 
            {
                cout<<"Queue is empty"<<endl;
                return;
            }
            data[1] = data[size-1];
            size--;
            int i = 1;
            while (i < size) 
            {
                int left = 2 * i;
                int right = 2 * i + 1;
                int minIndex = i;
                if (left < size && data[left].time < data[minIndex].time) 
                {
                    minIndex = left;
                }
                if (right < size && data[right].time < data[minIndex].time) 
                {
                    minIndex = right;
                }
                if (minIndex == i) 
                {
                    break;
                }
                priorityQNode temp = data[i];
                data[i] = data[minIndex];
                data[minIndex] = temp;
                i = minIndex;
            }
        }

        bool isEmpty() 
        {
            return size == 1; 
        }

        void displayQueue() 
        {
            while (size > 1) 
            {
                cout<<data[1].intersection<<" Green Time "<<data[1].time<<"\n";
                dequeue();
            }
        }
        void print() 
        {
            for (int i = 1; i < size; i++) 
            {
                cout<<data[i].intersection<<" Green Time "<<data[i].time<<endl;
            }
        }

        char peekIntersection() 
        {
            if (size > 1) 
            {
                return data[1].intersection;
            }

            return ' ';
    }
};









        void ASearch(char start, char end) {
            cout << "Emergency vehicle is being routed..." << endl;

            int startVertex = vertexHash(start);
            int endVertex = vertexHash(end);

            for (int i = 0; i < graph->vertices; i++) {
                distance[i] = 99999;
                visited[i] = false;
                previous[i] = ' ';
            }
            distance[startVertex] = 0;
            P1->enqueue(0, start);

            bool pathFound = false;

            while (!P1->isEmpty()) {
                char current = P1->peekIntersection();
                P1->dequeue();

                int currVertex = vertexHash(current);
                if (visited[currVertex]) {
                    continue;
                }
                visited[currVertex] = true;

                if (current == end) {
                    pathFound = true;
                    break;
                }

                Node *neighbour = graph->list[currVertex].head;
                while (neighbour != NULL) {
                    int neighborVertex = vertexHash(neighbour->vertex);
                    if (visited[neighborVertex]) {
                        neighbour = neighbour->next;
                        continue;
                    }

                    float newCost = distance[currVertex] + neighbour->weight;
                    float heuristic = abs(neighborVertex - endVertex); // Heuristic (Manhattan distance)
                    float totalCost = newCost + heuristic;

                    if (newCost < distance[neighborVertex]) {
                        distance[neighborVertex] = newCost;
                        previous[neighborVertex] = current;
                        P1->enqueue(totalCost, neighbour->vertex);
                    }

                    neighbour = neighbour->next;
                }
            }

            if (!pathFound) {
                cout << "No path exists from " << start << " to " << end << "." << endl;
                return; 
            }

            // Construct the path
            char current = end;
            // for(int i=0; i<graph->vertices; i++)
            // {
            //     signals[i].isGreen = false;
            // }
            while (current != start) {
                overrideSignals(current);  
                S1.push(current);
                current = previous[vertexHash(current)];
            }
            overrideSignals(start);
            S1.push(start);

            printPath(start, end);

            restoreSignals(); 
        }
