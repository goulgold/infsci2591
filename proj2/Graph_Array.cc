#include "include/Graph_Array.h"

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
    weightMatrix_ = new int[num_vertex*(num_vertex-1)/2];
    for (int i = 0; i < num_vertex*(num_vertex-1)/2; ++i) {
        weightMatrix_[i] = -1;
    }
    int index = 0;
    while (file >> temp) {
        if (temp != ".") {
            setWeight(index/num_vertex, index%num_vertex, atoi(temp.c_str()));
        }
        index++;
    }
}

Graph::Graph(int n) {
    num_vertex = n;
    weightMatrix_ = new int[n*(n-1)/2];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            setWeight(i,j,-1);
        }
    }
    int connect;
    srand(time(NULL));
    for (int i = 1; i < n; ++i) {
        connect = rand() % i;
        setWeight(i, connect, rand() % MAX_WEIGHT + 1);
        if (rand() % 100 > 30) {
            connect = rand() % i;
            setWeight(i, connect, rand() % MAX_WEIGHT + 1);
        }
    }

}
Graph::~Graph() {
    //TODO
}

bool Graph::isNeighbor(int i, int j) {
    if (Graph::getWeight(i, j) != -1) {
        return true;
    } else {
        return false;
    }
}

int Graph::getWeight(int i, int j) {
    int index;
    if (i > j) {
        index = i*(i-1)/2 + j;
    } else {
        index = j*(j-1)/2 + i;
    }
    return weightMatrix_[index];
}

int Graph::setWeight(int i, int j, int weight) {
    int index;
    if (i > j) {
        index = i*(i-1)/2 + j;
    } else {
        index = j*(j-1)/2 + i;
    }
    weightMatrix_[index] = weight;
    return 0;
}

int Graph::getNumVertex() {
     return num_vertex;
}

void Graph::Show() const {
    for (int i = 1; i < num_vertex; ++i) {
        for (int j = 0; j < i; ++j) {
            cout << weightMatrix_[i*(i-1)/2 + j] << " ";
        }
        cout << endl;
    }
}
