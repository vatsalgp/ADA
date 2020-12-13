#include "Matrix.h"
#include <iostream>

using namespace std;

Matrix::Matrix(int n) {
    this->n = n;
    m = new int *[n];
    for (int i = 0; i < n; i++)
        m[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = 0;
}

Matrix ::~Matrix() {
    for (int i = 0; i < n; i++)
        delete[] m[i];
    delete[] m;
}
Matrix::Matrix(const Matrix &copy) {
    if (copy.m != nullptr) {
        n = copy.n;
        m = new int *[n];
        for (int i = 0; i < n; i++)
            m[i] = new int[n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                m[i][j] = copy.m[i][j];
    } else
        m = nullptr;
}

Matrix &Matrix::operator=(const Matrix &rhs) {
    if (this != &rhs) {
        if (m != nullptr) {
            for (int i = 0; i < n; i++)
                delete[] m[i];
            delete[] m;
        }
        if (rhs.m != nullptr) {
            n = rhs.n;
            m = new int *[n];
            for (int i = 0; i < n; i++)
                m[i] = new int[n];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    m[i][j] = rhs.m[i][j];
        } else
            m = nullptr;
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &other) {
    Matrix out(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out.m[i][j] = m[i][j] + other.m[i][j];
    return out;
}

Matrix Matrix::operator-(const Matrix &other) {
    Matrix out(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out.m[i][j] = m[i][j] - other.m[i][j];
    return out;
}

Matrix Matrix::operator*(const Matrix &other) {
    if (this->n == 1) {
        Matrix out(1);
        out.m[0][0] = m[0][0] * other.m[0][0];
        return out;
    }

    // Splitting into smaller matrices

    int n = this->n / 2;
    Matrix a(n), b(n), c(n), d(n), e(n), f(n), g(n), h(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a.m[i][j] = m[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            b.m[i][j] = m[i][j + n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c.m[i][j] = m[i + n][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            d.m[i][j] = m[i + n][j + n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            e.m[i][j] = other.m[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            f.m[i][j] = other.m[i][j + n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g.m[i][j] = other.m[i + n][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            h.m[i][j] = other.m[i + n][j + n];

    // Performing operations on smaller matrices

    Matrix p1 = a * (f - h);
    Matrix p2 = (a + b) * h;
    Matrix p3 = (c + d) * e;
    Matrix p4 = d * (g - e);
    Matrix p5 = (a + d) * (e + h);
    Matrix p6 = (b - d) * (g + h);
    Matrix p7 = (a - c) * (e + f);

    Matrix x = p5 + p4 + p6 - p2;
    Matrix y = p1 + p2;
    Matrix z = p3 + p4;
    Matrix w = (p1 + p5) - (p3 + p7);

    // Combining the smaller matrices

    Matrix out(this->n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out.m[i][j] = x.m[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out.m[i][j + n] = y.m[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out.m[i + n][j] = z.m[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out.m[i + n][j + n] = w.m[i][j];
    return out;
}

void Matrix::input() {
    cout << endl << "Enter values: " << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> m[i][j];
}

void Matrix::print() {
    cout << endl << "Matrix is" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}