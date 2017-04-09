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
int selectRank(int *A, int left, int right, int k) {
  if (left > right) {
    return -1;
  }
  int mid = partition(A, left, right);
  int leftNnum = mid - left + 1;
  if (leftNnum == k) {
    return mid;
  } else if (leftNnum < k) {
    return selectRank(A, mid + 1, right, k - leftNnum);
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
  cout << "k: " << k << endl;
  if (left > right) {
    return -1;
  }
  int groupNum = (right - left) / 5 + 1;
  int *medianGoup = new int[groupNum];
  for (int i = 0; i < groupNum; i++) {
    int groupSize = 5 < right - left + 1 - 5 * i ? 5 : right - left + 1 - 5 * i;
    medianGoup[i] = findMedianOfFive(A + left + i * 5, groupSize);
  }

  cout << "median group: ";
  for (int i = 0; i < groupNum; i++) {
    cout << medianGoup[i] << " ";
  }
  cout << endl;

  cout << "after group: ";
  for (int i = left; i <= right; i++) {
    cout << A[i] << " ";
  }
  cout << endl;

  int pivot = selectRank(medianGoup, 0, groupNum - 1, (groupNum + 1) / 2);
  cout << "pivot: " << pivot << " " << medianGoup[pivot] << endl;
  int mid = partition(A, left, right, medianGoup[pivot]);

  cout << "mid: " << mid << " " << medianGoup[mid] << endl;

  cout << "after partition: ";
  for (int i = left; i <= right; i++) {
    cout << A[i] << " ";
  }
  cout << endl;

  delete[] medianGoup;

  int leftNnum = mid - left + 1;
  if (leftNnum == k) {
    return mid;
  } else if (leftNnum < k) {
    return selectRank_2(A, mid + 1, right, k - leftNnum);
  } else {
    return selectRank_2(A, left, mid - 1, k);
  }
}
/*****************************************************************************/

int main() {
  int A[] = {2, 5, 3, 6, 4, 1};
  for (int k = -1; k <= 7; k++) {
    int index = selectRank_2(A, 0, sizeof(A) / sizeof(int) - 1, k);
    if (index != -1) {
      printf("rank %d: %d\n", k, A[index]);
    } else {
      printf("rank %d not exists\n", k);
    }
  }
}
