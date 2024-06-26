/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

vector<int> adj[MAXN];
bool guarded[MAXN];    

struct Guard {
    int position;
    int stamina;
};

void bfs(int start, int stamina, int n) {
    queue<pair<int, int>> q;
    vector<bool> visited(n + 1, false);
    q.push({start, 0});
    visited[start] = true;

    while (!q.empty()) {
        auto [v, dist] = q.front();
        q.pop();

        if (dist <= stamina) {
            guarded[v] = true;
            for (int u : adj[v]) {
                if (!visited[u]) {
                    visited[u] = true;
                    q.push({u, dist + 1});
                }
            }
        }
    }
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;

   
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<Guard> guards(K);
    for (int i = 0; i < K; ++i) {
        cin >> guards[i].position >> guards[i].stamina;
    }

    fill(guarded, guarded + N + 1, false);

    for (const auto& guard : guards) {
        bfs(guard.position, guard.stamina, N);
    }

    vector<int> guarded_vertices;
    for (int i = 1; i <= N; ++i) {
        if (guarded[i]) {
            guarded_vertices.push_back(i);
        }
    }

    sort(guarded_vertices.begin(), guarded_vertices.end());
    cout<<  guarded_vertices.size()<<endl;

    for (int v : guarded_vertices) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}

