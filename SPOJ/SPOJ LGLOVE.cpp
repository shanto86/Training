// Segment tree for operations (min/max/lazy).
// Used priority queue for finding lcm by keeping track
// of highest power of primes.
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

typedef pair<LL, LL> PII;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

int num[100005];
PII q[4 * 100005];
LL lazy[4 * 100005];
int n, m;

void build(int at, int l, int r) {
	if (l == r) {
		q[at] = PII(num[l], num[r]);
		return;
	}
	int m = (l + r) / 2;
	build(at * 2, l, m);
	build(at * 2 + 1, m + 1, r);
	q[at].first = MAX(q[at * 2].first, q[at * 2 + 1].first);
	q[at].second = MIN(q[at * 2].second, q[at * 2 + 1].second);
}

void add(int at, int l, int r, int L, int R, int k) {
	if (L <= l && r <= R) {
		lazy[at] += k;
		q[at].first += k;
		q[at].second += k;
		return;
	}

	if (R < l || r < L) return;
	int m = (l + r) / 2;
	add(at * 2, l, m, L, R, k);
	add(at * 2 + 1, m + 1, r, L, R, k);
	q[at].first = lazy[at] + MAX(q[at * 2].first, q[at * 2 + 1].first);
	q[at].second = lazy[at] + MIN(q[at * 2].second, q[at * 2 + 1].second);
}

PII query(int at, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		return q[at];
	}

	if (R < l || r < L) return{ -1000000000000000LL, 1000000000000000LL };
	int m = (l + r) / 2;
	PII a = query(at * 2, l, m, L, R);
	PII b = query(at * 2 + 1, m + 1, r, L, R);
	PII c;
	c.first = lazy[at] + MAX(a.first, b.first);
	c.second = lazy[at] + MIN(a.second, b.second);
	return c;
}

vector<int> Prime;
int mark[300005];

void sieve(int n)
{
	int i, j, limit = sqrt(n*1.) + 2;

	mark[1] = 1;
	for (i = 4; i <= n; i += 2) mark[i] = 1;

	Prime.push_back(2);
	for (i = 3; i <= n; i += 2)
		if (!mark[i])
		{
			Prime.push_back(i);

			if (i <= limit)
			{
				for (j = i*i; j <= n; j += i * 2)
				{
					mark[j] = 1;
				}
			}
		}
}

struct PIIS {
	LL first, second;
	PIIS(LL a, LL b) {
		first = a;
		second = b;
	}
};
bool operator<(PIIS A, PIIS B) {
	return A.first > B.first;
}
LL lcm[300005];
int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif
	sieve(300000);
	priority_queue<PIIS> PQ;
	for (int i : Prime) PQ.push(PIIS(i, i));
	LL now = 1;
	lcm[1] = 1;
	for (int i = 2; i <= 300000; i++) {
		lcm[i] = lcm[i - 1];
		while (PQ.top().first <= i) {
			PIIS x = PQ.top(); PQ.pop();
			lcm[i] = (lcm[i] * x.second) % 1000000007;
			x.first = ((1LL * x.first) * x.second);
			PQ.push(x);
		}
	}
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &num[i]);
	}
	build(1, 0, n - 1);
	for (int i = 0; i < m; i++) {
		int id, l, r, k;
		scanf("%d %d %d", &id, &l, &r);
		if (id == 0) scanf("%d", &k);

		if (id == 0) add(1, 0, n - 1, l, r, k);
		else {
			PII now = query(1, 0, n - 1, l, r);
			int ans = (id == 1 ? now.first : now.second);
			printf("%lld\n", lcm[ans]);
		}
	}
	return 0;
}