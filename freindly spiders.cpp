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
#include <numeric>

using namespace std;

const int MAXN = 300005;

vector<int> adj[MAXN];
int dist[MAXN];
int parent[MAXN];

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void bfs(int start, int n) {
    queue<int> q;
    q.push(start);
    fill(dist, dist + n + 1, -1);
    dist[start] = 0;
    parent[start] = -1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                parent[u] = v;
                q.push(u);
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int s, t;
    cin >> s >> t;

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (gcd(a[i], a[j]) != 1) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    bfs(s, n);

    if (dist[t] == -1) {
        cout << -1 << endl;
    } else {
        vector<int> path;
        for (int v = t; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        cout << path.size() << endl;
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
