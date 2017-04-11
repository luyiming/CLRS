#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

int findTwoSum(int *S, int n, int a) {
  int i = -1;
  int j = n - 1;
  int cnt = 0;
  while (i < j) {
    i++;
    while (i < j && S[i] + S[j] > a) {
      j--;
    }
    if (i >= j)
      break;
    if (S[i] + S[j] == a) {
      cnt++;
      // cout << "i: " << i << " j: " << j << endl;
    }
    if (j < n - 1) {
      j++;
    }
  }
  return cnt;
}

int main() {
  int n, sumN;
  cin >> n >> sumN;
  int *A = new int[n];
  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }

  sort(A, A + n);

  int result = 0;
  for (int i = n - 1; i >= 2; i--) {
    result += findTwoSum(A, i, sumN - A[i]);
  }
  cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
  cout << result;

  return 0;
}
