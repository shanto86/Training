/*
Main idea is to, divide the plane by vertical lines through
circles' extreme x's and intersections. And then sweep line vertically.
*/
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

#define eps 1e-8
struct point { double x, y; };

double xmult(point p1, point p2, point p0) {
	return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
}
double Distance(point p1, point p2) {
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
double disptoline(point p, point l1, point l2) {
	return fabs(xmult(p, l1, l2)) / Distance(l1, l2);
}
point intersection(point u1, point u2, point v1, point v2) {
	point ret = u1;
	double t = ((u1.x - v1.x)*(v1.y - v2.y) - (u1.y - v1.y)*(v1.x - v2.x))
		/ ((u1.x - u2.x)*(v1.y - v2.y) - (u1.y - u2.y)*(v1.x - v2.x));
	ret.x += (u2.x - u1.x)*t;
	ret.y += (u2.y - u1.y)*t;
	return ret;
}

int intersect_line_circle(point c, double r, point l1, point l2) {
	return disptoline(c, l1, l2)<r + eps;
}

int intersect_seg_circle(point c, double r, point l1, point l2) {
	double t1 = Distance(c, l1) - r, t2 = Distance(c, l2) - r;
	point t = c;
	if (t1<eps || t2<eps)
		return t1>-eps || t2>-eps;
	t.x += l1.y - l2.y;
	t.y += l2.x - l1.x;
	return xmult(l1, c, t)*xmult(l2, c, t)<eps&&disptoline(c, l1, l2) - r<eps;
}

int intersect_circle_circle(point c1, double r1, point c2, double r2) {
	return Distance(c1, c2)<r1 + r2 + eps&&Distance(c1, c2)>fabs(r1 - r2) - eps;
}

point dot_to_circle(point c, double r, point p) {
	point u, v;
	if (Distance(p, c)<eps)
		return p;
	u.x = c.x + r*fabs(c.x - p.x) / Distance(c, p);
	u.y = c.y + r*fabs(c.y - p.y) / Distance(c, p)*((c.x - p.x)*(c.y - p.y)<0 ? -1 : 1);
	v.x = c.x - r*fabs(c.x - p.x) / Distance(c, p);
	v.y = c.y - r*fabs(c.y - p.y) / Distance(c, p)*((c.x - p.x)*(c.y - p.y)<0 ? -1 : 1);
	return Distance(u, p)<Distance(v, p) ? u : v;
}

void intersection_line_circle(point c, double r, point l1, point l2, point& p1, point& p2) {
	point p = c;
	double t;
	p.x += l1.y - l2.y;
	p.y += l2.x - l1.x;
	p = intersection(p, c, l1, l2);
	t = sqrt(r*r - Distance(p, c)*Distance(p, c)) / Distance(l1, l2);
	p1.x = p.x + (l2.x - l1.x)*t;
	p1.y = p.y + (l2.y - l1.y)*t;
	p2.x = p.x - (l2.x - l1.x)*t;
	p2.y = p.y - (l2.y - l1.y)*t;
}

void intersection_circle_circle(point c1, double r1, point c2, double r2, point& p1, point& p2) {
	point u, v;
	double t;
	t = (1 + (r1*r1 - r2*r2) / Distance(c1, c2) / Distance(c1, c2)) / 2;
	u.x = c1.x + (c2.x - c1.x)*t;
	u.y = c1.y + (c2.y - c1.y)*t;
	v.x = u.x + c1.y - c2.y;
	v.y = u.y - c1.x + c2.x;
	intersection_line_circle(c1, r1, u, v, p1, p2);
}
struct Event {
	int id;
	double y;
	int u;

	bool operator<(const Event& E) const {
		if (y != E.y) return y < E.y;
		if (u != E.u) return u < E.u;
		return id < E.id;
	}
};
point p[103];
double r[103];
int n;
int vis[103];

void solve() {
	set<double> Xs;
	for (int i = 0; i < n; i++) {
		Xs.insert(p[i].x - r[i]);
		Xs.insert(p[i].x + r[i]);
		for (int j = i + 1; j < n; j++) {
			point a, b;
			if (!intersect_circle_circle(p[i], r[i], p[j], r[j])) continue;
			intersection_circle_circle(p[i], r[i], p[j], r[j], a, b);
			Xs.insert(a.x);
			Xs.insert(b.x);
		}
	}

	double prev_x = -100;
	for (double x : Xs) {
		if (prev_x < -50) {
			prev_x = x;
			continue;
		}

		double mid = (prev_x + x) / 2.;
		vector<Event> E;
		for (int i = 0; i < n; i++) {
			if (!IN(mid, p[i].x - r[i], p[i].x + r[i])) continue;
			E.push_back({ i, p[i].y - sqrt(S(r[i]) - S(mid - p[i].x)), +1 });
			E.push_back({ i, p[i].y + sqrt(S(r[i]) - S(mid - p[i].x)), -1 });
		}
		sort(ALL(E));
		set<int, greater<int>> Ids;
		for (auto& e : E) {
			if (e.u == +1) Ids.insert(e.id);
			else Ids.erase(e.id);
			if (!Ids.empty()) vis[*Ids.begin()] = 1;
		}

		prev_x = x;
	}
}

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif

	while (scanf("%d", &n) != EOF) {
		if (!n) break;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf", &p[i].x, &p[i].y, &r[i]);
		}
		CLR(vis);
		solve();
		int ans = 0;
		for (int i = 0; i < n; i++) ans += vis[i];
		printf("%d\n", ans);
	}
	return 0;
}