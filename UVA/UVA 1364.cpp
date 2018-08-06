// Split into BCC, then bicoloring.
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
#define FORN(i, n) for(i = 0; i < n; i++)
#define FORAB(i, a, b) for(int i = a; i <= b; i++)
#define ALL(V) V.begin(), V.end()
#define IN(A, B, C)  ((B) <= (A) && (A) <= (C))
#define AIN(A, B, C) assert(IN(A, B, C))

typedef pair<int,int> PII;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

//typedef int LL;
typedef long long int LL;
//typedef __int64 LL;

#define MAX_EDGE 1000006
#define MAX_NODE 1003

struct EDGE {
	int from, to, next;
};

EDGE edge[MAX_EDGE];
int nedge, head[MAX_NODE];

void add_edge(int u, int v) {
	nedge++;
	edge[nedge].from = u;
	edge[nedge].to = v;
	edge[nedge].next = head[u];
	head[u] = nedge;
}

stack<int> S;
vector<vector<int> > blocks;
int low[MAX_NODE], dfsNumber[MAX_NODE], dfsTime;
int mark[MAX_NODE], isCutPoint[MAX_NODE];

void dfs(int root, int at, int parent)
{
	int childOfRoot = 0;

	low[at] = dfsNumber[at] = ++dfsTime;
	mark[at] = 1;
	S.push(at);

	for (int i = head[at]; i != -1; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == parent) continue;
		if (dfsNumber[v] == 0)
		{
			dfs(root, v, at);
			low[at] = MIN(low[at], low[v]);
			if (at == root) childOfRoot++;
			if (low[v] >= dfsNumber[at])
			{
				int x;
				vector<int> V;

				do
				{
					x = S.top();
					S.pop();
					mark[x] = 0;
					V.push_back(x);
				} while (v != x);

				V.push_back(at);
				blocks.push_back(V);

				if (at != root) isCutPoint[at] = true;
			}
		}
		else if (mark[v])
		{
			low[at] = MIN(low[at], dfsNumber[v]);
		}
	}

	if (at == root && childOfRoot >= 2) isCutPoint[at] = true;
}

void Initialize(int n)
{
	blocks.clear();
	while (!S.empty()) S.pop();

	nedge = -1;
	dfsTime = 0;

	memset(head, -1, sizeof(head));
	memset(mark, 0, sizeof(mark));
	memset(isCutPoint, false, sizeof(isCutPoint));
	memset(dfsNumber, 0, sizeof(dfsNumber));
}

int odd[MAX_NODE];
int color[MAX_NODE][2];
int bicolor(int at, int ncomp)
{
	queue<PII> Q;
	int u, i;

	color[at][0] = 1;
	Q.push({ at, 0 });
	while (!Q.empty())
	{
		PII u = Q.front();
		Q.pop();
		for (i = head[u.first]; i != -1; i = edge[i].next)
		{
			if (mark[edge[i].to] != ncomp) continue;
			PII v = { edge[i].to, 1 ^ u.second };
			if (color[v.first][v.second]) continue;
			color[v.first][v.second] = 1;
			Q.push(v);
		}
	}
	return !color[at][1];
}

int adg[MAX_NODE][MAX_NODE];

//VI V[1003];

int main()
{
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
	//	freopen("out.out", "w", stdout);
#endif
	int T;
	//scanf("%d", &T);
	//for (int ks = 1; ks <= T; ks++)
	while (true)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		if (!n && !m) break;
		Initialize(n);
		CLR(adg);

		for (int i = 0; i<m; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			adg[a][b] = adg[b][a] = 1;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (adg[i][j])continue;
				add_edge(i, j);
				add_edge(j, i);
			}
		}
		for (int i = 1; i <= n; i++) 
		{
			if (dfsNumber[i]) continue;
			dfs(i, i, -1);
		}

		int comp = 0;
		CLR(mark);
		CLR(odd);
		for (auto& bcc : blocks) {
			comp++;
			for (int v : bcc) {
				mark[v] = comp;
				color[v][0] = color[v][1] = 0;
			}
			if (!bicolor(bcc[0], comp)) {
				for (int v : bcc) odd[v] = 1;
			}
		}

		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if (!odd[i]) ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
