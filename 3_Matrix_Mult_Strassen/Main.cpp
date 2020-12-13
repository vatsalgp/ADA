#include "Matrix.h"
#include <iostream>
using namespace std;

// Works only for orders of powers of 2

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;
    Matrix a(n);
    a.input();
    Matrix b(n);
    b.input();
    Matrix c = a * b;
    c.print();
}
