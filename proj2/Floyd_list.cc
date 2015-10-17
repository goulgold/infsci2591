/* Floyd Algorithm search shortest path in a graph.
 * Qiming Guo
 * Oct 15 2015
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "include/Graph_List.h"
#include "include/util.h"

using std::string;
using std::cout;
using std::endl;
using std::min;

void ShowMatrix(int** mat, int num_vertex) {
    for (int i = 0; i < num_vertex; ++i) {
        for (int j = 0; j < num_vertex; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void Floyd (int** result, int num_vertex) {
    int n = num_vertex;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if (result[i][k] == -1 || result[k][j] == -1) {
                    continue;
                } else if (result[i][j] == -1) {
                    result[i][j] = result[i][k] + result[k][j];
                    result[j][i] = result[i][j];
                }
                else {
                    int new_wt = min(result[i][j], result[i][k] + result[k][j]);
                    result[i][j] = new_wt;
                    result[j][i] = new_wt;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Useage: -f matrix_file\n"
             << "        -n num_vertex\n";
        exit(1);
    }
    string param = argv[1];
    int num_vertex;
    Graph* origin;
    if (param == "-f") {
        ifstream file;
        file.open(argv[2]);
        origin = new Graph(file);
        num_vertex = origin->getNumVertex();
    } else if (param == "-n") {
        num_vertex = atoi(argv[2]);
        origin = new Graph(num_vertex);
    } else {
        cout << "Useage: -f matrix_file\n"
             << "        -n num_vertex\n";
        exit(1);

    }
    int** result = new int*[num_vertex];
    for (int i = 0; i < num_vertex; ++i) {
         result[i] = new int[num_vertex];
    }
    for (int i = 0; i < num_vertex; ++i) {
        for (int j = 0; j < num_vertex; ++j) {
            result[i][j] = -1;
        }
    }
#ifdef VERBOSE
    origin->Show();
#endif
    origin->outputMatrix(result);
    Floyd(result, num_vertex);
#ifdef VERBOSE
    ShowMatrix(result, num_vertex);
#endif

    return 0;
}
