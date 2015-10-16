#include "Graph_List.h"

Graph::Graph(ifstream& file) {
    if (!file.is_open()) {
        cout<<"Open File Failed.\n";
        exit(1);
    }
    num_vertex = 0;
    string temp;
    while (getline(file, temp)) {
        num_vertex++;
    }
    file.clear();
    file.seekg(0, file.beg);
    vertexs = new edgeNode* [num_vertex];
    ptrs = new edgeNode* [num_vertex];
    int index = 0;
    while (file >> temp) {
        if (temp != ".") {
            edgeNode* newedge = new edgeNode(index % num_vertex, atoi(temp.c_str()));
            edgeNode* oldedge = vertexs[index / num_vertex];
            vertexs[index / num_vertex] = newedge;
            newedge->next = oldedge;
        }
        index++;
    }
}

Graph::Graph(int n) {
     //TODO
    num_vertex = n;
    vertexs = new edgeNode* [num_vertex];
    ptrs = new edgeNode* [num_vertex];

    int connect;
    int weight;
    srand(time(NULL));
    for (int i = 1; i < num_vertex; ++i) {
         connect = rand() % i;
        weight = rand() % MAX_WEIGHT;
        addEdge(i, connect, weight);
        addEdge(connect, i, weight);
         if (rand() % 100 > 80) {
            connect = rand() % i;
            weight = rand() % MAX_WEIGHT;
            addEdge(i, connect, weight);
            addEdge(connect, i, weight);

         }
    }

}

Graph::~Graph() {
     //TODO
    delete[] vertexs;
}

void Graph::outputMatrix(int** output) {
    for (int i = 0; i < num_vertex; ++i) {
        edgeNode* ptr = vertexs[i];
        while (ptr != nullptr) {
            output[i][ptr->index] = ptr->weight;
            output[ptr->index][i] = ptr->weight;
            ptr = ptr->next;
        }
    }
}

int Graph::getNumVertex() {
    return num_vertex;
}

void Graph::Show() {
    for (int i = 0; i < num_vertex; ++i) {
        cout << i <<": ";
        edgeNode* ptr = vertexs[i];
        while(ptr != nullptr) {
            cout << "-->(" << ptr->index << ", " << ptr->weight << ")";
            ptr = ptr->next;
        }
        cout << endl;
    }
}

int Graph::nextNeighbor(int index) {
    if (ptrs[index] == nullptr) {
        ptrs[index] = vertexs[index];
    } else {
        ptrs[index] = ptrs[index]->next;
    }
    if (ptrs[index] == nullptr) {
         return -1;
    } else {
        int rval = ptrs[index]->index;
        return rval;
    }
}

int Graph::thisWeight(int index) {
    return ptrs[index]->weight;
}

void Graph::addEdge(int i, int j, int weight) {
    edgeNode* newedge = new edgeNode(j, weight);
    edgeNode* oldedge = vertexs[i];
    vertexs[i] = newedge;
    newedge->next = oldedge;
}
