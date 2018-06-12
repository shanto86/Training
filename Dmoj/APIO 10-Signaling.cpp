// Editorial: http://apio-olympiad.org/2010/solutions.pdf
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
//typedef __int64 LL;

typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

LL xx[4000], yy[4000];
LL n;

int quadrant(const PLL& A) {
	if (A.first >= 0 && A.second >= 0) return 0;
	if (A.first <= 0 && A.second >= 0) return 1;
	if (A.first <= 0 && A.second <= 0) return 2;
	if (A.first >= 0 && A.second <= 0) return 3;
	assert(0);
}

// clockwise
bool circular_cmp(const PLL& A, const PLL& B) {
	int quadA = quadrant(A), quadB = quadrant(B);
	if (quadA != quadB) return quadA < quadB;
	LL d = A.second  * B.first - A.first * B.second;
	return d < 0;
}

LL calcA() {
	LL ret = 0;
	for (int i = 0; i < n; i++) {
		LL now = 0;
		vector<PLL> V;
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			V.push_back({ xx[j] - xx[i], yy[j] - yy[i] });
		}

		sort(ALL(V), circular_cmp);
		int k = 0;
		for (int j = 0; j < SZ(V); j++) {
			if (k < j) k = j;
			while (true) {
				LL d = V[j].second * V[(k + 1) % SZ(V)].first - V[j].first * V[(k + 1) % SZ(V)].second;
				if (d < 0) k++;
				else break;
			}
			LL extra = k - j;
			now += extra * (extra - 1) / 2;
		}
		//printf(">>%lld %lld, %lld\n", xx[i], yy[i], now);
		ret += now;
	}
	return ret;
}

LL calcB() {
	return n * (n - 1) * (n - 2) * (n - 3) / 24;
}

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif
	scanf("%lld", &n);
	//srand(n);
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &xx[i], &yy[i]);
		//xx[i] = rand() % 11;
		//yy[i] = rand() % 11;
	}
	LL A = calcA();
	LL B = calcB();
	assert(A >= 3 * B);
	LL P = A - 2 * B;
	LL Q = n * (n - 1) * (n - 2) / 6;
	double ans = 3 + (1. * P) / Q;
	printf("%.10lf\n", ans);
	return 0;
}
