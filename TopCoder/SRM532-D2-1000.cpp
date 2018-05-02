// Bitmask dp. Just think about going row by row and keep the states:
// 0- did not put block, 1-put block but odd, 2-put block but even.
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
#include <cctype>
using namespace std;

#define MEM(a, b) memset(a, (b), sizeof(a))
#define CLR(a) memset(a, 0, sizeof(a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(X) ( (X) > 0 ? (X) : ( -(X) ) )
#define S(X) ( (X) * (X) )
#define SZ(V) (int )V.size()
#define FORN(i, n) for(i = 0; i < n; i++)
#define FORAB(i, a, b) for(i = a; i <= b; i++)
#define ALL(V) V.begin(), V.end()
#define IN(A, B, C)  ((B) <= (A) && (A) <= (C))

typedef pair<int,int> PII;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

#define AIN(A, B, C) assert(IN(A, B, C))


//typedef int LL;
typedef long long int LL;
//typedef __int64 LL;
int n, m;
// 0 = no, 1 = has but odd, 2 = has but even
LL dp[7000][102][8];
const LL MOD = 1000000007;

int MASK(VI& V) {
	int ret = 0;
	for (int i = SZ(V) - 1; i >= 0; i--) {
		ret = ret * 3 + V[i];
	}
	return ret;
}

LL DP(int mask, int row, int col) {
	if (col == m) {
		return DP(mask, row + 1, 0);
	}
	LL& ret = dp[mask][row][col];
	if (ret != -1) return ret;
	if (row == n) {
		for (int i = 0; i < m; i++) {
			int now = mask % 3;
			mask /= 3;
			if (now == 1) return ret = 0;
		}
		return ret = 1;
	}

	ret = 0;

	VI V;
	for (int i = 0; i < m; i++) {
		V.push_back(mask % 3);
		mask /= 3;
	}

	// don't place
	if (V[col] != 1) {
		VI W = V;
		W[col] = 0;
		ret += DP(MASK(W), row, col + 1);
	}

	if (V[col] != 2) {
		VI W = V;
		if (col) {
			if (W[col - 1] == 1) W[col - 1] = 2;
			else if (W[col - 1] == 2) W[col - 1] = 1;
		}
		int cnt = (col ? W[col - 1] > 0 : 0)
			+ (W[col] > 0);
		W[col] = ((cnt&1) ? 1 : 2);
		ret += DP(MASK(W), row, col + 1);
	}
	ret %= MOD;
	return ret;
}
class DengklekPaintingSquares {
public:
    int numSolutions(int N, int M) {
    n = N, m = M;
    MEM(dp, -1);
    return DP(0, 0, 0);
    }

};



// Powered by FileEdit
// Powered by CodeProcessor