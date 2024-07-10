#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isTreeDistanceMatrix(const vector<vector<long long>>& dist, int n) {

    for (int i = 0; i < n; i++) {
        if (dist[i][i] != 0) {
            return false;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] != dist[j][i]) {
                return false;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (i != j && j != k && i != k) {
                    if (dist[i][j] + dist[j][k] < dist[i][k]) {
                        return false;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (i != j && j != k && i != k) {
                    if (dist[i][j] + dist[j][k] == dist[i][k] ||
                        dist[i][k] + dist[k][j] == dist[i][j] ||
                        dist[j][i] + dist[i][k] == dist[j][k]) {
                        continue;
                    } else {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

int main() {
    int n;
    cin >> n;

    vector<vector<long long>> dist(n, vector<long long>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    if (isTreeDistanceMatrix(dist, n)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
