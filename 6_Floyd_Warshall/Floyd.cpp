# include <iostream>

using namespace std;

int main () {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;
    int mat[n][n];
    cout << "Enter Values" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> mat[i][j];

    for (int k = 0; k < n; k++) 
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);

    cout << "Minimum Distances are: " << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}