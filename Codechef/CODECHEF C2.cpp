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

LL MOD;
map<PII, LL> M;

LL ncr[106][106];

LL f(int n, int k)
{
	if (n == 1) return 1;
	if (k == 0) return n;
	if (M.find(PII(n, k)) != M.end()) return M[PII(n, k)];

	if (n % 2) {
		LL temp = 1;
		for (int i = 1; i <= k; i++) {
			temp = (temp * n) % MOD;
		}
		LL ret = (f(n - 1, k) + temp) % MOD;
		return M[PII(n, k)] = ret;
	}

	LL temp = 1;
	for (int i = 1; i <= k; i++) {
		temp = (temp * 2) % MOD;
	}

	LL ret = (temp * f(n / 2, k)) % MOD;
	temp = 1;
	for (int i = 0; i <= k; i++) {
		LL z = (ncr[k][i] * ((temp * f(n / 2, i)) % MOD)) % MOD;
		if ((k - i) % 2) z = MOD - z;
		ret = (ret + z) % MOD;
		temp = (temp * 2) % MOD;
	}

	return M[PII(n, k)] = ret;
}

void gen()
{
	ncr[0][0] = 1;
	int limncr = 102;
	int i, j;
	for (i = 1; i <= limncr; i++)
		for (j = 0; j <= limncr; j++)
		{
			if (j>i) ncr[i][j] = 0;
			else if (j == i || j == 0) ncr[i][j] = 1;
			else ncr[i][j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % MOD;
		}
}

int value(int n, int k)
{
	gen();
	return f(n, k);
}

LL mod;
LL S[105][105];

void solve() {
	LL n, k;
	scanf("%lld %lld %lld", &n, &k, &mod);

	M.clear();
	MOD = mod;
	printf("%d\n", value(n, k));
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