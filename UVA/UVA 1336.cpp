/*
DP state is, from where to where the robot already
cleaned, and at which side it is.
Then recurrance will follow easily.
*/
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

int n, v, x;
struct Robot {
	int pos, cost, del;
	void scan() {
		scanf("%d %d %d", &pos, &cost, &del);
	}
	bool operator<(const Robot& r) const {
		return pos < r.pos;
	}
} robot[1004];

int psum[1003], ssum[1003];

double dp[1003][1003][2];
int vis[1003][1003][2];
double DP(int a, int b, int side) {
	if (a == 0 && b == n - 1) return 0;
	double& ret = dp[a][b][side];
	if (vis[a][b][side]) return ret;
	vis[a][b][side] = 1;

	ret = 2000000000;
	if (a) {
		if (side == 0) {
			double t = (1. * robot[a].pos - robot[a - 1].pos) / v;
			double now = DP(a - 1, b, 0) + t * (psum[a - 1] + ssum[b + 1]) + robot[a - 1].cost;
			ret = MIN(ret, now);
		}
		else {
			double t = (1. * robot[b].pos - robot[a - 1].pos) / v;
			double now = DP(a - 1, b, 0) + t * (psum[a - 1] + ssum[b + 1]) + robot[a - 1].cost;
			ret = MIN(ret, now);
		}
	}
	if (b != n - 1) {
		if (side == 0) {
			double t = (1. * robot[b + 1].pos - robot[a].pos) / v;
			double now = DP(a, b + 1, 1) + t * (psum[a - 1] + ssum[b + 1]) + robot[b + 1].cost;
			ret = MIN(ret, now);
		}
		else {
			double t = (1. * robot[b + 1].pos - robot[b].pos) / v;
			double now = DP(a, b + 1, 1) + t * (psum[a - 1] + ssum[b + 1]) + robot[b + 1].cost;
			ret = MIN(ret, now);
		}
	}
	return ret;
}
LL solve() {
	for (int i = 0; i < n; i++) {
		robot[i].scan();
	}
	robot[n++] = { x, 0, 0 };

	sort(robot, robot + n);
	int at = -1;
	for (int i = 0; i < n; i++) {
		if (robot[i].pos == x) {
			at = i;
		}
	}

	psum[0] = robot[0].del;
	for (int i = 1; i < n; i++) psum[i] = psum[i - 1] + robot[i].del;
	ssum[n] = 0;
	for (int i = n - 1; i >= 0; i--) ssum[i] = ssum[i + 1] + robot[i].del;

	MEM(vis, 0);
	return DP(at, at, 0);
}

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif
	while (scanf("%d %d %d", &n, &v, &x) != EOF) {
		if (!n) break;
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}