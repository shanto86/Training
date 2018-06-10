/*
Once we fix the top of the isosceles triangle,
there is a very subtle relationship among the other
two vertices of the triangle. If the top is at i,
then the sum of other two is: 2i or n+2i or 2i-n.
We can take advantage of this and compute FFT of
the polynomial twice (once for 0 and other for 1).
I used NTT so that I dont suffer any precision loss.
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
typedef pair<long double, long double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

char word[2000006];

//modular fft
LL powmod(LL a, LL b, LL m) {
	if (b == 0) return 1;
	LL x = powmod(a, b / 2, m);
	x = (x * x) % m;
	if (b & 1) x = (x * a) % m;
	return x;
}

const int mod = 7340033;
const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1 << 20;

void fft(vector<int> & a, bool invert) {
	int n = (int)a.size();

	for (int i = 1, j = 0; i<n; ++i) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		int wlen = invert ? root_1 : root;
		for (int i = len; i<root_pw; i <<= 1)
			wlen = int(wlen * 1ll * wlen % mod);
		for (int i = 0; i<n; i += len) {
			int w = 1;
			for (int j = 0; j<len / 2; ++j) {
				int u = a[i + j], v = int(a[i + j + len / 2] * 1ll * w % mod);
				a[i + j] = u + v < mod ? u + v : u + v - mod;
				a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
				w = int(w * 1ll * wlen % mod);
			}
		}
	}
	if (invert) {
		LL nrev = powmod(n, mod - 2, mod);
		//int nrev = reverse (n, mod);
		for (int i = 0; i<n; ++i)
			a[i] = int(a[i] * 1ll * nrev % mod);
	}
}

void multiply(const vector<int> & a, const vector<int> & b, vector<int> & res) {
	vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	size_t n = 1;
	while (n < max(a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize(n), fb.resize(n);

	fft(fa, false), fft(fb, false);
	for (size_t i = 0; i < n; ++i) {
		fa[i] = (fa[i] * 1LL * fb[i]) % mod;
	}
	fft(fa, true);

	res.resize(n);
	for (size_t i = 0; i < n; ++i)
		res[i] = fa[i];
}

LL solve() {
	LL ret = 0;
	int len = strlen(word);
	for (int i = 0; i < 2; i++) {
		VI A;
		for (int j = 0; j < len; j++) {
			A.push_back(word[j] == '0' + i);
		}
		VI B = A;
		VI C;
		multiply(A, B, C);
		for (int j = 0; j < len; j++) if (A[j]) {
			if (2 * j < SZ(C)) {
				ret += C[2 * j] - 1;
			}
			if (len + 2 * j < SZ(C)) {
				ret += C[len + 2 * j];
			}
			if (0 <= 2 * j - len && 2 * j - len < SZ(C)) {
				ret += C[2 * j - len];
			}
		}
		if (len % 2 == 0) {
			LL line = 0;
			for (int j = 0; j < len; j++) {
				if (A[j] && A[(j + len / 2) % len]) {
					line++;
				}
			}
			ret -= line;
		}
		if (len % 3 == 0) {
			LL equi = 0;
			for (int j = 0; j < len; j++) {
				if (A[j] && A[(j + len / 3) % len] && A[(j + len / 3 * 2) % len]) {
					equi++;
				}
			}
			equi /= 3;
			ret -= 4 * equi;
		}
	}
	return ret/2;
}
int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\sample.in", "r", stdin);
#endif
	int n;
	scanf("%d", &n);
	FORAB(ks, 1, n) {
		scanf("%s", word);
		LL ans = solve();
		printf("Case %d: %lld\n", ks, ans);
	}
	return 0;
}