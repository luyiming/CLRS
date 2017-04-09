#include <cstdio>
#include <iostream>

using namespace std;

struct Result {
  int l, r, sum;
  Result(int l, int r, int sum) : l(l), r(r), sum(sum) {}
};

Result findMaxCrossingSubarray(int *A, int low, int mid, int high) {
  int leftSum = A[mid];
  int maxLeft = mid;
  int sum = A[mid];
  for (int i = mid - 1; i >= low; i--) {
    sum += A[i];
    if (leftSum < sum) {
      leftSum = sum;
      maxLeft = i;
    }
  }
  int rightSum = A[mid + 1];
  int maxRight = mid + 1;
  sum = A[mid + 1];
  for (int i = mid + 2; i <= high; i++) {
    sum += A[i];
    if (rightSum < sum) {
      rightSum = sum;
      maxRight = i;
    }
  }
  return Result(maxLeft, maxRight, leftSum + rightSum);
}

Result findMaximumSubarray(int *A, int low, int high) {
  if (low == high) {
    return Result(low, high, A[low]);
  }
  int mid = (low + high) / 2;
  Result lResult = findMaximumSubarray(A, low, mid);
  Result rResult = findMaximumSubarray(A, mid + 1, high);
  Result cResult = findMaxCrossingSubarray(A, low, mid, high);
  if (lResult.sum > rResult.sum && lResult.sum > cResult.sum) {
    return lResult;
  } else if (rResult.sum > lResult.sum && rResult.sum > cResult.sum) {
    return rResult;
  } else {
    return cResult;
  }
}

Result linear_findMaximumSubarray(int *A, int low, int high) {
  int maxLeft = low, maxRight = low;
  int maxSum = A[low];
  int *f = new int[high];
  f[low] = A[low];
  for (int i = low + 1; i <= high; i++) {
    if (f[i - 1] + A[i] > A[i]) {
      f[i] = f[i - 1] + A[i];
      if (f[i] > maxSum) {
          maxSum = f[i];
          maxRight = i;
      }
    } else {
      f[i] = A[i];
      if (f[i] > maxSum) {
          maxSum = f[i];
          maxLeft = maxRight = i;
      }
    }
  }
  return Result(maxLeft, maxRight, maxSum);
}

int main() {
  int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
  printf("array: ");
  for (int i = 0; i < sizeof(a) / sizeof(int); i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
  Result res = linear_findMaximumSubarray(a, 0, sizeof(a) / sizeof(int) - 1);
  printf("maximum subarray: A[%d] -> A[%d] = %d\n", res.l, res.r, res.sum);
  for (int i = res.l; i <= res.r; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");

  int b[] = {13, -3};
  printf("array: ");
  for (int i = 0; i < sizeof(b) / sizeof(int); i++) {
    printf("%d ", b[i]);
  }
  printf("\n");
  res = linear_findMaximumSubarray(b, 0, sizeof(b) / sizeof(int) - 1);
  printf("maximum subarray: A[%d] -> A[%d] = %d\n", res.l, res.r, res.sum);
  for (int i = res.l; i <= res.r; i++) {
    printf("%d ", b[i]);
  }
  printf("\n");
}
