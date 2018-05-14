#include <bits/stdc++.h>

#define MAX_EDGES 79801
#define MAX_NODES 401

using namespace std;

class Compare {
 public:
    bool operator() (pair<int, int> a, pair<int, int> b) {
        return a.second > b.second;
    }
};


int main() {
    int n, m, q;
    ifstream fin ("revedges.in");
    fin >> n >> m >> q;
    vector<pair<int, int>> adj[n + 1];
    vector<int> matrix[n + 1];


    for (int i = 0, a, b; i < m; ++i) {
        fin >> a >> b;
        adj[a].push_back(make_pair(b, 0));
        adj[b].push_back(make_pair(a, 1));
    }

    FILE *output = fopen("revedges.out", "w");
    for (int i = 1; i < n + 1; ++i) {
        matrix[i].resize(n + 1, INT_MAX);
        matrix[i][i] = 0; // distanta de la un nod pana la el insusi e 0
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> q; 
        q.push(make_pair(0, i));
        while (!q.empty()) {
            int u = q.top().second;
            q.pop();

            for (auto k = adj[u].begin(); k != adj[u].end(); ++k) {
                int v = (*k).first;
                int w = (*k).second;
                if (matrix[i][v] > w + matrix[i][u]) {
                    matrix[i][v] = w + matrix[i][u];
                    q.push(make_pair(matrix[i][v], v));
                }
            }
        }

    }

    for (int i = 0, a, b; i < q; ++i) {
        fin >> a >> b;
        fprintf(output, "%d\n", matrix[a][b]);
    }
    
    fclose(output);

    return 0;
}