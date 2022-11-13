#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n, m;
class Trie {
    vector<Trie*> childs;
    int is_end = 0;
public:
    Trie():childs(26) {

    }
    void insert(const string& word) {
        Trie* root = this;
        for(auto ch : word) {
            int pos = ch - 'a';
            if(root->childs[pos] == nullptr) {
                root->childs[pos] = new Trie();
            }
            root = root->childs[pos];
        }
        root->is_end++;
    }

    int find_prefix(const string& t) {
        Trie* root = this;
        int ans = 0;
        for(auto&& ch : t) {
            int pos = ch - 'a';
            if(root->childs[pos] == nullptr) {
                break;
            }
            root = root->childs[pos];
            if(root->is_end > 0) ans += root->is_end;
        }
        return ans;
    }
};

void solve() {
    Trie* root = new Trie();
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        string s; cin >> s;
        root->insert(s);
    }
    for(int i = 0; i < m; ++i) {
        string s; cin >> s;
        ans = root->find_prefix(s);
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    solve();
    return 0;
}