/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <numeric>

using namespace std;

const int MAXN = 100005;
const int INF = INT_MAX;

vector<int> adj[MAXN];        
vector<int> goods[MAXN];      
int dist[MAXN][101];          

void bfs(int good_type, int n) {
    queue<int> q;
    vector<bool> visited(n + 1, false);

    for (int town : goods[good_type]) {
        q.push(town);
        dist[town][good_type] = 0;
        visited[town] = true;
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                dist[u][good_type] = dist[v][good_type] + 1;
                q.push(u);
            }
        }
    }
}

int main() {
    int n, m, k, s;
    cin >> n >> m >> k >> s;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        goods[a[i]].push_back(i);
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

   
    for (int i = 1; i <= n; ++i) {
        fill(dist[i], dist[i] + k + 1, INF);
    }

    
    for (int good_type = 1; good_type <= k; ++good_type) {
        bfs(good_type, n);
    }

    vector<int> result(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        vector<int> costs;
        for (int good_type = 1; good_type <= k; ++good_type) {
            costs.push_back(dist[i][good_type]);
        }
        sort(costs.begin(), costs.end());
        result[i] = accumulate(costs.begin(), costs.begin() + s, 0);
    }

    for (int i = 1; i <= n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}

