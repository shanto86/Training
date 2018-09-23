/*
Main idea is inclusion exclusion. Although it is not difficult to come up with the idea 
directly, I came from slow solution to fast (although the solutions are independent from each other).

First of all, we will convert the problem to: how many R*C boards have no rows/columns with only 0.
It's not difficult, just multiply ncr(R, r)*ncr(C, c) with the answer from (R-r)*(C-c) size board.

Now the main problem,
First slow solution is recurrence: f(r1, r2, c) = how many columns are remaining, r1 rows have atleast 
one 1, and r2 rows have no 1s, and r1+r2 = R. So the number of state is O(n^2).
If we run a loop over 0 to r2, we can easily come up with O(n^3) solution.

The second slow solution is O(n^2), but this time, instead of walking through column and looping
through rows, we just walk through rows and column will be taken care by formula.
There are: (2^r)^C arrangements of a r*C board. Now we will find, how many r*C boards
maintain our restriction. We will first find the answer for 1*C, 2*C ... boards. So when
we want to find the answer for r*C we know the answer for smaller r's. Say answer for r*C is F[r]. Then:
F[r] = (2^r)^C - ncr(r, 1)F[r - 1] - ncr(r, 2)F[r-2]...

Next O(n) solution (with precalc):
F[r] = (2^r - 1)^C = number of r*C boards with no zero column. 
Subtract ncr(r, 1)*F[r - 1]
Add ncr(r, 2)*F[r - 2]
and so on
to get how many r*C boards with no zero column have also no zero rows.
*/
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
using namespace std;

#define MEM(a, b) memset(a, (b), sizeof(a))
#define CLR(a) memset(a, 0, sizeof(a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(X) ( (X) > 0 ? (X) : ( -(X) ) )
//#define S(X) ( (X) * (X) )
#define SZ(V) (int )V.size()
#define FORN(i, n) for(int i = 0; i < n; i++)
#define FORAB(i, a, b) for(int i = a; i <= b; i++)
#define ALL(V) V.begin(), V.end()
#define IN(A, B, C)  ((B) <= (A) && (A) <= (C))
#define AIN(A, B, C) assert(IN(A, B, C))

//typedef int LL;
typedef long long int LL;
//typedef __int64 LL;

typedef pair<int,int> PII;
typedef pair<LL, LL> PLL;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;
typedef vector<double> VD;
typedef vector<LL> VL;

LL F[100005];
const LL MOD = 1000000007;
LL fact[100005];
LL ifact[100005];

LL bigmod(LL a, LL b) {
	if (b == 0) return 1;
	LL x = bigmod(a, b / 2);
	x = (x * x) % MOD;
	if (b & 1)x = (x*a) % MOD;
	return x;
}

LL ncr(int n, int r) {
	LL ret = fact[n];
	ret = (ret * ifact[r]) % MOD;
	ret = (ret * ifact[n - r]) % MOD;
	return ret;
}

int main()
{
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
	//	freopen("out.out", "w", stdout);
	double start_time = clock();
#endif

	fact[0] = 1;
	for (int i = 1; i <= 100000; i++) {
		fact[i] = (fact[i - 1] * i) % MOD;
	}
	ifact[100000] = bigmod(fact[100000], MOD - 2);
	for (int i = 99999; i >= 1; i--) {
		ifact[i] = (ifact[i + 1] * (i + 1)) % MOD;
	}
	ifact[0] = 1;
	int R, C, r, c;
	scanf("%d %d %d %d", &R, &C, &r, &c);

	if (R == r || C == c) {
		LL ans = (R == r && C == c);
		printf("%lld\n", ans);
		return 0;
	}

	R -= r, C -= c;
	//f[1] = 1;
	//f[0] = 1;
	//F[1] = 1;
	//for (int i = 2; i <= 10; i++) {
	//	f[i] = bigmod(bigmod(2, i) + MOD - 0, 2);
	//	F[i] = bigmod(bigmod(2, i) + MOD - 1, 2);
	//	for (int j = 1; j <= i; j++) {
	//		f[i] = (f[i] + MOD - (ncr(i, j) * f[i - j]) % MOD) % MOD;
	//		if (f[i] < 0) f[i] += MOD;
	//	}
	//}

	LL p2 = 1;
	for (int i = 1; i <= R; i++) {
		p2 = (p2 * 2) % MOD;
		F[i] = bigmod(p2 + MOD - 1, C);
	}
	LL ans = F[R];
	for (int j = R - 1; j >= 1; j--) {
		int k = (R - j);
		LL tmp = ncr(R, k) * F[j];
		tmp %= MOD;
		if (k & 1) tmp = MOD - tmp;
		ans = (ans + tmp) % MOD;
	}
	ans *= (ncr(R + r, r) * ncr(C + c, c)) % MOD;
	ans %= MOD;

	printf("%lld\n", ans);

#ifdef LOCAL
	double end_time = clock();
	fprintf(stderr, "Time = %lf\n", (end_time - start_time) / CLOCKS_PER_SEC);
#endif

	return 0;
}
