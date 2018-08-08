// Once you figure out the distance formula is: max(|deltax|, |deltay|)
// then rest is easy. You need to do sweep line along diagonal axis, and 
// need to keep 4 bit / segment tree.
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

LL tree[4][100005];
int cnt[4][100005];

//return cf[idx]
pair<LL, LL> read(int id, int idx)
{
	LL sum = 0;
	int ret = 0;

	while (idx > 0)
	{
		sum += tree[id][idx];
		ret += cnt[id][idx];
		idx -= (idx & -idx);
	}

	return { sum, ret };
}

//add val to f[idx].
//MaxVal = Just max value of index
void update(int id, int idx, int val, int add_delete)
{
	while (idx <= 100000)
	{
		tree[id][idx] += val;
		cnt[id][idx] += add_delete;
		idx += (idx & -idx);
	}
}

PII p[100005];
int n;
VI dia2;

bool cmp(PII A, PII B) {
	return A.first + A.second < B.first + B.second;
}

inline int ID(PII A) {
	int d2 = A.first - A.second;
	return lower_bound(ALL(dia2), d2) - dia2.begin() + 1;
}

LL process(PII A) {
	int idx = ID(A);
	update(0, idx, -A.second, -1);
	update(1, idx, -A.first, -1);

	LL ret = 0;
	{
		auto now = read(0, idx);
		ret += now.first - now.second * A.second;
	}
	{
		auto now1 = read(1, 100000);
		auto now2 = read(1, idx);
		pair<LL, LL> now = { now1.first - now2.first, now1.second - now2.second };
		ret += now.first - now.second * A.first;
	}
	{
		auto now = read(2, idx);
		ret += now.second * A.first - now.first;
	}
	{
		auto now1 = read(3, 100000);
		auto now2 = read(3, idx);
		pair<LL, LL> now = { now1.first - now2.first, now1.second - now2.second };
		ret += now.second * A.second - now.first;
	}
	update(3, idx, A.second, +1);
	update(2, idx, A.first, +1);
	return ret;
}

// \ y0 /
//  \  /
// x2\/  x1
//   /\
//  /  \
// / y3 \ 

int main()
{
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
	//	freopen("out.out", "w", stdout);
#endif
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &p[i].first, &p[i].second);
		//p[i].first = rand() * rand();
		//p[i].second = rand() * rand();
		dia2.push_back(p[i].first - p[i].second);
	}
	sort(ALL(dia2));
	dia2.erase(unique(ALL(dia2)), dia2.end());
	sort(p, p + n, cmp);

	for (int i = 0; i < n; i++) {
		int idx = ID(p[i]);
		update(0, idx, p[i].second, +1);
		update(1, idx, p[i].first, +1);
	}

	LL ans = 1000000000000000000LL;
	for (int i = 0; i < n; i++) {
		LL now = process(p[i]);
		ans = MIN(ans, now);
	}
	printf("%lld\n", ans);
	return 0;
}
