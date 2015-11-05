#include <iostream>
#include <queue>

using namespace std;
class Knapsack {
    private:
        static int *p_;
        static int *w_;
        static int n_;
        static int W_;

        struct node {
            int weight;
            int profit;
            int level;
            double bound;
        };

        class compare {
             public:
                 bool operator() (const node& ln, const node& rn) const {
                     return (ln.bound < rn.bound);
                 }
        };

        static double bound(node n) {
            int totweight = n.weight;
            double result = n.profit;
            int j = n.level + 1;
            while (j <= n_ && totweight + w_[j] <= W_) {
                 totweight += w_[j];
                 result += p_[j];
                 j++;
            }
            if (j <=n_ ) {
                 result += (W_ - n.weight) * p_[j]/w_[j];
            }
            return result;
        }

    public:
        static void knapsack (int n,
                              int p[],
                              int w[],
                       int W,
                       int& maxprofit) {
            n_ = n;
            p_ = p;
            w_ = w;
            W_ = W;
            priority_queue<node, vector<node>, compare> Q;
            node v, u;
            maxprofit = 0;
            v.weight = 0;
            v.profit = 0;
            v.level = 0;
            v.bound = bound(v);
            Q.push(v);
            while (!Q.empty()) {
                v = Q.top();
                Q.pop();
                u.level = v.level + 1;
                if (u.level <= n_) {
                    u.weight = v.weight + w[u.level];
                    u.profit = v.profit + p[u.level];
                    if (u.profit > maxprofit && u.weight <= W) {
                        maxprofit = u.profit;
                    }
                    if (bound(u) > maxprofit) {
                        Q.push(u);
                    }
                    u.weight = v.weight;
                    u.profit = v.profit;
                    if (bound(u) > maxprofit) {
                        Q.push(u);
                    }
                }
            }
        }
};

int *Knapsack::p_;
int *Knapsack::w_;
int Knapsack::n_;
int Knapsack::W_;

int main(int argc, char* argv[]) {
    int level = 5;
    int p_[] = {0, 20, 30, 35, 12, 3};
    int w_[] = {0, 2, 5, 7, 3, 1};
    int result;
    Knapsack::knapsack(level, p_, w_, 13, result);
    cout << result << endl;
    return 0;
}
