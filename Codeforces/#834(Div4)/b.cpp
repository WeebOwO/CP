#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
int t;
vector<int> nums(3);
void solve() {
  int len; cin >> len;
  string s; cin >> s;
  char max_ch = s[0];
  for(auto ch : s) {
    if(ch > max_ch) {
      max_ch = ch;
    }
  }
  cout << int(max_ch - 'a' + 1) << endl;
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