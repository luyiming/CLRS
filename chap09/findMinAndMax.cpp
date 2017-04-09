#include <algorithm>
#include <iostream>
using namespace std;

bool findMinAndMax(int *A, int n, int &minimal, int &maximal) {
  if (n < 1) {
    return false;
  }
  if (n == 1) {
    minimal = maximal = A[1];
    return true;
  }
  for (int i = 0; i + 1 < n; i += 2) {
    if (A[i] > A[i + 1]) {
      swap(A[i], A[i + 1]);
    }
  }
  minimal = A[0], maximal = A[1];
  for (int i = 2; i < n; i += 2) {
    if (A[i] < minimal) {
      minimal = A[i];
    }
  }
  for (int i = 3; i < n; i += 2) {
    if (A[i] > maximal) {
      maximal = A[i];
    }
  }
  return true;
}

int main() {
  int A[] = {1, 2, 3, 4, 5, 6};
  int minimal, maximal;
  if (findMinAndMax(A, sizeof(A) / sizeof(int), minimal, maximal)) {
    cout << "maximal: " << maximal << endl << "minimal: " << minimal << endl;
  } else {
    cout << "error" << endl;
  }
}
