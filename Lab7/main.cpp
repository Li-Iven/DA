#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int n, m;
    cin >> n >> m;
    vector<vector<long long>> A (n, vector<long long>(m)); // Исходный массив штрафов

    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> A[i][j];
        }
    }

    for(int i = n - 2; i > (-1); --i) {
        for (int j = 0; j < m; ++j) {
            if (j == 0) { 
                A[i][j] += min(A[i + 1][j], A[i + 1][j + 1]);
            }
            else if (j == m - 1) {
                A[i][j] += min(A[i + 1][j - 1], A[i + 1][j]);
            }
            else {
                A[i][j] += min({A[i + 1][j - 1], A[i + 1][j], A[i + 1][j + 1]});
            }
        }
    }

    long long minimum = A[0][0];
    int ind = 0;
    for(int i = 1; i < m; ++i) {
        if (A[0][i] <= minimum) {
            minimum = A[0][i];
            ind = i;
        }
    }

    cout << minimum << "\n";
    
    int i, j = ind;
    for(i = 0; i < n - 1; ++i) {
        cout << "(" << i + 1 << "," << j + 1 << ") ";
        if (j == 0) { 
            long long x = min(A[i + 1][j], A[i + 1][j + 1]);
            if (x == A[i + 1][j + 1]) {
                j++;
            }
        }
        else if (j == m - 1) {
            long long x = min(A[i + 1][j - 1], A[i + 1][j]);
            if (x == A[i + 1][j - 1]) {
                j--;
            }
        }
        else { 
            long long x = min({A[i + 1][j - 1], A[i + 1][j], A[i + 1][j + 1]});
            if (x == A[i + 1][j - 1]) {
                j--;
            }
            else if (x == A[i + 1][j + 1]) {
                j++;
            }
        }  
    }
    cout << "(" << i + 1 << "," << j + 1 << ")\n";

    return 0;
}