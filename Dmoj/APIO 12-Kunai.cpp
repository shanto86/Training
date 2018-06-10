/*
Main idea is like dijkstra, for each arrow
and all the direction, find the closest arrow that
it can hit. And put this pair in a priority queue.
Then pop the earliest arrow and remove them, also
insert new clashing arrows to PQ.
This will give how much time each arrow is alive.
Next we need to count how many cells are covered by these segments.
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
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

struct Arrow {
	// id = which arrow
	// val = value in the corresponding axis
	// x, y = initial pos.
	int id, val1, val2, dir;
	int x, y;

	bool operator<(const Arrow& A) const {
		if (val1 != A.val1) return val1 < A.val1;
		if (val2 != A.val2) return val2 < A.val2;
		if (x != A.x) return x < A.x;
		if (y != A.y) return y < A.y;
		return id < A.id;
	}
};

int n, w, h;
Arrow arrows[100005];
int active[100005];
// dir: 0 - right, 1 - up, 2 - left, 3 - down.
// axis: 0 - |, 1- -, 2 - \, 3 - /
// | -> First: left to right, then bottom to top
// - -> First: bottom to top, then left to right
// \ -> First: bottom left to top right, then bottom right to top left
// / -> First: bottom right to top left, then bottom left to top right
int sx[] = { 1, 0, 1, -1 };
int sy[] = { 0, 1, 1, 1 };

Arrow CreateArrow(int id, int axis) {
	return{ id,
		sx[axis] * arrows[id].x + sy[axis] * arrows[id].y,
		sx[axis ^ 1] * arrows[id].x + sy[axis ^ 1] * arrows[id].y,
		arrows[id].dir,
		arrows[id].x, arrows[id].y };
}

// dir, axis
set<Arrow> S[4][4];
struct ArrowPair {
	int id1, id2;
	double time;
	ArrowPair() {}
	ArrowPair(int i1, int i2, double _time) {
		id1 = i1;
		id2 = i2;
		if (id1 > id2) swap(id1, id2);
		time = _time;
	}

	bool operator<(const ArrowPair A) const {
		if (time != A.time) return time > A.time;
		if (id1 != A.id1) return id1 < A.id1;
		return id2 < A.id2;
	}
};

priority_queue<ArrowPair> PQ;
unordered_set<LL> Has;

int CheckAndInsert(set<Arrow>& S, int id, int val1, int val2, int comp, int action = 1) {
	Arrow temp; temp.val1 = val1, temp.val2 = val2;
	set<Arrow>::iterator iS = S.lower_bound(temp);
	if (comp == -1) {
		if (iS == S.begin()) return -1;
		iS--;
	}
	if (iS == S.end()) return -1;
	if (iS->val1 != val1) return -1;
	if (!action) return iS->id;
	// hori/verti: 0:1, 1:1.5, 2:2, 3:2.5, 4:3: dist/2 + 1
	// dia: 0:1, 2:2, 4:3, 6:4: dist/2 + 1
	int dist = ABS(iS->x - arrows[id].x) + ABS(iS->y - arrows[id].y);
	double t = dist / 2. + 1;

	int id1 = id;
	int id2 = iS->id;
	if (id1 > id2) swap(id1, id2);
	LL idd = 100000LL * id1 + id2;
	if (Has.find(idd) != Has.end()) return -1;
	Has.insert(idd);
	PQ.push(ArrowPair(id, iS->id, t));
	return -1;
}

void Insert(int id) {
	int p, q;
	if (arrows[id].dir == 0) {
		// right
		p = 1, q = 1 ^ p;
		CheckAndInsert(S[2][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1);
		p = 2, q = 1 ^ p;
		CheckAndInsert(S[1][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1);
		p = 3, q = 1 ^ p;
		CheckAndInsert(S[3][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1);
	}
	if (arrows[id].dir == 1) {
		// up
		p = 0, q = 1 ^ p;
		CheckAndInsert(S[3][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1);
		p = 2, q = 1 ^ p;
		CheckAndInsert(S[0][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1);
		p = 3, q = 1 ^ p;
		CheckAndInsert(S[2][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1);
	}
	if (arrows[id].dir == 2) {
		// left
		p = 1, q = 1 ^ p;
		CheckAndInsert(S[0][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1);
		p = 2, q = 1 ^ p;
		CheckAndInsert(S[3][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1);
		p = 3, q = 1 ^ p;
		CheckAndInsert(S[1][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1);
	}
	if (arrows[id].dir == 3) {
		// down
		p = 0, q = 1 ^ p;
		CheckAndInsert(S[1][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1);
		p = 2, q = 1 ^ p;
		CheckAndInsert(S[2][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1);
		p = 3, q = 1 ^ p;
		CheckAndInsert(S[0][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1);
	}
}

void GetNextIds(set<int>& NextIds, int id) {
	int p, q, r;
	if (arrows[id].dir == 0) {
		// right
		p = 1, q = 1 ^ p;
		r = CheckAndInsert(S[2][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1, 0);
		if (r != -1) NextIds.insert(r);
		p = 2, q = 1 ^ p;
		r = CheckAndInsert(S[1][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1, 0);
		if (r != -1) NextIds.insert(r);
		p = 3, q = 1 ^ p;
		r = CheckAndInsert(S[3][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1, 0);
		if (r != -1) NextIds.insert(r);
	}
	if (arrows[id].dir == 1) {
		// up
		p = 0, q = 1 ^ p;
		r = CheckAndInsert(S[3][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1, 0);
		if (r != -1) NextIds.insert(r);
		p = 2, q = 1 ^ p;
		r = CheckAndInsert(S[0][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1, 0);
		if (r != -1) NextIds.insert(r);
		p = 3, q = 1 ^ p;
		r = CheckAndInsert(S[2][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1, 0);
		if (r != -1) NextIds.insert(r);
	}
	if (arrows[id].dir == 2) {
		// left
		p = 1, q = 1 ^ p;
		r = CheckAndInsert(S[0][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1, 0);
		if (r != -1) NextIds.insert(r);
		p = 2, q = 1 ^ p;
		r = CheckAndInsert(S[3][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			1, 0);
		if (r != -1) NextIds.insert(r);
		p = 3, q = 1 ^ p;
		r = CheckAndInsert(S[1][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1, 0);
		if (r != -1) NextIds.insert(r);
	}
	if (arrows[id].dir == 3) {
		// down
		p = 0, q = 1 ^ p;
		r = CheckAndInsert(S[1][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1, 0);
		if (r != -1) NextIds.insert(r);
		p = 2, q = 1 ^ p;
		r = CheckAndInsert(S[2][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1, 0);
		if (r != -1) NextIds.insert(r);
		p = 3, q = 1 ^ p;
		r = CheckAndInsert(S[0][p],
			id,
			arrows[id].x * sx[p] + arrows[id].y * sy[p],
			arrows[id].x * sx[q] + arrows[id].y * sy[q],
			-1, 0);
		if (r != -1) NextIds.insert(r);
	}
}
int togo[100005];

set<int> SY;
vector<int> Y;
int seg[4 * 200005];

void update(int at, int l, int r, int x, int u) {
	if (l == r) {
		seg[at] += u;
		return;
	}
	int m = (l + r) / 2;
	if (x <= Y[m]) update(at * 2, l, m, x, u);
	else update(at * 2 + 1, m + 1, r, x, u);
	seg[at] += u;
}

int query(int at, int l, int r, int L, int R) {
	if (L <= Y[l] && Y[r] <= R) return seg[at];
	if (R < Y[l] || Y[r] < L) return 0;
	int m = (l + r) / 2;
	return query(at * 2, l, m, L, R) + query(at * 2 + 1, m + 1, r, L, R);
}

void process(vector<tuple<int, int, int>>& V) {
	vector<tuple<int, int, int>> ret;
	sort(ALL(V));
	for (int i = 0; i < SZ(V); ) {
		VP Z;
		int y = get<0>(V[i]);
		while (i < SZ(V) && y == get<0>(V[i])) {
			Z.push_back({ get<1>(V[i]), +1 });
			Z.push_back({ get<2>(V[i]) + 1, -1 });
			i++;
		}

		sort(ALL(Z));
		int cntr = 0;
		int start = -1;
		for (int j = 0; j < SZ(Z); ) {
			int cur = Z[j].first;
			while (j < SZ(Z) && Z[j].first == cur) {
				cntr += Z[j].second;
				j++;
			}
			if (start == -1 && cntr > 0) start = cur;
			else if (cntr == 0) {
				ret.push_back(make_tuple(y, start, cur - 1));
				start = -1;
			}
		}

	}
	V.swap(ret);
}

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif
	scanf("%d %d", &w, &h);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &arrows[i].x, &arrows[i].y, &arrows[i].dir);
		if (arrows[i].dir & 1) arrows[i].dir ^= 2;
		active[i] = 1;
		togo[i] = -1;
		for (int j = 0; j < 4; j++) {
			S[arrows[i].dir][j].insert(CreateArrow(i, j));
		}
	}

	for (int i = 0; i < n; i++) {
		Insert(i);
	}

	while (!PQ.empty()) {
		double tt = PQ.top().time;
		set<int> ArrowIds;
		while (!PQ.empty() && PQ.top().time == tt) {
			ArrowPair u = PQ.top();
			PQ.pop();
			//printf(">>>%d %d %.1lf\n", u.id1, u.id2, tt);
			if (!active[u.id1] || !active[u.id2]) continue;
			ArrowIds.insert(u.id1);
			ArrowIds.insert(u.id2);
			//printf("%d %d %.1lf\n", u.id1, u.id2, tt);
		}

		for (int id : ArrowIds) {
			active[id] = 0;
			togo[id] = tt;
			for (int j = 0; j < 4; j++) {
				S[arrows[id].dir][j].erase(CreateArrow(id, j));
			}
		}

		set<int> NextIds;
		for (int id : ArrowIds) {
			GetNextIds(NextIds, id);
		}
		for (int nextId : NextIds) {
			Insert(nextId);
		}
	}

	// dir: 0 - right, 1 - up, 2 - left, 3 - down.
	vector<tuple<int, int, int>> hori, vert;
	for (int i = 0; i < n; i++) {
		LL x, y;
		if (arrows[i].dir == 0) {
			y = arrows[i].y;
			x = (active[i] ? w : arrows[i].x + togo[i] - 1);
			x = MIN(x, w);
			hori.push_back(make_tuple(y, arrows[i].x, x));
			SY.insert(y);
		}
		if (arrows[i].dir == 2) {
			y = arrows[i].y;
			x = (active[i] ? 1 : arrows[i].x - togo[i] + 1);
			x = MAX(x, 1);
			hori.push_back(make_tuple(y, x, arrows[i].x));
			SY.insert(y);
		}
		if (arrows[i].dir == 1) {
			x = arrows[i].x;
			y = (active[i] ? h : arrows[i].y + togo[i] - 1);
			y = MIN(y, h);
			vert.push_back(make_tuple(x, arrows[i].y, y));
		}
		if (arrows[i].dir == 3) {
			x = arrows[i].x;
			y = (active[i] ? 1 : arrows[i].y - togo[i] + 1);
			y = MAX(y, 1);
			vert.push_back(make_tuple(x, y, arrows[i].y));
		}
	}

	process(hori);
	process(vert);

	LL ans = 0;

	for (int y : SY) Y.push_back(y);
	vector<tuple<int, int, int>> events;
	for (auto& a : hori) {
		events.push_back(make_tuple(get<1>(a), get<0>(a), +1));
		events.push_back(make_tuple(get<2>(a) + 1, get<0>(a), -1));
		ans += get<2>(a) - get<1>(a) + 1;
	}
	sort(ALL(events));
	sort(ALL(vert));
	int nn = SZ(Y);
	int j = 0;
	for (int i = 0; i < SZ(vert); i++) {
		while (j < SZ(events) && get<0>(events[j]) <= get<0>(vert[i])) {
			update(1, 0, nn - 1, get<1>(events[j]), get<2>(events[j]));
			j++;
		}
		int l = get<1>(vert[i]), r = get<2>(vert[i]);
		ans += r - l + 1;
		if (nn) ans -= query(1, 0, nn - 1, l, r);
	}

	printf("%lld\n", ans);
	/*
	for (int i = 0; i < n; i++) {
		printf("%d: %d %d\n", i, active[i], togo[i]);
	}
	*/
	
	return 0;
}