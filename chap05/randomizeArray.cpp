#include <algorithm>
#include <iostream>

using namespace std;

void randomizeInPlace(int *A, int n) {
  srand(time(NULL));
  for (int i = 0; i < n - 1; i++) {
    // swap A[i] with A[random(i, n)]
    int k = (rand() % (n - i - 1)) + i + 1;
    swap(A[i], A[k]);
  }
}

int main() {
  int arr[] = {1, 2, 3, 4, 5, 6};
  randomizeInPlace(arr, sizeof(arr) / sizeof(int));
  for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
  return 0;
}
