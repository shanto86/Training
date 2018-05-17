/*
Tricky DP problem. Requires observation that, if we take
smallest m numbers, the optimal solution would differ
from this one by at most k(k-1) for each mod k set.
The editorial says at most (k-1) for each mod is enough.
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

int n, m, k;
VP V[22];
LL dp[805][22];
LL solve(VI& X, int need, int mod) {
	MEM(dp, -1);
	dp[0][0] = 0;
	for (int x : X) {
		for (int j = 800; j >= 0; j--) {
			for (int m = 0; m < k; m++) {
				if (dp[j][m] == -1) continue;
				LL& ret = dp[j + 1][(m + x) % k];
				LL now = dp[j][m] + x;
				if (ret == -1 || ret > now) ret = now;
			}
		}
	}
	return dp[need][mod];
}

void solve() {
	scanf("%d %d %d", &n, &m, &k);
	VI X;
	for (int i = 0; i < k; i++) V[i].clear();
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		X.push_back(x);
	}
	sort(ALL(X));
	for (int i = 0; i < n; i++) {
		V[X[i] % k].push_back(PII(X[i], i < m));
	}

	int taken = 0;
	LL sum = 0;
	X.clear();

	for (int i = 0; i < k; i++) {
		sort(ALL(V[i]));
		int cnt = 0;
		for (int j = 0; j < SZ(V[i]); j++) {
			cnt += V[i][j].second == 1;
		}
		for (int j = 0; j < cnt - (k - 1); j++) {
			taken++;
			sum += V[i][j].first;
		}
		for (int j = MAX(0, cnt - (k - 1)), cc = 0; j < SZ(V[i]) && cc < 2 * k; cc++, j++) {
			X.push_back(V[i][j].first);
		}
	}

	int need = m - taken;
	LL ans = solve(X, need, (k - (sum%k))%k);
	if (ans != -1) ans += sum;
	printf("%lld\n", ans);
}

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	while (T--) solve();

	return 0;
}