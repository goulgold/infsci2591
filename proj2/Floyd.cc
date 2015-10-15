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
                int new_wt = min(result.getWeight(i,j), result.getWeight(i,k) + result.getWeight(k,j));
                if (!result.setWeight(i,j,new_wt)) {
                    cout << "weight updated failed.\n";
                    exit(1);
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
    Graph* mygraph = new Graph(file);
    mygraph->Show();
    return 0;
}
