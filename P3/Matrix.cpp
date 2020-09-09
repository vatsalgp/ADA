#include <iostream>

using namespace std;

int **init(int n) {
    int **out = new int *[n];
    for (int i = 0; i < n; i++)
        out[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[i][j] = 0;
    return out;
}

int **input(int n) {
    cout << endl;
    int **out = init(n);
    cout << "Enter values: " << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> out[i][j];
    return out;
}

void print(int **m, int n) {
    cout << endl << "Matrix is" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

int **add(int **x, int **y, int n) {
    int **out = init(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[i][j] = x[i][j] + y[i][j];
    return out;
}

int **sub(int **x, int **y, int n) {
    int **out = init(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[i][j] = x[i][j] - y[i][j];
    return out;
}

int **combine(int **a, int **b, int **c, int **d, int n) {
    int **out = init(n * 2);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[i][j] = a[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[i][j + n] = b[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[i + n][j] = c[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[i + n][j + n] = d[i][j];
    return out;
}

int ***split(int **x, int n) {
    n /= 2;
    int ***out = new int **[4];
    out[0] = init(n);
    out[1] = init(n);
    out[2] = init(n);
    out[3] = init(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[0][i][j] = x[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[1][i][j] = x[i][j + n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[2][i][j] = x[i + n][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[3][i][j] = x[i + n][j + n];
    return out;
}

int **mult(int **x, int **y, int n) {
    // Todo
    // Free the memory
    if (n == 1) {
        int **out = init(n);
        out[0][0] = x[0][0] * y[0][0];
        return out;
    }
    int ***s1 = split(x, n);
    int ***s2 = split(y, n);
    int **a = s1[0], **b = s1[1], **c = s1[2], **d = s1[3];
    int **e = s2[0], **f = s2[1], **g = s2[2], **h = s2[3];
    n /= 2;
    int **p1 = mult(a, sub(f, h, n), n);
    int **p2 = mult(add(a, b, n), h, n);
    int **p3 = mult(add(c, d, n), e, n);
    int **p4 = mult(d, sub(g, e, n), n);
    int **p5 = mult(add(a, d, n), add(e, h, n), n);
    int **p6 = mult(sub(b, d, n), add(g, h, n), n);
    int **p7 = mult(sub(a, c, n), add(e, f, n), n);

    int **i = sub(add(add(p5, p4, n), p6, n), p2, n);
    int **j = add(p1, p2, n);
    int **k = add(p3, p4, n);
    int **l = sub(add(p1, p5, n), add(p3, p7, n), n);

    return combine(i, j, k, l, n);
}

int main() {
    // Works only for orders of powers of 2
    int n;
    cout << "Enter n: ";
    cin >> n;
    int **a = input(n);
    int **b = input(n);
    int **c = mult(a, b, n);
    print(c, n);
}
