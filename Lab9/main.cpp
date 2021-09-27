#include <iostream>
#include <vector>
#include <set>

using namespace std;

const long long INF = 1e13 + 7;

struct TEdge {
    int to, cost;
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, s, f;
    cin >> n >> m >> s >> f;
    s--;
    f--;

    int a, b, c;
    vector<vector<TEdge>> G(n);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c;
        a--;
        b--;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }

    long long dis = 0;
    vector<long long> d(n, INF);
    d[s] = 0;

    set<pair<long long, int>> st; // 1 -- dist, 2 -- num
    st.insert({0, s});

    while (!st.empty()) {

        pair<long long,int> p = *st.begin();
        long long dist = p.first;
        int current = p.second;
        if (current == f) {
            dis = dist;
            break;
        }
        st.erase(st.begin());
        
        for (TEdge to_cost: G[current]) {
            int to = to_cost.to;
            long long cost = to_cost.cost;
            if (d[to] > d[current] + cost) {
                st.erase({d[to], to});
                d[to] = d[current] + cost;
                st.insert({d[to], to});
            }
        }  
    }

    if (!st.empty()) {
        cout << dis << "\n";
    } else {
        cout << "No solution" << "\n";
    }

    return 0;
}