#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

/************** Expect complexity O(n) Selection algorithm **************/
int partition(int *A, int p, int r) {
  // use A[r] to partition A[p..r]
  int i = p;
  for (int j = p; j < r; j++) {
    if (A[j] < A[r]) {
      swap(A[j], A[i]);
      i++;
    }
  }
  swap(A[r], A[i]);
  return i;
}

// k starts from 1, Expect O(n)
// return index
int selectRank(int *A, int left, int right, int k) {
  if (left > right) {
    return -1;
  }
  int mid = partition(A, left, right);
  int leftNum = mid - left + 1;
  if (leftNum == k) {
    return mid;
  } else if (leftNum < k) {
    return selectRank(A, mid + 1, right, k - leftNum);
  } else {
    return selectRank(A, left, mid - 1, k);
  }
}
/*****************************************************************************/

/************** Worst case complexity O(n) Selection algorithm **************/
int partition(int *A, int p, int r, int pivot) {
  // use pivot to partition A[p..r]
  for (int i = p; i <= r; i++) {
    if (A[i] == pivot) {
      swap(A[i], A[r]);
      break;
    }
  }
  return partition(A, p, r);
}

// 1 <= n <= 5
int findMedianOfFive(int *A, int n) {
  assert(0 <= n && n <= 5);
  sort(A, A + n);
  return A[n / 2];
}

int selectRank_2(int *A, int left, int right, int k) {
  if (left > right) {
    return -1;
  }
  int groupNum = (right - left) / 5 + 1;
  int *medianGoup = new int[groupNum];
  for (int i = 0; i < groupNum; i++) {
    int groupSize = 5 < right - left + 1 - 5 * i ? 5 : right - left + 1 - 5 * i;
    medianGoup[i] = findMedianOfFive(A + left + i * 5, groupSize);
  }

  int pivot = selectRank(medianGoup, 0, groupNum - 1, (groupNum + 1) / 2);
  int mid = partition(A, left, right, medianGoup[pivot]);

  delete[] medianGoup;

  int leftNum = mid - left + 1;
  if (leftNum == k) {
    return mid;
  } else if (leftNum < k) {
    return selectRank_2(A, mid + 1, right, k - leftNum);
  } else {
    return selectRank_2(A, left, mid - 1, k);
  }
}
/*****************************************************************************/

#define TEST_NUM 10000
#define ARRSIZE 100
int main() {
  int a[ARRSIZE];
  int b[ARRSIZE];
  int c[ARRSIZE];
  for (int i = 0; i < TEST_NUM; i++) {
    int arrSize = (rand() % ARRSIZE) + 1;
    for (int j = 0; j < arrSize; j++) {
      a[j] = b[j] = c[j] = rand();
    }
    sort(b, b + arrSize);
    for (int j = 0; j < arrSize; j++) {
      int index = selectRank_2(a, 0, arrSize - 1, j + 1);
      if (b[j] != a[index]) {
        cout << "array size: " << arrSize << endl;
        cout << "array: ";
        for (int k = 0; k < arrSize; k++) {
          cout << c[k] << " ";
        }
        cout << endl;

        cout << "select rank: " << j + 1 << endl;

        cout << "expect result: " << b[j] << endl;

        cout << "my result: " << index << " -> " << a[index] << endl;
        return -1;
      }
    }
  }
  cout << "test succeed" << endl;
}
