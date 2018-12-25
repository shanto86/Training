// The constraints are low enough to perform simulation.
// However, the last step, that is, finding the sum of a diaognal-square can not be
// found in naive way. One can easily optimize this step by sliding the square
// and add/sub-ing the modified cells. This is not O(1) but was good enough to pass the generous TL.
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
//typedef __int128 LL;
//typedef __int64 LL;

typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef pair<long double, long double> PDD;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII > VP;
typedef vector<double> VD;
typedef vector<LL> VL;
typedef long double ld;

int R, C, s, pr, pc;
int sum[2][102][102];
const int MOD = 1000000007;

void add(int& a, int& b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

void sub(int& a, int& b) {
	a -= b;
	if (a < 0) a += MOD;
}

void Calc(int t) {
	sum[1][1][1] = 0;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (ABS(i - 1) + ABS(j - 1) < t) {
				add(sum[1][1][1], sum[0][i][j]);
			}
		}
	}
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (i == 1 && j == 1) continue;
			
			if (j != 1) {
				sum[1][i][j] = sum[1][i][j - 1];
				int r, c;
				r = i, c = j - t;
				for (int k = 0; k < t; k++) {
					if (IN(r + k, 1, R) && IN(c + k, 1, C)) {
						sub(sum[1][i][j], sum[0][r + k][c + k]);
					}
					if (k && IN(r - k, 1, R) && IN(c + k, 1, C)) {
						sub(sum[1][i][j], sum[0][r - k][c + k]);
					}
				}
				r = i, c = j + t - 1;
				for (int k = 0; k < t; k++) {
					if (IN(r + k, 1, R) && IN(c - k, 1, C)) {
						add(sum[1][i][j], sum[0][r + k][c - k]);
					}
					if (k && IN(r - k, 1, R) && IN(c - k, 1, C)) {
						add(sum[1][i][j], sum[0][r - k][c - k]);
					}
				}
			}
			else {
				sum[1][i][j] = sum[1][i - 1][j];
				int r, c;
				r = i - t, c = j;
				for (int k = 0; k < t; k++) {
					if (IN(r + k, 1, R) && IN(c + k, 1, C)) {
						sub(sum[1][i][j], sum[0][r + k][c + k]);
					}
					if (k && IN(r + k, 1, R) && IN(c - k, 1, C)) {
						sub(sum[1][i][j], sum[0][r + k][c - k]);
					}
				}
				r = i + t - 1, c = j;
				for (int k = 0; k < t; k++) {
					if (IN(r - k, 1, R) && IN(c - k, 1, C)) {
						add(sum[1][i][j], sum[0][r - k][c - k]);
					}
					if (k && IN(r - k, 1, R) && IN(c + k, 1, C)) {
						add(sum[1][i][j], sum[0][r - k][c + k]);
					}
				}
			}
		}
	}
}
void solve(int ks) {
	scanf("%d %d %d %d %d", &R, &C, &s, &pr, &pc);
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			scanf("%d", &sum[1][i][j]);
		}
	}
	for (int t = 1; t <= s; t++) {
		for (int i = 1; i <= R; i++) {
			for (int j = 1; j <= C; j++) {
				sum[0][i][j] = sum[1][i][j];
			}
		}
		Calc(t);
	}
	printf("Case %d: %d\n", ks, sum[1][pr][pc]);
}

int main()
{
#ifdef LOCAL
	double start_time = clock();
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
	//	freopen("out.out", "w", stdout);
#endif
	freopen("treasures.in", "r", stdin);

	if (1) {
		int T;
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
