#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const long long INF = 1e18;
/*
* ================================================
* 迪杰斯特拉算法实现， 运用堆优化，朴素算法实在是过不去oj........
* 
* 输入 n
* n行 r1, r2 , weigth
* 
* 实现起来稍微有些复杂，弄了我好久
* 本算法已经通过OJ验证 ， 链接：https://codeforces.com/problemset/problem/20/C
* ================================================
*/

vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, int start, int end) {
    int n = graph.size();
    vector<long long> dist(n, INF);
    vector<int> prev(n, -1);
    vector<bool> done(n, false);
    using P = pair<long long, int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (done[u]) continue;
        done[u] = true;
        if (u == end) break;

        for (auto& [v, w] : graph[u]) {
            long long nd = d + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                prev[v] = u;
                pq.push({ nd, v });
            }
        }
    }
    vector<int> path;
    if (dist[end] == INF) return path;
    for (int v = end; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    // 加速用的
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        --x; --y;
        graph[x].push_back({ y, w });
        graph[y].push_back({ x, w });
    }
    vector<int> res = dijkstra(graph, 0, n - 1);
    if (res.empty()) {
        cout << -1 << '\n';
    }
    else {
        for (size_t i = 0; i < res.size(); ++i) {
            if (i) cout << ' ';
            cout << res[i] + 1;
        }
        cout << '\n';
    }
    return 0;
}