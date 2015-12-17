/* Floyd Algorithm search shortest path in a graph.
 * Qiming Guo
 * Oct 15 2015
 */
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <string>
#include "include/Graph_Matrix.h"
#include "include/util.h"

using std::list;
using std::string;
using std::cout;
using std::endl;
using std::min;

void FindShortestPath (Graph& graph, list<int> &PathEdges, int begin, int end) {
    int num_vertex = graph.getNumVertex();
    int vnear_begin, vnear_end;
    int origin;
    int* touch_begin = new int[num_vertex];
    int* touch_end = new int[num_vertex];
    int* length_begin = new int[num_vertex];
    int* length_end = new int[num_vertex];
    int* edges_begin = new int[num_vertex];
    int* edges_end = new int[num_vertex];
    int min;

    origin = begin;
    // Initialize touch[] and length[] of begin node
    for (int i = 0; i < num_vertex; ++i) {
        if (i == origin) {
            touch_begin[i] = 0;
            length_begin[i] = 0;
            edges_begin[i] = -1;
        } else if (graph.isNeighbor(i, origin)) {
            touch_begin[i] = origin;
            length_begin[i] = graph.getWeight(i, origin);
            edges_begin[i] = origin;
        } else {
             touch_begin[i] = -1;
             length_begin[i] = -1;
             edges_begin[i] = -1;
        }
    }
    // Initialize touch[] and length[] of end node
    origin = end;
    for (int i = 0; i < num_vertex; ++i) {
        if (i == origin) {
            touch_end[i] = 0;
            length_end[i] = 0;
            edges_end[i] = -1;
        } else if (graph.isNeighbor(i, origin)) {
            touch_end[i] = origin;
            length_end[i] = graph.getWeight(i, origin);
            edges_end[i] = origin;
        } else {
             touch_end[i] = -1;
             length_end[i] = -1;
             edges_end[i] = -1;
        }
    }


    for (int iter = 0; iter < num_vertex; ++iter) { //TODO iter < num_vertex
        min = -1;
        if (iter % 2 == 0) {
            // side of begin node
            for (int i = 0; i < num_vertex; ++i) {
                // Check each vertex for having shortest path from begin.
                if (min == -1 && length_begin[i] > 0) {
                    min = length_begin[i];
                    vnear_begin = i;
                } else if (length_begin[i] > 0 && length_begin[i] < min) {
                     min = length_begin[i];
                     vnear_begin = i;
                }
            }


            for (int i = 0; i < num_vertex; ++i) {
                int weight = graph.getWeight(i, vnear_begin);
                if (length_begin[i] == -1 && weight != -1) {
                    length_begin[i] = length_begin[vnear_begin] + weight;
                    touch_begin[i] = vnear_begin;
                } else if (length_begin[i] > 0 && weight != -1 && weight + length_begin[vnear_begin] < length_begin[i]) {
                    length_begin[i] = length_begin[vnear_begin] + weight;
                    touch_begin[i] = vnear_begin;
                }
            }
            length_begin[vnear_begin] = 0;
            edges_begin[vnear_begin] = touch_begin[vnear_begin];
            // if the set of begin and set of end meets.
            if (edges_end[vnear_begin] != -1 || vnear_begin == end) {
                int index = vnear_begin;
                PathEdges.push_front(vnear_begin);
                while (edges_begin[index] != -1) {
                    PathEdges.push_front(edges_begin[index]);
                    index = edges_begin[index];
                }
                index = vnear_begin;
                while (edges_end[index] != -1) {
                    PathEdges.push_back(edges_end[index]);
                    index = edges_end[index];
                }
                return;
            }


        } else {
            // side of end node
            for (int i = 0; i < num_vertex; ++i) {
                // Check each vertex for having shortest path from begin.
                if (min == -1 && length_end[i] > 0) {
                    min = length_end[i];
                    vnear_end = i;
                } else if (length_end[i] > 0 && length_end[i] < min) {
                    min = length_end[i];
                    vnear_end = i;
                }
            }

            edges_end[vnear_end] = touch_end[vnear_end];
            // if the set of begin and set of end meets.
            if (edges_begin[vnear_end] != -1 || vnear_end == begin) {
                int index = vnear_end;
                PathEdges.push_front(vnear_end);
                while (edges_begin[index] != -1) {
                    PathEdges.push_front(edges_begin[index]);
                    index = edges_begin[index];
                }
                index = vnear_end;
                while (edges_end[index] != -1) {
                    PathEdges.push_back(edges_end[index]);
                    index = edges_end[index];
                }
                return;
            }


            for (int i = 0; i < num_vertex; ++i) {
                int weight = graph.getWeight(i, vnear_begin);
                if (length_begin[i] == -1 && weight != -1) {
                    length_begin[i] = length_begin[vnear_begin] + weight;
                    touch_begin[i] = vnear_begin;
                } else if (length_begin[i] > 0 && weight != -1 && weight + length_begin[vnear_begin] < length_begin[i]) {
                    length_begin[i] = length_begin[vnear_begin] + weight;
                    touch_begin[i] = vnear_begin;
                }
            }
            length_begin[vnear_begin] = 0;
            edges_end[vnear_end] = touch_end[vnear_end];
            // if the set of begin and set of end meets.
            if (edges_begin[vnear_end] != -1 || vnear_end == begin) {
                int index = vnear_end;
                PathEdges.push_front(vnear_end);
                while (edges_begin[index] != -1) {
                    PathEdges.push_front(edges_begin[index]);
                    index = edges_begin[index];
                }
                index = vnear_end;
                while (edges_end[index] != end) {
                    PathEdges.push_back(edges_end[index]);
                    index = edges_end[index];
                }
                return;
            }
        }
    }

}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Useage: Dijkstra -f matrix_file begin end\n"
             << "        Dijkstra -n num_vertex begin end\n";
        exit(1);
    }
    string param = argv[1];
    int begin = atoi(argv[3]);
    int end = atoi(argv[4]);
    int num_vertex;
    Graph* pgraph;
    if (param == "-f") {
        ifstream file;
        file.open(argv[2]);
        pgraph = new Graph(file);
        num_vertex = pgraph->getNumVertex();
        file.close();
    } else if (param == "-n") {
        num_vertex = atoi(argv[2]);
        pgraph = new Graph(num_vertex);
    } else {
        cout << "Useage: Dijkstra -f matrix_file origin\n"
             << "        Dijkstra -n num_vertex origin\n";
        exit(1);
    }

    list<int> PathEdges;
    FindShortestPath(*pgraph, PathEdges, begin, end);
#ifdef VERBOSE
    pgraph->Show();
    cout << endl;
        while (!PathEdges.empty()) {
            int index = PathEdges.front();
            cout << index << "-->";
            PathEdges.pop_front();
        }
#endif
    return 0;
}
