#include <iostream>
#include <unordered_map>
using namespace std;

int nums[200001];
void solve() {
  int n, c;
  cin >> n >> c;
  unordered_map<int, int> cnts;
  long long ans = 0;
  for(int i = 0; i < n; ++i) {
    cin >> nums[i];
    int target_a = nums[i] + c, target_b = nums[i] - c;
    if(cnts.count(target_a)) {
      ans += cnts[target_a];
    }
    if(cnts.count(target_b)) {
      ans += cnts[target_b];
    }
    cnts[nums[i]]++;
  }
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
  return 0;
}