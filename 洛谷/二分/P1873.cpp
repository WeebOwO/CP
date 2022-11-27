#include <iostream>
#include <algorithm>
using namespace std;

int nums[1000001];
int n, m;
void solve() {
  int l = 1, r = 2e9;
  auto check = [&](int mid) {
    long long ret = 0;
    for(int i = 0; i < n; ++i) {
      if(nums[i] > mid) {
        ret += nums[i] - mid;
      }
    }
    return ret >= m;
  };
  while(l < r) {
    int mid = (l + r + 1) >> 1;
    if(check(mid)) {
        l = mid;
    } else {
        r = mid - 1;
    }
  }
  cout << l << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  for(int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  solve();
  return 0;
}