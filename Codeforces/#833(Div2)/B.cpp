#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
int t;
int n;
string s;
void solve() {
  cin >> n >> s;
  long long ans = 0;
  for(int i = 0; i < s.size(); ++i) {
    int distinct = 0, max_freq = 0;
    vector<int> freq(10);
    for (int j = i; j < s.size() && (++freq[s[j] - '0']) <= 10; ++j) {
      max_freq = max(freq[s[j] - '0'], max_freq);
      if (freq[s[j] - '0'] == 1) ++distinct;
      if (max_freq <= distinct) {
        ++ans;
      }
    }
  }
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while(t--) {
    solve();
  }
}