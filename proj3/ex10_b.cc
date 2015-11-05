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
            double bound;
        };

        class compare {
             public:
                 bool operator() (const node& ln, const node& rn) const {
                     return (ln.bound > rn.bound);
                 }
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

        static double bound(vector<int>& path) {
            double result;
            set<int> temp;
            for (int i = 1; i <=n_; ++i) {
                temp.insert(i);
            }
            vector<int>::iterator it;
            for (it = path.begin(); it < path.end() - 1; it++) {
                result += W_[*it][*(it+1)];
                temp.erase(*it);
            }
            int lastnode = *(path.end()-1);
            set<int>::iterator i, j;
            for (i = temp.begin(); i != temp.end(); ++i) {
                double tmin = INT_MAX;
                if (*i == lastnode) {
                    for (j = temp.begin(); j != temp.end(); ++j) {
                        if (W_[*i][*j] < tmin && i != j) {
                            tmin = W_[*i][*j];
                        }
                    }
                } else {
                    for (j = temp.begin(); j != temp.end(); ++j) {
                        if (W_[*i][*j] < tmin && i != j && *j != lastnode) {
                            tmin = W_[*i][*j];
                        }
                    }
                    if (W_[1][*i] < tmin) tmin = W_[1][*i];
                }
                result += tmin;
            }
        return result;
        }

    public:
        static void tsp (int n,
                         int **W,
                         vector<int>& opttour,
                         int& minlength) {
            n_ = n;
            W_ = W;
            priority_queue<node, vector<node>, compare> Q;
            node v, u;
            minlength = INT_MAX;
            v.level = 0;
            v.path.push_back(1);
            v.bound = bound(v.path);
            Q.push(v);
            while (!Q.empty()) {
                v = Q.top();
                Q.pop();
                if (v.bound < minlength) {
                    u.level = v.level + 1;
                    for (int i = 2; i <= n; ++i ) {
                        if (!pfind(v.path, i)) {
                            u.path = v.path;
                            u.path.push_back(i);
                            if (u.level == n-2) {
                                int last_index = lindex(u.path);
                                u.path.push_back(last_index);
                                u.path.push_back(1);
                                if (length(u.path) < minlength) {
                                     minlength = length(u.path);
                                     opttour = u.path;
                                }
                            } else {
                                 u.bound = bound(u.path);
                                 if (u.bound < minlength) {
                                    Q.push(u);
                                 }
                            }
                        }
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
