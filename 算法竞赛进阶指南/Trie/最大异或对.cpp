#include <iostream>
using namespace std;

const int N = 100010, M = 3100010;
int a[N], son[M][2];
int idx;

void insert(int x) {
  int p = 0;
  for(int i = 30; i >= 0; --i) {
    int& next_node = son[p][(x >> i) & 1];
    if(!next_node) {
      next_node = ++idx;
    }
    p = next_node;
  }
}

int query(int x) {
  int res = 0; int p = 0;
  for(int i = 30; i >= 0; --i) {
    int s = (x >> i) & 1;
    if(son[p][!s]) {
      p = son[p][!s];
      res += (1 << i);
    } else {
      p = son[p][s];
    }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  for(int i = 0; i < n; ++i) {
    cin >> a[i];
    insert(a[i]);
  }
  int ans = 0;
  for(int i = 0; i < n; ++i) {
    ans = max(query(a[i]), ans);
  }
  cout << ans << endl;
  return 0;
}