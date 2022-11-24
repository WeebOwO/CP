#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int t;
vector<int> nums(3);
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while(t--) {
    for(int i = 0; i <= 2; ++i) {
      cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    cout << nums[1] << endl;
  }
  return 0;
}