#include <iostream>

using namespace std;

int LCS(string s1, string s2) {
    int n1 = s1.size();
    int n2 = s2.size();
    int dp[n1 + 1][n2 + 1];

    for (int i = 0; i <= n1; i++)
        for (int j = 0; j <= n2; j++)
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (s1[i - 1] == s2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);

    return dp[n1][n2];
}

int main() {
    string s1, s2;

    cout << "S1: ";
    getline(cin, s1);

    cout << "S2: ";
    getline(cin, s2);

    cout << "LCS: " << LCS(s1, s2) << endl;
}