#include <iostream>
#include <climits>

using namespace std;

#define MAXN 100

void printMatrix(int s[MAXN][MAXN], int i, int j) {
  if (i == j) {
    cout << " A" << i << " ";
    return;
  }
  cout << "(";
  printMatrix(s, i, s[i][j]);
  printMatrix(s, s[i][j] + 1, j);
  cout << ")";
}

void matrixChainOrder(int *p, int n) {
  unsigned int m[MAXN][MAXN];
  int s[MAXN][MAXN];
  for (int i = 1; i <= n; i++) {
    m[i][i] = 0;
  }
  for (int l = 2; l <= n; l++) {
    for (int i = 1; i <= n - l + 1; i++) {
      int j = i + l - 1;
      m[i][j] = UINT_MAX;
      // split A[i..k]A[k+1..j]
      for (int k = i; k < j; k++) {
        int tmp = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
        if (tmp < m[i][j]) {
          m[i][j] = tmp;
          s[i][j] = k;
        }
      }
    }
  }
  cout << m[1][n] << endl;
  printMatrix(s, 1, n);
}

int main() {
  int p[] = {30, 35, 15, 5, 10, 20, 25};
  matrixChainOrder(p, 6);
  return 0;
}
