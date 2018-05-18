/*
Cumulative sum approach. First rotate the grid, and then
scan the whole grid, and see how many points are
inside the 2m*2m grid centering at the grid points.
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

int grid[2005][2005];
int dx, dy, n, q, m;
VP Points;

void solve2() {
	CLR(grid);
	for (int i = 0; i < n; i++) {
		int x = Points[i].first;
		int y = Points[i].second;
		grid[x + y][x - y + 1000]++;
	}
	for (int i = 2; i <= dx + dy; i++) {
		for (int j = 1 - dy + 1000; j <= dx - 1 + 1000; j++) {
			grid[i][j] += grid[i - 1][j] + grid[i][j - 1] - grid[i - 1][j - 1];
		}
	}

	int final_ans = 0, final_x = 1, final_y = 1;
	for (int j = 1; j <= dy; j++) {
		for (int i = 1; i <= dx; i++) {
			int lx = i + j - m, ux = i + j + m;
			int ly = i - j - m, uy = i - j + m;
			lx = MAX(lx, 2); ux = MIN(ux, dx + dy);
			ly = MAX(ly, 1 - dy); uy = MIN(uy, dx - 1);

			int sum = grid[ux][uy + 1000] - grid[ux][ly - 1 + 1000] - grid[lx - 1][uy + 1000] + grid[lx - 1][ly - 1 + 1000];
			if (final_ans < sum) {
				final_ans = sum;
				final_x = i;
				final_y = j;
			}
		}
	}
	printf("%d (%d,%d)\n", final_ans, final_x, final_y);
}

int ks = 0;
int solve() {
	scanf("%d %d %d %d", &dx, &dy, &n, &q);
	if (dx == 0) return 0;
	printf("Case %d:\n", ++ks);
	Points.clear();
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		Points.push_back({ x, y });
	}
	for (int i = 1; i <= q; i++) {
		scanf("%d", &m);
		solve2();
	}
	return 1;
}

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif
	while (solve());

	return 0;
}