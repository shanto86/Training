#pragma warning(disable:4786)
#pragma warning(disable:4996)
#include<list>
#include<bitset>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<functional>
#include<string>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<utility>
#include<fstream>
#include<sstream>
#include<cmath>
#include<stack>
#include<assert.h>
using namespace std;

#define MEM(a, b) memset(a, (b), sizeof(a))
#define CLR(a) memset(a, 0, sizeof(a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(X) ( (X) > 0 ? (X) : ( -(X) ) )
#define S(X) ( (X) * (X) )
#define SZ(V) (int )V.size()
#define FORN(i, n) for(int i = 0; i < n; i++)
#define FORAB(i, a, b) for(int i = a; i <= b; i++)
#define ALL(V) V.begin(), V.end()
#define IN(A, B, C)  ((B) <= (A) && (A) <= (C))
#define AIN(A, B, C) assert(IN(A, B, C))

//typedef int LL;
typedef long long int LL;
//typedef __int64 LL;

typedef pair<int, int> PII;
typedef pair<long double, long double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

VI V[505];
VI adj[505];
VI ids[505];
int n, c;
int vis[505], eVis[505];
int start[505], back[505], t;

vector<PII> edges;
int isBridge[505];

void DFS(int at) {
	vis[at] = 1;
	start[at] = back[at] = ++t;

	for (int i : adj[at]) {
		if (eVis[i]) continue;
		eVis[i] = 1;
		int v = edges[i].first ^ edges[i].second ^ at;
		if (!vis[v]) {
			DFS(v);
			if (back[v] > start[at]) {
				isBridge[i] = 1;
			}
		}
		back[at] = MIN(back[at], back[v]);
	}
}

int calc() {
	int comp = 0;
	CLR(vis);
	for (int i = 1; i <= c; i++) {
		if (vis[i] || SZ(adj[i]) == 0) continue;
		comp++;
		queue<int> Q;
		Q.push(i);
		vis[i] = 1;
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			for (int du : adj[u]) {
				int v = edges[du].first ^ edges[du].second ^ u;
				if (vis[v]) continue;
				vis[v] = 1;
				Q.push(v);
			}
		}
	}

	AIN(comp, 1, c);
	if (comp > 1) return -1;

	int odd = 0;
	for (int i = 1; i <= c; i++) {
		int deg = SZ(adj[i]);
		odd += (deg & 1);
	}
	assert((odd % 2) == 0);
	if (odd > 2) return -1;
	if (!odd) return 0;

	CLR(vis);
	CLR(eVis);
	CLR(isBridge);
	t = 0;
	for (int i = 1; i <= c; i++) {
		if (!vis[i]) {
			DFS(i);
		}
	}

	int ret = 1000000;
	for (int i = 1; i <= c; i++) {
		if (SZ(adj[i]) % 2 == 0) continue;
		if (SZ(adj[i]) == 1) {
			ret = MIN(ret, adj[i][0]);
		}
		else {
			for (int e : adj[i]) {
				if (!isBridge[e]) ret = MIN(ret, e);
			}
		}
	}
	return ret;
}

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif
	while (scanf("%d %d", &n, &c) != EOF) {
		if (!n && !c) break;
		AIN(n, 1, 500);
		AIN(c, 1, 100);
		for (int i = 1; i <= n; i++) V[i].clear();
		for (int i = 1; i <= c; i++) {
			int k;
			scanf("%d", &k);
			for (int j = 1; j <= k; j++) {
				int city;
				scanf("%d", &city);
				city++;
				V[city].push_back(i);
			}
		}
		edges.clear();
		for (int i = 1; i <= c; i++) {
			adj[i].clear();
		}
		for (int i = 1; i <= n; i++) {
			AIN(SZ(V[i]), 1, 2);
			if (SZ(V[i]) == 1) {
				edges.push_back({ V[i][0], V[i][0] });
				adj[V[i][0]].push_back(i - 1);
				adj[V[i][0]].push_back(i - 1);
			}
			else {
				edges.push_back({ V[i][0], V[i][1] });
				adj[V[i][0]].push_back(i - 1);
				adj[V[i][1]].push_back(i - 1);
			}
		}

		printf("%d\n", calc());
	}
	return 0;
}