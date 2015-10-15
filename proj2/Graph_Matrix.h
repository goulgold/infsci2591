#ifndef GRAPH_MATRIX_
#define GRAPH_MATRIX_
/* Graph implemented by 2-D matrix
 * Qiming Guo
 * Oct 15 2015
 */

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <climits>
using std::cout;
using std::endl;
using std::ifstream;
using std::string;


class Graph {
    private:
        int num_vertex;
        int **weightMatrix_;
    public:
        Graph(ifstream& file);
        ~Graph();
        int getWeight(int i, int j);
        int setWeight(int i, int j, int weight);
        int getNumVertex();
        void Show();
};

#endif
