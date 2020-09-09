#include <iostream>

using namespace std;

int **init(int n) {
    int **mat = new int *[n];
    for (int i = 0; i < n; i++)
        mat[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = 0;
    return mat;
}

int **input(int n) {
    cout << endl;
    int **mat = init(n);
    cout << "Enter values: " << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> mat[i][j];
    return mat;
}

void print(int **mat, int n) {
    cout << endl << "Matrix is" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

int **add(int **x, int **y, int n) {
    int **c = init(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = x[i][j] + y[i][j];
    return c;
}

int **sub(int **x, int **y, int n) {
    int **c = init(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = x[i][j] - y[i][j];
    return c;
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
    int **a = init(n);
    int **b = init(n);
    int **c = init(n);
    int **d = init(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = x[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            b[i][j] = x[i][j + n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = x[i + n][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            d[i][j] = x[i + n][j + n];
    int ***out = new int **[4];
    out[0] = a;
    out[1] = b;
    out[2] = c;
    out[3] = d;
    return out;
}

int **mult(int **x, int **y, int n) {
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

    int **out = combine(i, j, k, l, n);

    free(s1);
    free(s2);
    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);
    free(p6);
    free(p7);
    free(i);
    free(j);
    free(k);
    free(l);

    return out;
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
