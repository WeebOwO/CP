#include <iostream>
#include <cmath>
using namespace std;
int t, n;
 
void solve() {
  long long ans = 0;
  if (n % 2 == 0) {
    long long sets = n / 2;
    ans = (1 + sets) * sets;
  } else {
    long long sets = n / 2;
    ans = (1 + sets) * sets + (n + 1) / 2;
  }
  cout << (int)sqrt(ans) << endl;
}
 
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    solve();
  }
  return 0;
}