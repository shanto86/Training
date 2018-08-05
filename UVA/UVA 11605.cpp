// First find the probability of a cell being inside K-parallelopid, sum those up.
// To find such probability, find the probability, of a cell being inside parallelopid
// only once. Then applying binaomial theorem, we can compute, what;s the probability
// of that cell being inside K-parallelopids odd times.
// To find the probability of (i, j, k) in one single parallelopid, multiply
// the probability that i being inside [x1, x2], which is simple math.
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
#define FORN(i, n) for(i = 0; i < n; i++)
#define FORAB(i, a, b) for(int i = a; i <= b; i++)
#define ALL(V) V.begin(), V.end()
#define IN(A, B, C)  ((B) <= (A) && (A) <= (C))
#define AIN(A, B, C) assert(IN(A, B, C))

typedef pair<int,int> PII;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

//typedef int LL;
typedef long long int LL;
//typedef __int64 LL;

double Calc(int i, int N, int K) {
	double q = S(i - 1) + S(N - i);
	q /= S(N);
	double p = 1. - q;
	return p;
}

int main()
{
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
	//	freopen("out.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	FORAB(ks, 1, T) {
		int N, M, P, K;
		scanf("%d %d %d %d", &N, &M, &P, &K);

		double ans = 0;
		FORAB(i, 1, N) {
			double p1 = Calc(i, N, K);
			FORAB(j, 1, M) {
				double p2 = Calc(j, M, K);
				FORAB(l, 1, P) {
					double p3 = Calc(l, P, K);
					double p = p1 * p2 * p3;
					double q = 1 - p;
					double now = (1 - pow(q - p, K)) / 2.;
					ans += now;

				}
			}
		}
		printf("Case %d: %.10lf\n", ks, ans);
	}
	return 0;
}
