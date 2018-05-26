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

struct Glass {
	int h, r, R, dr;
	void scan() {
		scanf("%d %d %d", &h, &r, &R);
		dr = R - r;
	}
} glass[12];
int n;
double h[12];

double calc(const Glass& down, const Glass& up) {
	if (up.r >= down.R) return down.h;
	if (up.dr * down.h <= up.h * down.dr) {
		if (up.r <= down.r) return 0;
		// (up.r - down.r)/x = down.dr / down.h
		return (1. * (up.r - down.r)) * down.h / down.dr;
	}
	if (up.h <= down.h && (1. * down.dr) / down.h * up.h + down.r >= up.R) {
		return 0;
	}
	if (down.R >= up.R) {
		// (up.R - down.r)/x = down.dr / down.h
		return (1. * (up.R - down.r)) * down.h / down.dr - up.h;
	}
	else {
		// (down.R - up.r)/x = up.dr / up.h
		return down.h - (1. * (down.R - up.r)) * up.h / up.dr;
	}
}

double calc(VI& V) {
	double ret = 0;
	for (int i = 0; i < n; i++) {
		h[i] = 0;
		for (int j = 0; j < i; j++) {
			double del_h = calc(glass[V[j]], glass[V[i]]);
			h[i] = MAX(h[i], h[j] + del_h);
		}
		ret = MAX(ret, h[i] + glass[V[i]].h);
	}
	return ret;
}

void solve() {
	VI V;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		glass[i].scan();
		V.push_back(i);
	}

	double ans = 1e100;
	do {
		double now = calc(V);
		ans = MIN(ans, now);
	} while (next_permutation(ALL(V)));
	printf("%d\n", int(ans));
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