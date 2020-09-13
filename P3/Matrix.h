class Matrix {
  public:
    Matrix(int n);
    ~Matrix();
    Matrix(const Matrix &copy);
    Matrix &operator=(const Matrix &rhs);
    Matrix operator+(const Matrix &other);
    Matrix operator-(const Matrix &other);
    Matrix operator*(const Matrix &other);
    void input();
    void print();

  private:
    int **m;
    int n;
};