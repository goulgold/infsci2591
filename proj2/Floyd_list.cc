/* Floyd Algorithm search shortest path in a graph.
 * Qiming Guo
 * Oct 15 2015
 */
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Graph_List.h"

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
    if (argc != 2) {
        cout << "Parameter: Floyd matrix_file\n";
        exit(1);
    }
    ifstream file;
    file.open(argv[1]);
    Graph* origin = new Graph(file);
    origin->Show();
    int num_vertex = origin->getNumVertex();
    int** result = new int*[num_vertex];
    for (int i = 0; i < num_vertex; ++i) {
         result[i] = new int[num_vertex];
    }
    for (int i = 0; i < num_vertex; ++i) {
        for (int j = 0; j < num_vertex; ++j) {
            result[i][j] = -1;
        }
    }
    ShowMatrix(result, num_vertex);
    origin->outputMatrix(result);
    ShowMatrix(result, num_vertex);
    Floyd(result, num_vertex);
    ShowMatrix(result, num_vertex);
    return 0;
}
