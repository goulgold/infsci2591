#include <Graph_List.h>

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
}

Graph::~Graph() {
     //TODO
    delete[] vertexs;
}

Graph::isNeighbor(int i, int j)

