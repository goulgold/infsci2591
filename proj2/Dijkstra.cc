/* Floyd Algorithm search shortest path in a graph.
 * Qiming Guo
 * Oct 15 2015
 */
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Graph_Matrix.h"

using std::cout;
using std::endl;
using std::min;

void Dijkstra (Graph& graph, int* edges, int* weights, int origin) {
    int num_vertex = graph.getNumVertex();
    int vnear;
    int* touch = new int[num_vertex];
    int* length = new int[num_vertex];

    // Initialize touch[] and length[]
    for (int i = 0; i < num_vertex; ++i) {
        if (i == origin) {
            touch[i] = 0;
            length[i] = 0;
            weights[i] = 0;
            edges[i] = i;
        } else if (graph.isNeighbor(i, origin)) {
            touch[i] = origin;
            length[i] = graph.getWeight(i, origin);
            weights[i] = length[i];
        } else {
             touch[i] = -1;
             length[i] = -1;
             weights[i] = length[i];
        }
    }

    for (int iter = 0; iter < num_vertex; ++iter) {
        // Check each vertex for having shortest path.
        int min = -1;
        for (int i = 0; i < num_vertex; ++i) {
            if (min == -1 && length[i] > 0) {
                min = length[i];
                vnear = i;
            } else if (length[i] > 0 && length[i] < min) {
                 min = length[i];
                 vnear = i;
            }
        }
        // Add new edges to set_of_edges
        edges[vnear] = touch[vnear];

        for (int i = 0; i < num_vertex; ++i) {
            int weight = graph.getWeight(i, vnear);
            if (length[i] == -1 && weight != -1) {
                length[i] = length[vnear] + weight;
                weights[i] = length[i];
                touch[i] = vnear;
            } else if (length[i] > 0 && weight != -1 && weight + length[vnear] < length[i]) {
                length[i] = length[vnear] + weight;
                weights[i] = length[i];
                touch[i] = vnear;
            }
        }

        length[vnear] = 0;
    }

}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Parameter: Dijkstra matrix_file origin\n";
        exit(1);
    }
    ifstream file;
    file.open(argv[1]);
    int origin = atoi(argv[2]);
    Graph* pgraph = new Graph(file);
    file.close();
    int num_vertex = pgraph->getNumVertex();
    int* PathEdges = new int[num_vertex];
    int* ShortestWeight = new int[num_vertex];
    Dijkstra(*pgraph, PathEdges, ShortestWeight, origin);
    pgraph->Show();
    for (int i = 0; i <num_vertex; ++i) {
         cout << ShortestWeight[i] << " ";
    }
    cout << endl;
    return 0;
}
