// Adhoc  dfs problem.
// Greedily color the edges (try to color the edges
// closer to the root). Now implement it efficiently
// using dfs.
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
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

struct Edge {
	int v, id, type;
};
vector<Edge> adj[200005];
VI ans;

int DFS(int at, int cntA, int cnt) {
	int mx = ((cnt - cntA) * 2 >= cnt ? 0 : (cnt + 1)/2 - (cnt - cntA));
	for (Edge& e : adj[at]) {
		int x = DFS(e.v, cntA + e.type, cnt + 1);
		if (x > cntA) {
			ans.push_back(e.id);
			x--;
		}
		mx = MAX(mx, x);
	}
	return mx;
}

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int a, b;
		char s1[20], s2[20];
		scanf("%d %d %s", &a, &b, s1);
		if (s1[0] == 'a') scanf("%s", s2);

		adj[b].push_back({ a, i, s1[0] == 'a' });
	}

	DFS(1, 0, 0);
	printf("%d\n", SZ(ans));
	for (int i = 0; i < SZ(ans); i++) {
		if (i) printf(" ");
		printf("%d", ans[i]);
	}
	printf("\n");

	return 0;
}