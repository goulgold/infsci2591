#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <ctime>

using std::cout;
using std::endl;

int ret_mul(int a, int b);

int ret_mul(int a, int b) {
    //Implement algorithm here
    int a_size = 0;
    int b_size = 0;
    while ( a / (int) (pow10(a_size)) != 0) {
        a_size++;
    }
    while (b / (int) (pow10(b_size)) != 0) {
        b_size++;
    }
    if (a_size == 0 || b_size == 0) return 0;
    int *a_num = new int[a_size];
    for (int i = 0; i < a_size; ++i) {
        a_num[i] = a % 10;
        a = a / 10;
    }
    int *b_num = new int[b_size];
    for (int i = 0; i < b_size; ++i) {
        b_num[i] = b % 10;
        b = b / 10;
    }
    int *result = new int[a_size + b_size];
    for (int i = 0; i < a_size; ++i) {
        for (int j = 0; j < b_size; ++j) {
            result[i+j] += (a_num[i] * b_num[j]) % 10;
            result[i+j+1] += (a_num[i] * b_num[j]) / 10;
            if (result[i+j] >= 10) {
                 result[i+j+1] += result[i+j] / 10;
                 result[i+j] = result[i+j] % 10;
            }
        }
    }
    int t_result = 0;
    for (int i = (a_size + b_size - 1); i >= 0; --i) {
         t_result = t_result * 10 + result[i];
    }
    delete[] a_num, b_num, result;
    return t_result;
}

int main (int argc, char *argv[]) {
    if (argc != 3) {
        cout << "./prog <num1> <num2>" << endl;
        return 0;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    std::clock_t start = std::clock();
    double duration;
    int result = ret_mul(a,b);
    cout << a << " * " << b << " = " << result << endl;
    cout << "Time elapsed: " << (std::clock() - start) / 1000.0 << " ms." << endl;
    return 0;
}
