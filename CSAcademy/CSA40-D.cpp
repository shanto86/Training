/*
dp[at][right] = Currently placing at, (1..at-1 are already placed), there are right numbers in right side.


if (at+1 to be right to at) {
for i = right to at-1:
	dp[at+1][right]+= dp[at][i]
}
else if (at+1 to be left to at) {
for i = right-1 to 0
	dp[at+1][right]+= dp[at][i]
}

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

typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;
typedef vector<double> VD;
typedef vector<LL> VL;

const int MOD = 1000000007;
int dp[2][2003], sdp[2003];
int n;

void add(int& a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

int main()
{
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
	//	freopen("out.out", "w", stdout);
	double start_time = clock();
#endif

	scanf("%d", &n);
	int u = 0, v = 1;
	CLR(dp);
	dp[u][0] = 1;
	for (int i = 2; i <= n; i++) {
		int ord;
		scanf("%d", &ord);
		//ord = rand() % 2;
		for (int j = 0; j <= n; j++) dp[v][j] = 0;
		for (int j = 0; j <= n; j++) sdp[j] = dp[u][j];
		for (int j = 1; j <= n; j++) add(sdp[j], sdp[j - 1]);

		for (int j = 0; j <= i - 1; j++) {
			if (ord == 0) {
				// i will sit left of i-1
				if (j) dp[v][j] = sdp[j - 1];
			}
			else {
				// i will sit right of i-1
				dp[v][j] = sdp[i - 2];
				if (j) dp[v][j] -= sdp[j - 1];
				if (dp[v][j] < 0) dp[v][j] += MOD;
			}
		}
		swap(u, v);
	}
	int ans = 0;
	for (int i = 0; i <= n - 1; i++) add(ans, dp[u][i]);
	printf("%d\n", ans);


#ifdef LOCAL
	double end_time = clock();
	fprintf(stderr, "Time = %lf\n", (end_time - start_time) / CLOCKS_PER_SEC);
#endif

	return 0;
}
