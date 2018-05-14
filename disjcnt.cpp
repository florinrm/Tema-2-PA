#include <bits/stdc++.h>

using namespace std;


const int kNmax = 100005;
vector<int> edges[kNmax];
vector<bool> visited;
vector<bool> articulation;
vector<int> parent;
vector<int> low;
vector<int> discovered;
vector<pair<int, int>> critical_edges;


int time_count = 0, n, m;

void findCriticalEdgesHelper (int v) {
	visited[v] = true;
	++time_count;
	low[v] = time_count;
	discovered[v] = time_count;
	for (auto i = edges[v].begin(); i != edges[v].end(); ++i) {
		if (!visited[*i]) {
			parent[*i] = v;
			findCriticalEdgesHelper(*i);
			low[v] = low[v] <= low[*i] ? low[v] : low[*i];
			if (low[*i] > discovered[v]) {
				critical_edges.push_back(make_pair(v, *i));
			}
		} else if (parent[v] != *i) {
			low[v] = low[v] <= discovered[*i] ? low[v] : discovered[*i];
		}
	}
}

void findCriticalEdges () {
    visited.resize(n + 1, false);
	low.resize(n + 1, 0);
	parent.resize(n + 1, INT_MIN);
	discovered.resize(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		if (!visited[i])
			findCriticalEdgesHelper(i);
	}
}

void removeCriticalEdges () {
    findCriticalEdges();
    for (int i = 0; i < (int) critical_edges.size(); ++i) {
        int u = critical_edges[i].first;
        int v = critical_edges[i].second;
        edges[u].erase(find(edges[u].begin(), edges[u].end(), v));
        edges[v].erase(find(edges[v].begin(), edges[v].end(), u));
    }
}

    vector<int> buff;
	vector<bool> visited1;
	stack<int> st;
    vector<vector<int>> connected;

void kindOfDFS (int v) {
	visited1[v] = true;
	for (auto i = edges[v].begin(); i != edges[v].end(); ++i) {
		if (!visited1[*i])
			kindOfDFS(*i);
	}
	st.push(v);
}

void DFS (int v) {
	visited1[v] = true;
	buff.push_back(v);
	for (auto i = edges[v].begin(); i != edges[v].end(); ++i) {
		if (!visited1[*i])
			DFS(*i);
	}
}

void getIslands () {

    visited1.resize(n + 1, false);

	for (int i = 1; i <= n; ++i) {
		if (!visited1[i])
			kindOfDFS(i);
	}
	for (int i = 1; i <= n; ++i)
		visited1[i] = false;
	//vector<vector<int>> sol;
	while (!st.empty()) {
		int node = st.top();
		st.pop();
		if (!visited1[node]) {
			DFS(node);
			connected.push_back(buff);
			buff.clear();
		}
	}
}


long long getResult () {
    long long sum = 0;
    for (int i = 0; i < (int) connected.size(); ++i) {
        int size = connected[i].size();
        cout << size << endl;
        if (size > 1) {
            sum += (1LL * size * (size - 1)) / 2;
        }
    }
    return sum;
}

int main() {
    ifstream fin("disjcnt.in");
    fin >> n >> m;
    for (int i = 0, a, b; i < m; ++i) {
        fin >> a >> b;
        edges[b].push_back(a);
        edges[a].push_back(b);
    } 
    fin.close();
    /*
    for (int i = 1; i <= n; ++i) {
        cout << i << ": ";
        for (int j = 0; j < edges[i].size(); ++j)
            cout << edges[i][j] << " ";
        cout << endl;
    }
    cout << "meow" << endl; */
    removeCriticalEdges(); 
    getIslands();
    /*
    for (int i = 1; i <= n; ++i) {
        cout << i << ": ";
        for (int j = 0; j < edges[i].size(); ++j)
            cout << edges[i][j] << " ";
        cout << endl;
    }

    cout << "meow" << endl;
    for (int i = 0; i < connected.size(); ++i) {
        cout << i + 1 << ": ";
        for (int j = 0; j < connected[i].size(); ++j) {
            cout << connected[i][j] << " ";
        }
        cout << endl;
    } */

    ofstream fout("disjcnt.out");
    long long res = getResult();
    fout << res;
    fout.close();

    return 0;
} 


/* 

muchile critice leaga componentele conexe intre ele
pot sa am componente conexe din 2 noduri: (5, 4), (4, 5)
nr de noduri din componenta conexa - combinari luate cate 2


asadar aflu muchiile critice, le tai, aflu componentele conexe, fac combinatorica si bam
*/