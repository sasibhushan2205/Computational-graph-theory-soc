#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>

using namespace std;

class UnionFind {
public:
    UnionFind(int n) : parent(n), rank(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int p) {
        if (parent[p] != p) {
            parent[p] = find(parent[p]);
        }
        return parent[p];
    }

    bool union_sets(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP != rootQ) {
            if (rank[rootP] > rank[rootQ]) {
                parent[rootQ] = rootP;
            } else if (rank[rootP] < rank[rootQ]) {
                parent[rootP] = rootQ;
            } else {
                parent[rootQ] = rootP;
                rank[rootP]++;
            }
            return true;
        }
        return false;
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int kruskal(int n, vector<tuple<int, int, int>>& edges) {
    sort(edges.begin(), edges.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<2>(a) < get<2>(b);
    });

    UnionFind uf(n);
    int mst_cost = 0;
    int edges_used = 0;

    for (const auto& edge : edges) {
        int a, b, cost;
        tie(a, b, cost) = edge;
        if (uf.union_sets(a - 1, b - 1)) {  
            mst_cost += cost;
            edges_used++;
            if (edges_used == n - 1) {
                return mst_cost;
            }
        }
    }

    return -1;  
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i] = make_tuple(a, b, c);
    }

    int result = kruskal(n, edges);
    if (result == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
