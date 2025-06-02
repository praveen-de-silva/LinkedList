//
// Created by ASUS on 01/06/2025.
//

#include "UsefulCodes.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <list>

using namespace std;


// =================
//     Heap Sort
// =================

class Heap {
    int *hArr;
    int maxSize;
    int crntSize;


public :

    Heap(int aMaxSize) {
        maxSize = aMaxSize;
        crntSize = 0;
        hArr = new int[maxSize];
    }

    ~Heap() {
        delete[] hArr; // free alocated memory
    }

    // get heap node key (since it is private)
    int getKey(int i) {
        return hArr[i];
    }

    void insertKey(int key) {
        if (crntSize == maxSize) {
            cout << "Heap is full! cannot add " << key << endl;
            return;
        }

        hArr[crntSize] = key;
        crntSize++;
    }

    void removeKey(int key) {
        for (int i = 0; i < crntSize; i++) {
            if (hArr[i] == key) {
                swap(hArr[i], hArr[crntSize-1]);
                crntSize--;
                return;
            }
        }
        cout << "Remove fail!" << endl;
    }

    void printHeap() {
        for (int i=0; i < crntSize; i++) {
            cout << hArr[i] << " ";
        }
        cout << endl;
    }

    // heapify a node (for max-heap)
    void heapify(int k) {
        int l = 2 * k + 1;
        int r = 2 * k + 2;
        int largest = k;

        if (l < crntSize && hArr[l] > hArr[largest]) {
            largest = l;
        }

        if (r < crntSize && hArr[r] > hArr[largest]) {
            largest = r;
        }

        if (largest != k) {
            swap(hArr[largest], hArr[k]);
            heapify(largest);
        }
    }

    // build heap
    void buildHeapIter() {
        for (int i = crntSize / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    void heapSort() {
        buildHeapIter();
        int originalSize = crntSize;

        while (crntSize > 0) {
            swap(hArr[0], hArr[crntSize-1]);
            crntSize--; // to ignore the last node which is already sorted
            heapify(0);
        }

        crntSize = originalSize;
    }

};

void heapSort(int arr[], int n) {
    // creating a heap
    Heap heap(n);

    // add elements to the heap
    for (int i=0; i<n; i++) {
        heap.insertKey(arr[i]);
    }

    // sort the heap using heap sort
    heap.heapSort();

    // insert the sorted values to the array
    for (int i=0; i<n; i++) {
        arr[i] = heap.getKey(i);
    }

};

void printArr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// ===========
//     DFS
// ===========

enum Color {WHITE, GRAY, BLACK};

struct Vertex {
    int id;
    Color color;
    int timeDiscover;
    int timefinish;
    Vertex *parent;
    list<int> adj;
};

class Graph {
private:
    vector<Vertex> vertices;
    int time;

public:
    Graph(int n) : time(0) {
        vertices.resize(n);

        for (int i = 0; i < n; i++) {
            vertices[i].id = i;
            vertices[i].color = WHITE;
            vertices[i].parent = nullptr;
        }
    }

    void addEdge(int u, int v) {
        /**
         * add edge (Directed Graph)
         */
        vertices[u].adj.push_back(v);
    }

    void DFS_visit(Vertex &vertex) {
        time++;
        vertex.color = GRAY;
        vertex.timeDiscover = time;

        for (int adjVertexId : vertex.adj) {
            Vertex &adjVertex = vertices[adjVertexId];

            if (adjVertex.color == WHITE) {
                adjVertex.parent = &vertex;
                DFS_visit(adjVertex);
            }
        }

        vertex.color = BLACK;
        time++;//
        vertex.timefinish = time;
    }

    void DFS() {
        for (Vertex &vertex : vertices) {
            if (vertex.color == WHITE) {
                DFS_visit(vertex);
            }
        }
    }

    void printDFS() {
        for (Vertex& u : vertices) {
            cout << "Vertex " << u.id << ": "
                 << "d = " << u.timeDiscover << ", "
                 << "f = " << u.timefinish << ", "
                 << "parent = ";
            if (u.parent) cout << u.parent->id;
            else cout << "NIL";
            cout << endl;
        }
    }

};

// =====================
//     DFS - adjList
// =====================

struct Node {
    int label;
    list<int> neighbours;
};

struct Graph
{
    int n;
    Node *nodes;

    // for DFS
    int time;
    vector<char> color;
    vector<int> parent;
    vector<int> timeDiscover;
    vector<int> timeFinish;

    Graph(int size) {
        n = size;
        nodes = new Node[n];

        for (int i = 0; i < n; i++) {
            nodes[i].label = i+1;
        }

        // for DFS
        time = 0;
        color = vector<char> (n, 'w');
        parent = vector<int> (n, -1);
        timeDiscover = vector<int> (n, 0);
        timeFinish = vector<int> (n, 0);
    }

    ~Graph() {
        delete[] nodes;
    }

    void addEdge(int u, int v) {
        /*
         * add edges for directed graphs
         */

        nodes[u-1].neighbours.push_back(v-1);
    }

    void printGraph() {
        /**
         * print the graph
         */
        for (int i=0; i<n; i++) {
            cout << nodes[i].label << " --> ";

            for (int adjVert : nodes[i].neighbours) {
                cout << adjVert+1 << " ";
            }
            cout << endl;
        }
    }

    void DFS_visit(Node &node) {
        color[node.label-1] = 'g';
        time++;
        timeDiscover[node.label-1] = time;

        cout << "visited : " << node.label << endl;

        for (int adjNodeVal : node.neighbours) {
            if (color[adjNodeVal] == 'w') {
                parent[adjNodeVal] = node.label;
                DFS_visit(nodes[adjNodeVal]);

            }
        }

        color[node.label-1] = 'b';
        time++;
        timeFinish[node.label-1] = time;


    }

    void DFS() {


        for (int i = 0; i < n; i++) {
            if (color[i] == 'w') {
                DFS_visit(nodes[i]);
            }
        }
    }

};

// ===========
//     BFS
// ===========

struct Node {
    int label;
    list<int> neibhours;
};

struct Graph
{
    int n;
    Node *nodes;

    Graph(int size) {
        n = size;
        nodes = new Node[n];

        for (int i = 0; i < n; i++) {
            nodes[i].label = i+1;
        }
    }

    ~Graph() {
        delete[] nodes;
    }

    void addEdge(int u, int v) {
        /*
         * add edges for undirected graphs
         */
        nodes[u-1].neibhours.push_back(v-1);
        nodes[v-1].neibhours.push_back(u-1);
    }

    void printGraph() {
        /**
         * print the graph
         */
        for (int i=0; i<n; i++) {
            cout << nodes[i].label+1 << " --> ";

            for (int adjVert : nodes[i].neibhours) {
                cout << adjVert+1 << " ";
            }
            cout << endl;
        }
    }

    void BFS(int start) {
        queue<int> q;
        vector<bool> visited(n, false);

        q.push(start-1);
        visited[start-1] = true;

        while (!q.empty()) {
            int crnt = q.front();
            cout << crnt + 1 << " ";
            q.pop(); // dequeue

            // add neigbhours of crnt
            for (int neigbhour : nodes[crnt].neibhours) {
                // enqueuing only unless visited
                if (!visited[neigbhour]) {
                    q.push(neigbhour);
                    visited[neigbhour] = true;
                }
            }


        }
    }
};

/*
   =================================
       MST : Kruskal's algorithm
   =================================
    * Weighted
    * Directed / Undirected

    * Approach : Greedy
*/

#define edge pair<int, int>

class Graph {
private:
    vector<pair<int, edge>> graph;
    vector<pair<int, edge>> mst;
    int *parents;
    int size;

public:
    Graph(int n) {
        size = n;
        parents = new int[n];

        for (int i=0; i<size; i++) {
            parents[i] = i;
        }

        graph.clear();
        mst.clear();
    }

    void addEdge(int u, int v, int w) {
        graph.push_back(make_pair(w, edge(u, v)));
    }

    int findSet(int u) {
        if (u == parents[u]) {
            return u;
        }

        return findSet(parents[u]);
    }

    void unionSet(int u, int v) {
        parents[u] = parents[v];
    }

    void kruskal() {
        int u, v;
        sort(graph.begin(), graph.end());

        for (pair<int, edge> p : graph) {
            u = findSet(p.second.first);
            v = findSet(p.second.second);

            if (u != v) {
                mst.push_back(p);
                unionSet(u, v);
            }
        }
    }

    void printGraph() {
        for (pair<int, edge> p : mst) {
            cout << p.second.first << "-" << p.second.second << " (" << p.first << ")" << endl;
        }
        cout << endl;
    }

};

/*
    ==============================
        MST : Prim's algorithm
    ==============================
     * Weighted
     * Directed / Undirected

     * Approach : Greedy
*/

const int INF = 1e6;

struct Edge {
    int to;
    int weight;
};

class Graph {
    int size;
    vector<vector<int>> graph;
    map<int, set<int>> adj;
    vector<int> dist;
    vector<int> parents;
    vector<bool> inMST;
    bool isMST;

public:
    Graph(int size) {
        this->size = size;
        graph = vector<vector<int>>(size, vector<int>(size, INF));
        dist = vector<int>(size, INF);
        parents = vector<int>(size, -1);
        inMST = vector<bool>(size, false);
        isMST = false;
    }

    void addEdge(int u, int v, int w) {
        int w_min = min(w, graph[u][v]);
        graph[u][v] = w_min;
        graph[v][u] = w_min; // for undirected graphs

//        graph[u][v] = w;
//        graph[v][u] = w;

        adj[u].insert(v);
        adj[v].insert(u); // for undirected graphs
    }

    void MST_Prim(int start) {
        // most part of the initialize has done in class construction (eg : dist, parents)

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // store key and node
        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {

            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;

            for (int v : adj[u]) {
                int w = graph[u][v];

                if (!inMST[v] && dist[v] > w) {
                    dist[v] = w;
                    pq.push({w, v});
                    parents[v] = u;
                    //    cout << u << "-" << v << " (" << w << ")"<< endl;
                }
            }
        }
        isMST = true;
    }

    vector<int> getParents() {
        return this->parents;
    }

    vector<int> getDist() {
        if (!isMST) MST_Prim(0);
        return this->dist;
    }

    vector<int> getPath(int start, int end) {
        /*
         * path in MST. (This is not SSSP)
         */
        vector<int> path;

        int crnt = end;

        do {
            path.push_back(crnt);
            crnt = parents[crnt];
        } while (crnt!=parents[start]);

        reverse(path.begin(), path.end());
        return path;
    }

    int getTotalWeight() {
        if (!isMST) MST_Prim(0);

        int totalWeight = 0;
        for (int u=0; u<size; u++) {
            if (parents[u] == -1) continue;
            int v = parents[u];

            totalWeight += graph[u][v];
        }

        return totalWeight;
    }

};

/*
    ====================================
        SSSP : BellmanFord algorithm
    ====================================
     * Weighted
     * Directed
     * Negative weight edges allowed

     * Approach : Dynamic Programming
*/

int INF = 1e6;

class Graph {
public:
    int size;
    vector<edge> g_edges;
    vector<int> g_weights;
    vector<int> dist;
    vector<int> parents;

    Graph (int size) {
        this->size = size;

        for (int i=0; i<size; i++) {
            dist.push_back(INF);
            parents.push_back(-1);
        }
    }

    void addEdge(int u, int v, int w) {
        g_edges.push_back(edge(u, v));
        g_weights.push_back(w);
    }

    void relax(int u, int v, int w) {
        if (dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            parents[v] = u;
        }
    }

    bool BellmanFord(int s) {
        dist[s] = 0;

        for (int j=0; j<size-1; j++) {
            for (int i=0; i<g_edges.size(); i++) {
                relax(g_edges[i].first, g_edges[i].second, g_weights[i]);
            }
        }

        for (int i=0; i<g_edges.size(); i++) {
            if (dist[g_edges[i].second] > dist[g_edges[i].first] + g_weights[i]) {
                return false;
            }
        }
        return true;
    }
};

/*
    ===================================
        SSSP : Dijkstra's algorithm
    ===================================
     * Weighted
     * Directed / Undirected
     * Non-negative weights

     * Approach : Greedy

*/

const int INF = 1e9;

struct Node {
    int value;
    bool visited;
    int dist;
    vector<int> neighbours;
};

class Graph {
    int size;
    Node *nodes;
    vector<vector<int>> graph;
    vector<bool> visited;

public:
    Graph(int size) {
        this->size = size;
        nodes = new Node[size];
        graph = vector<vector<int>>(size, vector<int>(size, INF));

        for (int i=0; i<size; i++) {
            nodes[i].value = i;
            nodes[i].dist = INF;
            nodes[i].visited = false;
        }
    }

    void addEdge(int u, int v, int w) {
        graph[u][v] = w;
        nodes[u].neighbours.push_back(v);
    }

    void SSSP_Dijkstra(int start) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, start});
        nodes[start].dist=0;

        while (!pq.empty()) {
            int u_dist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            // visiting if not visited yet
            if (!nodes[u].visited) {
                cout << "visited : " << u  << " | visited " << nodes[u].visited << endl;
                nodes[u].visited = true;
            }

            // relaxation
            for (int v : nodes[u].neighbours) {
                if (nodes[u].dist + graph[u][v] < nodes[v].dist && !nodes[v].visited) {
                    nodes[v].dist = nodes[u].dist + graph[u][v];
                    pq.push({nodes[v].dist, v});
                }
            }
        }

        cout << "\nFinal distances from source " << start << ":\n";
        for (int i = 0; i < size; ++i) {
            cout << "Node " << i << ": " << nodes[i].visited << endl;
        }
    }

    ~Graph() {
        delete[] nodes;
    }

    vector<int> getDist() {
        vector<int> distances(size);
        for (int i = 0; i < size; ++i) {
            distances[i] = nodes[i].dist;
        }
        return distances;
    }
};


/*
   ================
       Knapsack
   ================
*/

class knacsack {
    int size;
    vector<vector<int>> memory;
    int count;

public:
    knacsack(int size, int capacity) {
        memory = vector<vector<int>>(size, vector<int>(capacity, -1));
        this->size = size;
        // count = 0;
    }

    int P(vector<int> arr_w, vector<int> arr_p, int i, int k) {
        count++;
        // cout << memory[0][0];
        int n = arr_w.size()-1;

        // ---- switch "Memory" ----
        if (memory[size-1-i][k-1]!=-1) {
            return memory[size-1-i][k-1];
        }
        // -------------------------

        int p_i;

        if (i==n) {
            if (arr_w[i] > k) {
                p_i = 0;
            } else {
                // memory[i][k-1] = arr_p[i];
                p_i = arr_p[i];
            }
        } else {
            if (arr_w[i] > k) {
                p_i = P(arr_w, arr_p, i+1, k);
            } else {
                p_i = max(P(arr_w, arr_p, i+1, k), arr_p[i] + P(arr_w, arr_p, i+1, k-arr_w[i]));
            }
        }
        cout << i << " " << k-1 << " " << p_i<<endl;
        memory[size-1-i][k-1] = p_i;
        return p_i;

    }

    void printMemory() {
        for (vector<int> row : memory) {
            for (int num : row) {
                cout << setw(5)<< num ;
            }
            cout << endl;
        }
    }

    int getCount() {
        return count;
    }

};

/*
   ===============
       Sorting
   ===============
*/

// ---- Merge ----
const int inf = 1e9;

void printArr(vector<int> &arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

void merge(vector<int> &arr, int p, int q, int r) {
    int n1 = q-p+1, n2 = r-q;
    vector<int> L(n1 + 1), R(n2 + 1);

    for (int i=0; i<n1; i++) {
        L[i] = arr[p+i];
    }

    for (int j=0; j<n2; j++) {
        R[j] = arr[q+1+j];
    }

    L[n1] = inf;
    R[n2] = inf;

    int i=0, j=0;

    printArr(arr);

    for (int k=p; k<r+1; k++) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        printArr(arr);
    }
    cout << "--- p :" << p << " r : " << r << "---" << endl;
}

void mergeSort(vector<int> &arr, int p, int r) {
    if (p<r) {
        int q = (p+r)/2;

        mergeSort(arr, p, q);
        mergeSort(arr, q+1, r);
        merge(arr, p, q, r);
    }
}

// ---- Quick ----
int partition(vector<int> &arr, int left, int right) {
    int i = left+1, j = right;
    int piv = arr[left];

    while (true) {
        while (i <= right && arr[i] < piv) i++;

        while (j >= left && arr[j] > piv) j--;

        if (i >= j) break;

        swap(arr[i], arr[j]);
        i++;
        j--;
    }

    swap(arr[left], arr[j]);
    return j;
}

void quickSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        cout << left << " " << right << " | ";
        printArr(arr);
        int pivPos = partition(arr, left, right);

        quickSort(arr, left, pivPos-1);
        quickSort(arr, pivPos+1, right);
    }
}