#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
#include <set>
#include "util.h"

using namespace std;


class TSP {
    private:
        static int **W_;
        static int n_;

        struct node {
            int level;
            vector<int> path;
        };

        static int length(vector<int>& path) {
            int result = 0;
            for (vector<int>::iterator it = path.begin(); it < path.end() - 1; ++it) {
            result += W_[*it][*(it+1)];;
            }
            return result;
        }

        static bool pfind(vector<int>& path, int i) {
            std::vector<int>::iterator it;
            it = find (path.begin(), path.end(), i);
            if (it != path.end()) {
                return true;
            } else {
                return false;
            }
        }
        static int lindex(vector<int>& path) {
            for (int i = 2; i <= n_; ++i) {
                if (!pfind(path, i)) {
                    return i;
                }
            }
            return -1;
        }

    public:
        static void tsp (int n,
                         int **W,
                         vector<int>& opttour,
                         int& minlength) {
            n_ = n;
            W_ = W;
            queue<node> Q;
            node v,u;
            v.level = 0;
            v.path.push_back(1);
            Q.push(v);
            while(!Q.empty()) {
                v = Q.front();
                Q.pop();
                if (v.level < n-2) {
                    u.level = v.level + 1;
                    for (int i = 2; i <= n; ++i) {
                        u.path = v.path;
                        if (!pfind(u.path, i)) {
                            u.path.push_back(i);
                            Q.push(u);
                        }
                    }
                } else {
                    int last_index = lindex(v.path);
                    v.path.push_back(last_index);
                    v.path.push_back(1);
                    if (length(v.path) < minlength) {
                        minlength = length(v.path);
                        opttour = v.path;
                    }
                }
            }
        }
};

int TSP::n_;
int **TSP::W_;

int main(int argc, char* argv[]) {
    int n;
    int **w;
    string param = argv[1];
    if (param == "-f") {
        if (argc != 4) {
            cout << "error" << endl;
            return -1;
        }
        n = atoi(argv[3]);
        w = allocMatrix(n+1);
        readMatrixFile(w, n+1, argv[2]);
    } else if (param == "-n") {
         if (argc != 3) {
            cout << "error" << endl;
            return -1;
        }
        n = atoi(argv[2]);
        w = randomMatrix(n+1);
    } else {
        cout << "error" << endl;
        return -1;
    }
        vector<int>opttour;
        int minlength;
    TSP::tsp(n, w, opttour, minlength);
    cout << minlength << endl;
    vector<int>::iterator it;
    for (it = opttour.begin(); it != opttour.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
