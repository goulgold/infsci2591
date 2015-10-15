#ifndef GRAPH_LIST_
#define GRAPH_LIST_
/* Graph implemented by linked list
 * Qiming Guo
 * Oct 15 2015
 */

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

#define MAX_WEIGHT 50

class Graph {
    private:
        struct edgeNode {
            int index;
            int weight;
            edgeNode* next;
            edgeNode(int n, int w): index(n), weight(w), next(nullptr) {}
        };
        edgeNode** vertexs;
        int num_vertex;
        int **weightMatrix_;
    public:
        Graph(ifstream& file);
        Graph(int n);
        ~Graph();
        bool isNeighbor(int i, int j);
        int getWeight(int i, int j);
        int setWeight(int i, int j, int weight);
        int getNumVertex();
        void Show();
};

#endif
