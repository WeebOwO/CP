#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
 
int t;
int nums[200001];
void solve() {
  int n; cin >> n;
  for(int i = 0; i < n; ++i) cin >> nums[i];
  int cnt = 0;
  auto cal = [&]() {
    ++cnt;
    return cnt > 1 ? true : false;
  };
 
  for(int i = 0; i < n; ++i) {
    int j = i;
    while(j + 1 < n && nums[j + 1] == nums[i]) {
      ++j;
    }
    if(i != 0 && j != n - 1) {
      if(nums[i - 1] > nums[i] && nums[j + 1] > nums[j]) {
        if(cal()) {
          cout << "NO\n";
          return;
        }
      }
    }
    else if(i == 0) {
      if(j == n - 1) {
        if(cal()) {
          cout << "NO\n";
          return;
        }
      } else {
        if(nums[j + 1] > nums[j]) {
          if(cal()) {
            cout << "NO\n";
            return;
          }
        }
      }
    }
    else {
      if(nums[i - 1] > nums[i]) {
        if(cal()) {
          cout << "NO\n";
          return;
        }
      }
    }
    i = j;
  }
  cout << "YES\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}