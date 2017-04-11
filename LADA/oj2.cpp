#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Node {
  double x, y;
  Node(int x, int y) : x(x), y(y) {}
  Node() : x(0), y(0) {}
  void flip() { swap(x, y); }
};
bool operator<(const Node &lhs, const Node &rhs) { return lhs.x < rhs.x; }
bool operator==(const Node &lhs, const Node &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

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

double nodeDistance(Node &n1, Node &n2) {
  return sqrt((n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y));
}

double findMinDistance(vector<Node> &Nodes) {
  int nodesSize = Nodes.size();
  if (nodesSize <= 1) {
    return std::numeric_limits<double>::max();
  }
  if (nodesSize == 2) {
    return nodeDistance(Nodes.at(0), Nodes.at(1));
  }

  // int *xArray = new int[nodesSize];
  // for (int i = 0; i < nodesSize; i++) {
  //    xArray[i] = Nodes.at(i).x;
  //}
  // int xMedian = xArray[selectRank(xArray, 0, nodesSize - 1, nodesSize / 2)];
  sort(Nodes.begin(), Nodes.end());
  int xMedianIndex = nodesSize / 2;
  int xMedian = Nodes.at(xMedianIndex).x;

  // cout << "xmedian: " << xMedian << endl;
  vector<Node> leftNodes, rightNodes;
  for (int i = 0; i < nodesSize; i++) {
    if (Nodes.at(i).x < xMedian) {
      leftNodes.push_back(Nodes.at(i));
    } else {
      rightNodes.push_back(Nodes.at(i));
    }
  }

  // ensure both parts have nodes
  if (leftNodes.empty()) {
    if (rightNodes.at(0).y == rightNodes.at(1).y) {
      return 0.0;
    }
    rightNodes.clear();
    while (xMedianIndex < nodesSize && Nodes[xMedianIndex].x == xMedian) {
      xMedianIndex++;
    }
    if (xMedianIndex >= nodesSize) {
      // flip
      for (int i = 0; i < nodesSize; i++) {
        Nodes.at(i).flip();
      }
      return findMinDistance(Nodes);
    } else {
      xMedian = Nodes.at(xMedianIndex).x;
      for (int i = 0; i < nodesSize; i++) {
        if (Nodes.at(i).x < xMedian) {
          leftNodes.push_back(Nodes.at(i));
        } else {
          rightNodes.push_back(Nodes.at(i));
        }
      }
    }
  }

  double d1 = findMinDistance(leftNodes);
  double d2 = findMinDistance(rightNodes);

  double d = min(d1, d2);

  vector<Node> leftCandidateNodes, rightCandidateNodes;
  for (int i = 0; i < leftNodes.size(); i++) {
    if ((double)leftNodes.at(i).x >= (double)xMedian - d) {
      leftCandidateNodes.push_back(leftNodes.at(i));
    }
  }
  for (int i = 0; i < rightNodes.size(); i++) {
    if ((double)rightNodes.at(i).x < (double)xMedian + d) {
      rightCandidateNodes.push_back(rightNodes.at(i));
    }
  }

  for (int i = 0; i < leftCandidateNodes.size(); i++) {
    for (int j = 0; j < rightCandidateNodes.size(); j++) {
      double currentD =
          nodeDistance(leftCandidateNodes.at(i), rightCandidateNodes.at(j));
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
int cnt = 0;
int main() {

  const int TESTNUM = 76636025;
  const double EPSILON = 1.0e-5;
  const int NodeSize = 3;
  Node *testNodes = new Node[NodeSize];
  for (int i = 0; i < TESTNUM; i++) {
    vector<Node> testNodes2;
    cnt++;
    for (int j = 0; j < NodeSize; j++) {
      testNodes[j] = Node(rand() % 10, rand() % 10);
      testNodes2.push_back(testNodes[j]);
    }
    double d1 = bruteForceMinDistance(testNodes, NodeSize);
    double d2 = findMinDistance(testNodes2);
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
    }
  }
  return 0;

  int n, x, y;
  vector<Node> Nodes;
  cin >> n;
  for (int i = 0; i < n; i++) {
    scanf("%d,%d", &x, &y);
    Nodes.push_back(Node(x, y));
  }
  //  for (int i = 0; i < n; i++) {
  //    cout << Nodes[i].x << " " << Nodes[i].y << endl;
  //  }
  cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
  printf("%.6f", findMinDistance(Nodes));
  return 0;
}
