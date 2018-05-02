// Idea normal, code is a bit complex. Main idea is to use segment tree to fast process the topological sort algo.
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

typedef pair<int, int> PII;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

//typedef int LL;
typedef long long int LL;
//typedef __int64 LL;

int n, m;
VI V[100005];
int in[100005];
PII which[100005 * 4];
int lazy[100005 * 4];

void rejoin(int at) {
	int L = at * 2, R = at * 2 + 1;
	which[at].first = MIN(which[L].first, which[R].first);
	which[at].second = 0;
	if (which[L].first == which[at].first) which[at].second = MAX(which[at].second, which[L].second);
	if (which[R].first == which[at].first) which[at].second = MAX(which[at].second, which[R].second);
}

void build(int at, int l, int r) {
	if (l == r) {
		which[at] = { in[l], l };
		return;
	}
	lazy[at] = 0;
	int m = (l + r) / 2;
	build(at * 2, l, m);
	build(at * 2 + 1, m + 1, r);
	rejoin(at);
}

void propagate(int at) {
	lazy[at * 2] += lazy[at];
	lazy[at * 2 + 1] += lazy[at];
	which[at * 2].first += lazy[at];
	which[at * 2 + 1].first += lazy[at];
	lazy[at] = 0;
}

void update(int at, int l, int r, int L, int R, int val) {
	if (R < l || r < L) return;
	if (L <= l && r <= R) {
		lazy[at] += val;
		which[at].first += val;
		return;
	}

	if (lazy[at]) {
		propagate(at);
	}

	int m = (l + r) / 2;
	update(at * 2, l, m, L, R, val);
	update(at * 2 + 1, m + 1, r, L, R, val);
	rejoin(at);
}

void remove(int id) {
	update(1, 1, n, id + 1, n, -1);
	for (int v : V[id]) {
		update(1, 1, n, v, v, +1);
	}
	update(1, 1, n, id, id, 1000000);
}

void solve() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		V[i].clear();
		in[i] = i - 1;
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		V[u].push_back(v);
		in[v]--;
	}
	build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		int now = which[1].second;
		remove(now);
		if (i > 1) printf(" ");
		printf("%d", now);
	}
	printf("\n");
}

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\input.in", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
