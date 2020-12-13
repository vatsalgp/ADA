#include <iostream>

using namespace std;

int main() {
    // Get Input
    int n;
    cout << "Enter n: ";
    cin >> n;
    int arr[n];
    cout << "Enter n dimensions: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    // Initialize DP
    int dp[n][n] = {0};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (j > i)
                dp[i][j] = INT32_MAX;
    // Calculate
    for (int len = 2; len < n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                int nc = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], nc);
            }
        }
    }
    // Print
    cout << "The min cost is: " << dp[1][n - 1] << endl;
}