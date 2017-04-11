#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
int totalSize;
int cnt = 0;
const int NodeSize = 1000;

struct Node {
  double x, y;
  Node(int x, int y) : x(x), y(y) {}
  Node() : x(0), y(0) {}
  Node(const Node &rhs) {
    x = rhs.x;
    y = rhs.y;
  }
  void flip() { swap(x, y); }
};
bool operator<(const Node &lhs, const Node &rhs) { return lhs.x < rhs.x; }

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
/************** Expect complexity O(n) Selection algorithm **************/

double nodeDistance(Node n1, Node n2) {
  return sqrt((n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y));
}

double findMinDistance(Node *Nodes, int low, int high) {
  /*
if (CNodes != Nodes) {
  cout << CNodes << endl;
  exit(1);
}
if (low < 0 || low > high) {
  cout << "low: " << low << " high: " << high << endl;
  exit(1);
}
if (high >= NodeSize) {
  cout << "low: " << low << " high: " << high << endl;
  exit(1);
}
*/

  int nodesSize = high - low + 1;
  if (nodesSize <= 1) {
    return std::numeric_limits<double>::max();
  }
  if (nodesSize == 2) {
    // assert(low >= 0 && high < NodeSize);
    // assert(low <= high);
    // assert(high == low + 1);
    return nodeDistance(Nodes[low], Nodes[high]);
  }

  // int *xArray = new int[nodesSize];
  // for (int i = 0; i < nodesSize; i++) {
  //    xArray[i] = Nodes.at(i).x;
  //}
  // int xMedian = xArray[selectRank(xArray, 0, nodesSize - 1, nodesSize / 2)];

  sort(Nodes + low, Nodes + high + 1);
  // qsort(Nodes + low, high - low + 1, sizeof(Node), cmp);

  //  for (int i = low; i <= high; i++) {
  //    cout << Nodes[i].x << " ";
  //  }
  //  cout << endl;

  int xMedianIndex = (low + high) / 2;
  int xMedian = Nodes[xMedianIndex].x;

  // cout << "xmedian: " << xMedian << endl;
  if (Nodes[low].x == Nodes[high].x) {
    if (Nodes[low].y == Nodes[high].y) {
      return 0.0;
    }
    // flip
    for (int i = low; i <= high; i++) {
      Nodes[i].flip();
    }
    double ret = findMinDistance(Nodes, low, high);
    for (int i = low; i <= high; i++) {
      Nodes[i].flip();
    }
    return ret;
  }

  // ensure both parts have nodes
  if (xMedianIndex + 1 > high) {
    xMedianIndex--;
  }
  assert(xMedianIndex >= low && xMedianIndex < high);

  //  cout << "median: " << Nodes[xMedianIndex].x << endl;

  double d1 = findMinDistance(Nodes, low, xMedianIndex);
  double d2 = findMinDistance(Nodes, xMedianIndex + 1, high);

  double d = d1 < d2 ? d1 : d2;
  //  cout << "d: " << d << endl;

  int leftCandidatesIndex = xMedianIndex,
      rightCandidatesIndex = xMedianIndex + 1;
  while (leftCandidatesIndex >= low) {
    if ((double)Nodes[leftCandidatesIndex].x >= (double)xMedian - d) {
      leftCandidatesIndex--;
    } else {
      break;
    }
  }
  leftCandidatesIndex--;
  if (leftCandidatesIndex < low) {
    leftCandidatesIndex = low;
  }
  while (rightCandidatesIndex <= high) {
    if ((double)Nodes[rightCandidatesIndex].x <= (double)xMedian + d) {
      rightCandidatesIndex++;
    } else {
      break;
    }
  }
  rightCandidatesIndex++;
  if (rightCandidatesIndex > high) {
    rightCandidatesIndex = high;
  }
  //  cout << "xMedianIndex: " << xMedianIndex << endl;
  //  cout << "leftCandidatesIndex: " << leftCandidatesIndex << endl;
  //  cout << "rightCandidatesIndex: " << rightCandidatesIndex << endl;

/*
  for (int i = low; i < leftCandidatesIndex; i++) {
    if ((double)Nodes[i].x >= (double)xMedian - d) {
      cout << "1.d: " << d << endl;
      cout << "xMedian: " << xMedian << endl;
      cout << "xMedianIndex: " << xMedianIndex << endl;
      cout << "low: " << low << endl;
      cout << "high: " << high << endl;
      cout << "leftCandidatesIndex: " << leftCandidatesIndex << endl;
      cout << "rightCandidatesIndex: " << rightCandidatesIndex << endl;
      for (int j = low; j <= high; j++) {
        cout << Nodes[j].x << " ";
      }
      cout << endl;
      for (int j = low; j <= high; j++) {
        cout << Nodes[j].y << " ";
      }
      cout << endl;
      assert(0);
    }
  }
  for (int i = rightCandidatesIndex + 1; i <= high; i++) {
    if ((double)Nodes[i].x <= (double)xMedian + d) {
      cout << "2.d: " << d << endl;
      cout << "xMedian: " << xMedian << endl;
      cout << "xMedianIndex: " << xMedianIndex << endl;
      cout << "low: " << low << endl;
      cout << "high: " << high << endl;
      cout << "leftCandidatesIndex: " << leftCandidatesIndex << endl;
      cout << "rightCandidatesIndex: " << rightCandidatesIndex << endl;
      for (int j = low; j <= high; j++) {
        cout << Nodes[j].x << " ";
      }
      cout << endl;
      for (int j = low; j <= high; j++) {
        cout << Nodes[j].y << " ";
      }
      cout << endl;
      assert(0);
    }
  }
*/
  for (int i = leftCandidatesIndex; i <= xMedianIndex; i++) {
    for (int j = xMedianIndex + 1; j <= rightCandidatesIndex; j++) {
      double currentD = nodeDistance(Nodes[i], Nodes[j]);
      if (currentD < d) {
        d = currentD;
      }
    }
  }

  // delete[] xArray;
  return d;
}

double bruteForceMinDistance(Node *Nodes, int n) {
  double minDistance = std::numeric_limits<double>::max();
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      double currentD = nodeDistance(Nodes[i], Nodes[j]);
      if (currentD < minDistance) {
        minDistance = currentD;
      }
    }
  }
  return minDistance;
}

int main() {

    int x, y;
    cin >> totalSize;
    Node *Nodes = new Node[totalSize];
    for (int i = 0; i < totalSize; i++) {
      scanf("%d,%d", &x, &y);
      Nodes[i] = Node(x, y);
    }

    //  for (int i = 0; i < n; i++) {
    //    cout << Nodes[i].x << " " << Nodes[i].y << endl;
    //  }
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    printf("%.6f", findMinDistance(Nodes, 0, totalSize - 1));

    delete[] Nodes;
    // 3 657994585,941883880 243678075,1353968635 730268714,177645073
    // should be 25059.093140, you solve 30714.540872
    // should be 2148.444321, you solve 9909.975277
// 10 1653377373,1131176229 1914544919,859484421 756898537,608413784 1973594324,1734575198 2038664370,149798315 184803526,1129566413 1424268980,412776091 749241873,1911759956 42999170,137806862 135497281,982906996

/*
  const int TESTNUM = 100;
  const double EPSILON = 1.0e-5;
  Node *testNodes = new Node[NodeSize];
  Node *testNodes2 = new Node[NodeSize];
  for (int i = 0; i < TESTNUM; i++) {
    for (int j = 0; j < NodeSize; j++) {
      testNodes[j] = Node(rand(), rand());
      testNodes2[j] = testNodes[j];
    }
    cnt++;
    double d1 = bruteForceMinDistance(testNodes, NodeSize);
    double d2 = findMinDistance(testNodes2, 0, NodeSize - 1);
    if (fabs(d1 - d2) > EPSILON) {
      printf("should be %.6f, you solve %.6f\n", d1, d2);
      for (int k = 0; k < NodeSize; k++) {
        printf("%d,%d ", testNodes[k].x, testNodes[k].y);
      }
      printf("\n");
      for (int k = 0; k < NodeSize; k++) {
        printf("%d,%d ", testNodes2[k].x, testNodes2[k].y);
      }
      printf("\n");
      printf("\n");
      return 0;
    }
  }

*/
  return 0;
}
