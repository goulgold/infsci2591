#include "Graph_Matrix.h"

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
    file.seekg(file.beg);
    weightMatrix_ = new int*[num_vertex];
    for (int i = 0; i < num_vertex; ++i) {
        weightMatrix_[i] = new int[num_vertex];
    }
    int index = 0;
    while (file.good()) {
        file >> temp;
        if (temp == ".") {
             weightMatrix_[index/num_vertex][index%num_vertex] = -1;
        } else {
            weightMatrix_[index/num_vertex][index%num_vertex] = atoi(temp.c_str());
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < num_vertex; ++i) {
        delete[] weightMatrix_[i];
    }
    delete[] weightMatrix_;
}

int Graph::getWeight(int i, int j) {
    return weightMatrix_[i][j];
}

int Graph::setWeight(int i, int j, int weight) {
    weightMatrix_[i][j] = weight;
    return 0;
}

int Graph::getNumVertex() {
     return num_vertex;
}
