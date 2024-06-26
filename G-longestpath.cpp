/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

vector<int> adj[MAXN];
int dp[MAXN];      
bool visited[MAXN]; 

void topologicalSort(int v, stack<int> &Stack) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            topologicalSort(u,Stack);
        }
    }
    Stack.push(v);
}

int longestPath(int N) {
    stack<int> Stack;
    fill(visited, visited + N + 1, false);
    fill(dp, dp + N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            topologicalSort(i, Stack);
        }
    }

    while (!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();

        
        for (int u : adj[v]) {
            if (dp[u] < dp[v] + 1) {
                dp[u] = dp[v] + 1;
            }
        }
    }

    int maxLength = 0;
    for (int i = 1; i <= N; ++i) {
        if (dp[i] > maxLength) {
            maxLength = dp[i];
        }
    }

    return maxLength;
}

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
    }

    int result = longestPath(N);
    cout << result << endl;

    return 0;
}

