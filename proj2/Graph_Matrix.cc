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
    file.clear();
    file.seekg(0, file.beg);
    weightMatrix_ = new int*[num_vertex];
    for (int i = 0; i < num_vertex; ++i) {
        weightMatrix_[i] = new int[num_vertex];
    }
    int index = 0;
    while (file >> temp) {
        if (temp == ".") {
        weightMatrix_[index/num_vertex][index%num_vertex] = -1;
        } else {
            weightMatrix_[index/num_vertex][index%num_vertex] = atoi(temp.c_str());
        }
        index++;
    }
}

Graph::Graph(int n) {
    num_vertex = n;
    weightMatrix_ = new int*[num_vertex];
    for (int i = 0; i < num_vertex; ++i) {
        weightMatrix_[i] = new int[num_vertex];
    }
    for (int i = 0; i < num_vertex; ++i) {
        for (int j = 0; j < num_vertex; ++j) {
            setWeight(i,j,-1);
        }
    }
    int connect;
    srand(time(NULL));
    for (int i = 1; i < num_vertex; ++i) {
        connect = rand() % i;
        setWeight(i, connect, rand() % MAX_WEIGHT);
        if (rand() % 100 > 80) {
            connect = rand() % i;
            setWeight(i, connect, rand() % MAX_WEIGHT);
        }
    }

}
Graph::~Graph() {
    for (int i = 0; i < num_vertex; ++i) {
        delete[] weightMatrix_[i];
    }
    delete[] weightMatrix_;
}

bool Graph::isNeighbor(int i, int j) {
    if (Graph::getWeight(i, j) != -1) {
        return true;
    } else {
         return false;
    }
}

int Graph::getWeight(int i, int j) {
    return weightMatrix_[i][j];
}

int Graph::setWeight(int i, int j, int weight) {
    weightMatrix_[j][i] = weight;
    weightMatrix_[i][j] = weight;
    return 0;
}

int Graph::getNumVertex() {
     return num_vertex;
}

void Graph::Show() {
    for (int i = 0; i < num_vertex; ++i) {
        for (int j = 0; j < num_vertex; ++j) {
            cout << weightMatrix_[i][j] << " ";
        }
        cout << endl;
    }
}
