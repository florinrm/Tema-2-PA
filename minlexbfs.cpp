#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>

using namespace std;

int getSource (vector<int> *adj, int n) {
    for (int i = 1; i <= n; ++i) {
        if (!adj[i].empty())
            return i;
    }
    return 0;
}

int main () {
    int n, m;
    FILE *input = fopen("minlexbfs.in", "r");
    FILE *output = fopen("minlexbfs.out", "w");
    fscanf(input, "%d %d", &n, &m);
    vector<int> adj[n + 1];
    vector<bool> visited(n);
    for (int i = 0, x, y; i < m; ++i) {
        fscanf(input, "%d %d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    fclose(input);

    for (int i = 1; i <= n; ++i) {
        if (!adj[i].empty())
            sort(adj[i].begin(), adj[i].end());
    }
    
    int src = getSource(adj, n);
    queue<int> q;
    visited[src] = true;
    q.push(src);

    while (!q.empty()) {
        src = q.front();
        q.pop();
        fprintf(output, "%d ", src);
        for (auto i = adj[src].begin(); i != adj[src].end(); ++i) {
            if (!visited[*i]) {
                visited[*i] = true;
                q.push(*i);
            }
        }
    }
    fclose(output);

    return 0;
}
