// Main idea is winding number. Once you figure out
// how to say, whether the circle can pass through two given
// circles, the rest will be a bfs/dfs with winding number.
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
#include<unordered_map>
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
typedef pair<LL, LL> PLL;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<PII > VP;

struct Circle {
	double x, y, r;
	void scan() {
		scanf("%lf %lf %lf", &x, &y, &r);
	}
};
Circle circles[303];
int w[303][303];
int n;
int vis[303][2];

int cross(int id1, int id2) {
	if (circles[id1].y == circles[id2].y) return 0;
	if (circles[id1].y <= circles[n].y && circles[id2].y <= circles[n].y) return 0;
	if (circles[id1].y > circles[n].y && circles[id2].y > circles[n].y) return 0;
	double x = (circles[id2].x - circles[id1].x) / (circles[id2].y - circles[id1].y) * (circles[n].y - circles[id1].y) + circles[id1].x;
	if (x >= circles[n].x) return 1;
	return 0;
}

int solve() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			w[i][j] = 0;
			if (i == j) w[i][j] = 0;
			else {
				double dist = sqrt(S(circles[i].x - circles[j].x) + S(circles[i].y - circles[j].y));
				if (dist - circles[i].r - circles[j].r < circles[n].r * 2) {
					w[i][j] = 1;
				}
			}
		}
	}

	CLR(vis);
	queue<PII> Q;
	for (int i = 0; i < n; i++) {
		if (vis[i][0] || vis[i][1]) continue;
		Q.push({ i, 0 });
		vis[i][0] = 1;
		while (!Q.empty()) {
			PII now = Q.front();
			Q.pop();
			for (int i = 0; i < n; i++) {
				if (w[now.first][i]) {
					int new_node = i, new_color = now.second;
					if (cross(now.first, i)) {
						new_color ^= 1;
					}
					if (vis[new_node][new_color]) continue;
					vis[new_node][new_color] = 1;
					Q.push({ new_node, new_color });
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (vis[i][0] && vis[i][1]) return 0;
	}
	return 1;
}
int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
	//	freopen("out.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i <= n; i++) circles[i].scan();
		printf("%s\n", solve() ? "YES" : "NO");
		if (T) printf("\n");
	}
	return 0;
}
