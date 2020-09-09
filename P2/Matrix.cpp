#include <iostream>

using namespace std;

int n;

int **init() {
    int **mat = new int *[n];
    for (int i = 0; i < n; i++)
        mat[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = 0;
    return mat;
}

int **input() {
    cout << endl;
    int **mat = init();
    cout << "Enter values: " << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> mat[i][j];
    return mat;
}

void print(int **mat) {
    cout << endl << "Matrix is" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

int **mult(int **a, int **b) {
    int **c = init();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
    return c;
}

int main() {
    cout << "Enter n: ";
    cin >> n;
    int **a = input();
    int **b = input();
    int **c = mult(a, b);
    print(c);
}