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
typedef pair<long double, long double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

// x^2 + y^2 = r^2
// (x-x0)^2 + (y-y0)^2 = r0^2
// 2xx0 + 2yy0 = x0^2 + y0^2 - r0^2
// x = (Z - Yy)
// Z^2 - 2YZy + Y^2y^2 + y^2 = r^2
const double eps = 1e-8;
struct Point {
	double x, y;
};

inline bool operator<(const Point& lhs, const Point& rhs) {
	if (fabs(lhs.x - rhs.x) > 1e-8) {
		return lhs.x < rhs.x;
	}
	else if (fabs(lhs.y - rhs.y) > 1e-8) {
		return lhs.y < rhs.y;
	}
	else {
		return false;
	}
}

inline double sqr(double x) {
	return x * x;
}

inline double dis(const Point& lhs, const Point& rhs) {
	return hypot(lhs.x - rhs.x, lhs.y - rhs.y);
}

// |dx'|   |dx|   |cosa -sina|
// |   | = |  | * |          |
// |dy'|   |dy|   |sina  cosa|

bool intersection(const Point& o1, double r1, const Point& o2, double r2, Point& p1, Point& p2) {
	double d = dis(o1, o2);
	if (d < fabs(r1 - r2) - eps || d > r1 + r2 + eps) {
		return false;
	}
	double cosa = (sqr(r1) + sqr(d) - sqr(r2)) / (2 * r1 * d);
	double sina = sqrt(max(0., 1. - sqr(cosa)));
	p1 = p2 = o1;
	p1.x += r1 / d * ((o2.x - o1.x) * cosa + (o2.y - o1.y) * -sina);
	p1.y += r1 / d * ((o2.x - o1.x) * sina + (o2.y - o1.y) * cosa);
	p2.x += r1 / d * ((o2.x - o1.x) * cosa + (o2.y - o1.y) * sina);
	p2.y += r1 / d * ((o2.x - o1.x) * -sina + (o2.y - o1.y) * cosa);
	return true;
}

Point p[52]; int r[52];
int w[52][52], vis[52];

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif
	freopen("circles.in", "r", stdin);
	freopen("circles.out", "w", stdout);

	int n;
	Point a, b;
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %d", &p[i].x, &p[i].y, &r[i]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) w[i][j] = 1;
				else {
					//w[i][j] = intersect_circle_circle(p[i], r[i], p[j], r[j]);
					w[i][j] = intersection(p[i], r[i], p[j], r[j], a, b);
				}
			}
		}
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					w[i][j] |= w[i][k] & w[k][j];
				}
			}
		}
		int comp = 0;
		int V = 0, E = 0;
		CLR(vis);
		for (int i = 0; i < n; i++) {
			if (vis[i]) continue;
			int zh = 0;
			for (int j = 0; j < n; j++) {
				if (w[i][j]) vis[j] = 1;
				zh += w[i][j];
			}
			if (zh == 1) V++, E++;
			comp++;
		}

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				//if (!intersect_circle_circle(p[i], r[i], p[j], r[j])) continue;
				//intersection_circle_circle(p[i], r[i], p[j], r[j], a, b);
				if (!intersection(p[i], r[i], p[j], r[j], a, b)) continue;

				int triA = 0, triB = 0;
				for (int k = 0; k < j; k++) {
					if (k == i) continue;
					if (fabs(S(p[k].x - a.x) + S(p[k].y - a.y) - S(r[k])) < eps) triA = 1;
					if (fabs(S(p[k].x - b.x) + S(p[k].y - b.y) - S(r[k])) < eps) triB = 1;
				}
				if (!triA) V++;
				int dd = S(p[i].x - p[j].x) + S(p[i].y - p[j].y);
				if (!triB && !(dd == S(r[i] + r[j]) || dd == S(r[i] - r[j]))) V++;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) continue;
				//if (!intersect_circle_circle(p[i], r[i], p[j], r[j])) continue;
				//intersection_circle_circle(p[i], r[i], p[j], r[j], a, b);
				if (!intersection(p[i], r[i], p[j], r[j], a, b)) continue;

				int triA = 0, triB = 0;
				for (int k = 0; k < j; k++) {
					if (i == k) continue;
					if (fabs(S(p[k].x - a.x) + S(p[k].y - a.y) - S(r[k])) < eps) triA = 1;
					if (fabs(S(p[k].x - b.x) + S(p[k].y - b.y) - S(r[k])) < eps) triB = 1;
				}
				if (!triA) E++;
				int dd = S(p[i].x - p[j].x) + S(p[i].y - p[j].y);
				if (!triB && !(dd == S(r[i] + r[j]) || dd == S(r[i] - r[j]))) E++;
			}
		}
		// V - E + F = 2
		int ans = 2 - V + E + comp - 1;
		printf("%d\n", ans);
	}
	return 0;
}