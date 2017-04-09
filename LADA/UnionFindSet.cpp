#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

class UnionFindSet {
private:
  int *data = NULL;
  int setSize = 0;

public:
  UnionFindSet() { data = NULL; }
  UnionFindSet(int n) {
    data = new int[n];
    setSize = n;
    memset(data, -1, setSize * sizeof(int));
  }
  int Find(int k) {
    int p = k;
    while (data[p] >= 0) {
      p = data[p];
    }
    int q;
    while (data[k] >= 0) {
      q = k;
      k = data[k];
      data[q] = p;
    }
    return p;
  }
  void Union(int k1, int k2) {
    int p1 = Find(k1);
    int p2 = Find(k2);
    if (p1 == p2) {
      return;
    }
    if (data[p1] <= data[p2]) {
      data[p1] += data[p2];
      data[p2] = p1;
    } else {
      data[p2] += data[p1];
      data[p1] = p2;
    }
  }
  bool inSameSet(int k1, int k2) { return Find(k1) == Find(k2); }
  int maxHeight() {
    int maxHeight = 1;
    int currentHeight = 0;
    for (int i = 0; i < setSize; i++) {
      currentHeight = 1;
      int p = i;
      while (data[p] >= 0) {
        p = data[p];
        currentHeight++;
      }
      if (currentHeight > maxHeight) {
        maxHeight = currentHeight;
      }
    }
    return maxHeight;
  }
};

int main() {
  UnionFindSet set(10);
  assert(set.maxHeight() == 1);

  assert(set.inSameSet(0, 1) == false);
  set.Union(0, 1);
  assert(set.inSameSet(0, 1) == true);
  assert(set.maxHeight() == 2);

  assert(set.inSameSet(0, 2) == false);
  set.Union(0, 2);
  assert(set.inSameSet(0, 2) == true);
  assert(set.maxHeight() == 2);

  assert(set.inSameSet(0, 3) == false);
  set.Union(0, 3);
  assert(set.inSameSet(0, 3) == true);
  assert(set.maxHeight() == 2);

  assert(set.inSameSet(2, 3) == true);
  set.Union(2, 3);
  assert(set.inSameSet(2, 3) == true);
  assert(set.maxHeight() == 2);

  assert(set.inSameSet(4, 5) == false);
  set.Union(4, 5);
  assert(set.inSameSet(4, 5) == true);
  assert(set.maxHeight() == 2);

  set.Union(0, 4);
  assert(set.maxHeight() == 3);

  set.Find(5);
  assert(set.maxHeight() == 2);

  cout << "test succeed" << endl;
  return 0;
}
