#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <bitset>

using namespace std;

float targetfunc(int x);

float targetfunc(int x) {
    return sin(x*M_PI/256);
}

class MaxValue {
    private:
        int num_;
        float (*func_)(int);
        int *parents;
        int *children;
        float *fitness;
        float *cumfitness;
        void updateFitness(); // update fitness
        int select(); // select a parents randomly according to fitness;
        void swapvalue(); // swap parents and children
        void crossovers(int i, int j); // cross over parent i, j to children
        void mutate(int i); // mutate ith children
    public:
        MaxValue(float (*func)(int), int num);
        float maxFitness();
        void Start(void);
};
void MaxValue::Start() {
    for (int i = 0; i < 20; ++i) {
        updateFitness();
        for (int j = 0; j < num_; ++j) {
            children[j] = parents[select()];
        }
        for (int j = 0; j < num_-1; j += 2) {
            crossovers(j, j+1);
        }
        for (int j = 0; j < num_; ++j) {
            mutate(j);
        }
        swapvalue();
        cout << "max: " << maxFitness() << endl;
    }
    updateFitness();
}
MaxValue::MaxValue(float (*func)(int), int num) {
    num_ = num;
    func_ = func;
    parents = new int[num];
    children = new int[num];
    fitness = new float[num];
    cumfitness = new float[num];
    srand(time(0));
    for (int i = 0; i < num_; ++i) {
         parents[i] = rand() % 255;
    }
}
float MaxValue::maxFitness() {
    float result = 0.0;
    cout << "value: " << endl;
    for (int i = 0; i < num_; ++i) {
        cout << (*func_)(parents[i]) << endl;
        if ((*func_)(parents[i]) > result)
            result = (*func_)(parents[i]);
    }
    return result;
}
void MaxValue::updateFitness() { // update fitness
    float total = 0.0;
    for (int i = 0; i < num_; ++i) {
        total += (*func_)(parents[i]);
    }
    for (int i = 0; i < num_; ++i) {
        fitness[i] = (*func_)(parents[i]) / total;
    }
    total = 0.0;
    for (int i = 0; i < num_; ++i) {
        cumfitness[i] = total + fitness[i];
        total += fitness[i];
    }
}
void MaxValue::swapvalue() {
    copy(children, children+num_, parents);
}
void MaxValue::mutate(int i) {
    for (int j = 0; j < 8; ++j) {
        int test = rand() % 100;
        if (test == 1) {
            int mask = 1 << j;
            children[i] = children[i]^mask;
        }
    }

}
int MaxValue::select() {
    float val = (float) (rand() % 100) / 100.0;
    // TODO
    for (int i = num_-1; i >= 0; --i) {
        if (val > cumfitness[i]) {
            return i;
        }
    }
    return 0;
}
void MaxValue::crossovers(int i, int j) {
    int lp = rand() % num_;
    int rp = rand() % num_;
    int mask = 0;
    for (int k = rp; k != lp; k = (k+1) % 8) {
        mask = mask | 1 << k;
    }
    int part_i = parents[i] & mask;
    int part_j = parents[j] & mask;
    children[i] = parents[i] - part_i + part_j;
    children[j] = parents[j] - part_j + part_i;

}
int main() {
    MaxValue m = MaxValue(&targetfunc, 8);
    m.Start();
    return 0;
}
