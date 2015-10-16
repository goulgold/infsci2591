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

void Floyd (Graph& origin, Graph& result) {
    int n = origin.getNumVertex();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if (result.getWeight(i,k) == -1 || result.getWeight(k,j) == -1) {
                    continue;
                } else if (result.getWeight(i,j) == -1) {
                    result.setWeight(i,j,result.getWeight(i,k) + result.getWeight(k,j));
                }
                else {
                    int new_wt = min(result.getWeight(i,j), result.getWeight(i,k) + result.getWeight(k,j));
                    if (result.setWeight(i,j,new_wt)) {
                        cout << "weight updated failed.\n";
                        exit(1);
                    }
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
    ifstream file1, file2;
    file1.open(argv[1]);
    file2.open(argv[1]);
    Graph* origin = new Graph(file1);
    Graph* result = new Graph(file2);
    result->Show();
    Floyd(*origin, *result);
    result->Show();
    return 0;
}
