/*
Line sweep from left to right. Maintain a set.
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

struct Seg {
	int xx1, yy1, xx2, yy2, id;
	void scan(int _id) {
		id = _id;
		scanf("%d %d %d %d", &xx1, &yy1, &xx2, &yy2);
	}
	pair<LL, LL> eval(LL qx) const {
		return{ yy1 * (1LL * xx2 - xx1) + (yy2 - yy1)  * (qx - xx1), (xx2 - xx1) };
	}
};

int qx;
struct Cmp {
	bool operator()(const Seg* A, const Seg* B) const {
		pair<LL, LL> yA = A->eval(qx), yB = B->eval(qx);
		return yA.first * yB.second > yB.first * yA.second;
	}
};
struct Event {
	int id, status, pos, y, low;
	bool operator<(const Event& e) const {
		if (pos != e.pos) return pos < e.pos;
		if (status != e.status) return status > e.status;
		if (status == +1) {
			return y < e.y;
		}
		else {
			return y > e.y;
		}
	}
};
Seg seg[40004];
int nxt[40004];
int rain[40004];
int deg[40004];
int n;

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			nxt[i] = -1;
			rain[i] = 0;
			deg[i] = 0;
			seg[i].scan(i);
		}
		vector<Event> events;
		for (int i = 0; i < n; i++) {
			events.push_back({ i, +1, seg[i].xx1, seg[i].yy1, seg[i].yy1 < seg[i].yy2 });
			events.push_back({ i, -1, seg[i].xx2, seg[i].yy2, seg[i].yy1 > seg[i].yy2 });
		}
		sort(ALL(events));
		set<Seg*, Cmp> S;

		int prev = -1;
		for (int i = 0; i < SZ(events);) {
			int now = events[i].pos;
			qx = now;
			if (!S.empty()) {
				rain[(*S.begin())->id] += now - prev;
			}
			while (i < SZ(events) && events[i].pos == now) {
				int id = events[i].id;
				if (events[i].status == +1) {
					S.insert(&seg[id]);
				}
				if (events[i].low) {
					set<Seg*, Cmp>::iterator iS = S.find(&seg[id]);
					iS++;
					if (iS != S.end()) {
						nxt[id] = (*iS)->id;
						deg[nxt[id]]++;
					}
				}
				if (events[i].status == -1) {
					S.erase(&seg[id]);
				}
				i++;
			}
			prev = qx;
		}

		queue<int> Q;
		for (int i = 0; i < n; i++) {
			if (deg[i] == 0) {
				Q.push(i);
			}
		}
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();

			if (nxt[u] == -1) continue;
			deg[nxt[u]]--;
			if (deg[nxt[u]] == 0) Q.push(nxt[u]);
			rain[nxt[u]] += rain[u];
		}

		for (int i = 0; i < n; i++) {
			//printf("%d: %d %d %d %d -> %d\n", i, seg[i].xx1, seg[i].yy1, seg[i].xx2, seg[i].yy2, nxt[i]);
			printf("%d\n", rain[i]);
		}
	}
	return 0;
}