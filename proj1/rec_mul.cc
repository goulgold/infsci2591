#include <iostream>
#include <stdlib.h>
#include <vector>
#include <array>

using std::cout;
using std::endl;
using std::vector;
using std::array;

int ret_mul(int a, int b);

int ret_mul(int a, int b) {
    //Implement algorithm here
    vector<int> a_num, b_num;
    while (a != 0) {
        a_num.push_back(a % 10);
        a = a / 10;
    }
    while (b != 0) {
        b_num.push_back(b % 10);
        b = b / 10;
    }
    int a_size = a_num.size();
    int b_size = b_num.size();
    if (a_size == 0 || b_size == 0) return 0;
    // new memory space
    int **p = new int*[2*a_size];
    for (int i = 0; i < 2*a_size; ++i) {
        p[i] = new int [2*b_size];
    }
    for (int i = 0; i < a_size; ++i) {
        for (int j = 0; j < b_size; ++j) {
            p[2*i][2*j] = (a_num[i] * b_num[j]) % 10;
            p[2*i+1][2*j+1] = (a_num[i] * b_num[j]) / 10;
        }
    }
    int* result = new int[a_size + b_size];
    int c = 0;
    for (int i = 0; i < (a_size + b_size); ++i) {
        int index = (a_size + b_size - 1 - i);
        result[index] += c;
        int j = (2*i<2*a_size?2*i:2*a_size-1);
        while (j >=0 && (2*i - j) <= 2*b_size-1) {
            result[index] += p[j][2*i-j];
            j--;
        }
        c = result[index] / 10;
        result[index] = result[index] % 10;
    }

    // free memory space after usage.
    for (int i = 0; i < a_size; ++i) {
         delete [] p[i];
    }
    delete [] p;
    int r_num = 0;
    for (int i = 0; i < a_size + b_size; ++i) {
        r_num = r_num * 10 + result[i];
    }
    return r_num;

}

int main (int argc, char *argv[]) {
    if (argc != 3) {
        cout << "./prog <num1> <num2>" << endl;
        return 0;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int result = ret_mul(a,b);
    cout << a << " * " << b << " = " << result << endl;
    return 0;
}
