#include <iostream>

using namespace std;

int *merge(int *a, int n1, int *b, int n2) {
    int *out = new int[n1 + n2];
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < n1 && j < n2)
        out[k++] = (a[i] < b[j]) ? a[i++] : b[j++];
    while (i < n1)
        out[k++] = a[i++];
    while (j < n2)
        out[k++] = b[j++];
    return out;
}

int *mergeSort(int *arr, int l, int h) {
    if (l == h) {
        int *out = new int[1];
        out[0] = arr[l];
        return out;
    }
    int m = (l + h) / 2;
    int *left = mergeSort(arr, l, m);
    int *right = mergeSort(arr, m + 1, h);
    int *sorted = merge(left, m + 1, right, h - m);
    delete[] left;
    delete[] right;
    return sorted;
}

int *mergeSort(int *arr, int n) {
    int *out = mergeSort(arr, 0, n - 1);
    return out;
}

int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;
    int *arr = new int[n];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    arr = mergeSort(arr, n);
    cout << "After sorting: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
