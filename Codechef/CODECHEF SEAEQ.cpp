// Same as editorial
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#pragma warning(disable:4786)
#pragma warning(disable:4996)
#include <ctime>
#include<list>
#include <numeric>
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
#include<unordered_set>
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
//typedef __int128 LLL;
typedef long long LLL;

typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII > VP;
typedef vector<PLL > VPL;
typedef vector<double> VD;
typedef long double ld;

int n, e;
const LL MOD = 1000000000 + 7;
LL fact[502], ifact[502];
LL dp[502][502 * 502];

void add(LL& a, LL& b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

void sub(LL& a, LL& b) {
	a -= b;
	if (a < 0) a += MOD;
}

LL bigmod(LL a, LL b) {
	if (b == 0) return 1;
	LL x = bigmod(a, b / 2);
	x = (x * x) % MOD;
	if (b & 1) x = (x * a) % MOD;
	return x;
}

void solve(int ks) {
	scanf("%d %d", &n, &e);
	e = MIN(e, n * (n - 1) / 2);
	LL ans = 0;
	for (int i = 1; i <= n; i++) {
		LL now = fact[n];
		now *= ifact[i];
		now %= MOD;
//		now *= ifact[n - i];
//		now %= MOD;
		now *= now;
		now %= MOD;
		now *= dp[i][e];
		now %= MOD;

		now *= (n - i + 1);
		now %= MOD;
		add(ans, now);
	}
	printf("%lld\n", ans);
}

int main()
{
#ifdef LOCAL
	double start_time = clock();
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
	//	freopen("out.out", "w", stdout);
#endif

	fact[0] = 1;
	for (int i = 1; i <= 500; i++) {
		fact[i] = (i * fact[i - 1]) % MOD;
	}
	ifact[500] = bigmod(fact[500], MOD - 2);
	for (int i = 499; i >= 0; i--) {
		ifact[i] = (ifact[i + 1] * (i + 1)) % MOD;
	}
	dp[1][0] = 1;
	for (int i = 2; i <= 500; i++) {
		int max_lim = i * (i - 1) / 2;
		LL run = 0;
		for (int j = 0; j <= max_lim; j++) {
			add(run, dp[i - 1][j]);
			dp[i][j] = run;
			if (j >= i - 1) sub(run, dp[i - 1][j - i + 1]);
		}
	}
	for (int i = 1; i <= 500; i++) {
		for (int j = 0; j <= 500 * 500; j++) {
			add(dp[i][j], dp[i][j - 1]);
		}
	}
	if (1) {
		int T = 1000;
		scanf("%d", &T);
		for (int ks = 1; ks <= T; ks++) solve(ks);
	}
	else {
		 solve(0);
	}

#ifdef LOCAL
	double end_time = clock();
	fprintf(stderr, "Time = %lf\n", (end_time - start_time) / CLOCKS_PER_SEC);
#endif

	return 0;
}
