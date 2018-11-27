/*
The obvious approach is to do sqrt method. Loop from i = 1 to sqrt(k) and,
solve for the answer being 1 to sqrt(k)-1.
*/
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
//typedef __int128 LL;
//typedef __int64 LL;

typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef pair<long double, long double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;
typedef vector<double> VD;
typedef vector<LL> VL;

typedef long double ld;

LL brute(LL n, LL k) {
	LL ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += k % i;
	}
	return ans;
}

LL smart(LL n, LL k) {
	LL ans = 0;
	if (n > k) ans += (n - k) * k, n = k;
	for (int ii = 1; ; ii++) {
		if (k < ii * ii) {
			break;
		}
		if (ii > n) break;
		// process for ii, that is independent value of: n/1, n/2, ... = n/ii
		ans += k % ii;
	}
	for (int ii = 1; ; ii++) {
		if (k < ii * (1 + ii)) break;

		// start lo = n/(ii + 1) + 1
		// end hi = n/ii
		// Process for answer ii, that is: ii = n/start ... n/end
		LL start = k / (ii + 1) + 1;
		LL end = k / ii;
		if (start > n) continue;
		if (end > n) end = n;
		ans += (end - start + 1) * k - ii * (end + start) * (end - start + 1) / 2;
	}
	return ans;
}

void solve() {
	LL n, k;
	while (scanf("%lld %lld", &n, &k) != EOF) {
//	for (int i = 1; i <= 1000; i++) {
//		n = rand() % 10 + 1;
//		k = rand() % 10 + 1;
//		LL ans1 = brute(n, k);
		LL ans2 = smart(n, k);
//		if (ans1 != ans2) {
//			printf("%lld %lld-> %lld %lld\n", n, k, ans1, ans2);
//		}
		printf("%lld\n", ans2);
	}
}

int main()
{
	double start_time = clock();
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
	//	freopen("out.out", "w", stdout);
#endif

	solve();

	double end_time = clock();
	fprintf(stderr, "Time = %lf\n", (end_time - start_time) / CLOCKS_PER_SEC);

	return 0;
}
