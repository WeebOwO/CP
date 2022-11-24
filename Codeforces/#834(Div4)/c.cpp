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
  int max_element = nums[0], second_max = nums[1];
  if(max_element < second_max) {
    swap(max_element, second_max);
  }
  for(int i = 2; i < n; ++i) {
    if(nums[i] > max_element) {
      second_max = max_element;
      max_element = nums[i];
    } else if(nums[i] > second_max) {
      second_max = nums[i];
    }
  }
  for(int i = 0; i < n; ++i) {
    if(nums[i] != max_element) {
      cout << nums[i] - max_element <<  " ";
    } else {
      cout << nums[i] - second_max << " ";
    }
  }
  cout << endl;
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