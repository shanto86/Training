// Main solution is to count number of odd divisors of n!. To solve so,
// we need to generate all prime < 1e8. Loop through the primes and find 
// power of that prime in n!. But that's slow. You can solve for
// < sqrt(n) primes and >= primes separately.

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

void solve() {
	// 2N! = n2 + n - m2 - m
	// 2N! = (n - m)(n + m + 1) = ab
	// n = (a + b - 1)/2
	// m = (a - b - 1)/2
	
}

int mark[100000000 / 32 + 10];
int P[5800000], szP;

int last = -1, pos = -1;
int FindPos(int x) {
	if (x == last) return pos;
	last = x;
	pos = upper_bound(P, P + szP, x) - P;
	return pos;
}

LL bigmod(LL a, LL n, LL m) {
	if (n == 0) return 1;
	LL x = bigmod(a, n / 2, m);
	x = (x * x) % m;
	if (n & 1) x = (x * a) % m;
	return x;
}

int main()
{
	double start_time = clock();
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
	//	freopen("out.out", "w", stdout);
#endif

	int T, id = 0;

	for (LL i = 3; i <= 100000000; i += 2) {
		if ((mark[i >> 5] >> (i % 32)) & 1) {
			continue;
		}
		P[szP++] = i;
		for (LL j = i*i; j <= 100000000; j += 2*i) {
			mark[j >> 5] |= (1ll << (j % 32));
		}
	}
	//printf("%d\n", szP);
	scanf("%d", &T);
	for (int i = 1; i <= T; i++) {
		last = pos = -1;
		int n, m;
		scanf("%d %d", &n, &m);
		LL ans = 1;
		for (int ii = 0; ii < szP; ii++) {
			LL p = P[ii];
			if (n < p * p) {
				//printf(">>%d\n", ii);
				break;
			}
			LL cnt = 0;
			LL temp = n;
			while (temp) cnt += temp / p, temp /= p;
			ans *= cnt + 1;
			ans %= m;
		}
		//printf("%lld\n", ans);
		for (int ii = 1; ii * ii < n; ii++) {
			if (n < ii * (1 + ii)) break;
			LL x = FindPos(n / ii);
			LL y = FindPos(n / (ii + 1));
			LL cnt = x - y;
			ans *= bigmod(ii + 1, cnt, m);
			ans %= m;
		}
		//printf("%d\n", pos);
		ans = (ans + m - 1) % m;
		printf("%lld\n", ans);
	}

	double end_time = clock();
	fprintf(stderr, "Time = %lf\n", (end_time - start_time) / CLOCKS_PER_SEC);

	return 0;
}
