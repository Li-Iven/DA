#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void DFS(int v, const vector<vector<int>>& G, vector<bool>& used, vector<int>& res) {
    
    used[v] = 1;
    for (int to: G[v]) {
        if (!used[to]) {
            DFS(to, G, used, res);
        }
    }
    res.push_back(v);
}

bool Circle(int v, const vector<vector<int>>& G, vector<string>& color) {
    color[v] = "grey";             
    for (int to: G[v]) {
        if (color[to] == "white")
            Circle(to, G, color);
        if (color[to] == "grey")
            return false;
    }  
    color[v] = "black";  
    return true;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int a, b;
    vector<vector<int>> G(n);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
    }

    
    vector<string> color(n, "white");
    for (int i = 0; i < n; ++i) {
        if(!Circle(i, G, color)) {
            cout << "-1\n";
            return 0;
        }
    }

    vector<bool> used(n);
    vector<int> res;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            DFS(i, G, used, res);
        }
    }

    reverse (res.begin(), res.end());

    for (size_t i = 0; i < res.size() - 1; ++i) {
        cout << res[i] + 1 << " " << res[i + 1] + 1 << "\n";       
    }

    return 0;
}