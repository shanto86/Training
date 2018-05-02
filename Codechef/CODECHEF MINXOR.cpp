// Idea easy-medium, code quite is a bit complex. Once you think 
// about applying sqrt decomposition, rest is standard use case of trie/xor 
// which is common problem.
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

typedef pair<int, int> PII;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;

//typedef int LL;
typedef long long int LL;
//typedef __int64 LL;

void update(PII& ans, PII now) {
	if (ans.first > now.first) {
		ans = now;
	}
	else if (ans.first == now.first) {
		ans.second += now.second;
	}
}

struct Block {
	int trie[500 * 16 + 10][2];
	int cnt[500 * 16 + 10];
	int dirty;
	int global;
	int id;
	VI num;

	void insert(int x, int z = 1) {
		if (z) {
			num.push_back(x);
		}
		int at = 0;
		cnt[at]++;
		for (int i = 15; i >= 0; i--) {
			int bit = (x & (1 << i)) > 0;
			if (trie[at][bit] == -1) {
				trie[at][bit] = ++id;
				trie[id][0] = trie[id][1] = -1;
				cnt[id] = 0;
			}
			at = trie[at][bit];
			cnt[at]++;
		}
	}

	PII whole_block_query() {
		if (dirty) {
			id = 0;
			trie[0][0] = trie[0][1] = -1;
			cnt[0] = 0;
			for (int j = 0; j < num.size(); j++) {
				num[j] ^= global;
				insert(num[j], 0);
			}
			dirty = global = 0;
		}

		int at = 0;
		int ret = 0;
		for (int i = 15; i >= 0; i--) {
			int bit = (global & (1 << i)) > 0;
			ret <<= 1;
			if (trie[at][bit] != -1) {
				at = trie[at][bit];
				ret |= bit;
			}
			else {
				at = trie[at][bit ^ 1];
				ret |= bit ^ 1;
			}
		}
		return PII(ret ^ global, cnt[at]);
	}

	PII inside_query(int l, int r) {
		PII ret(1000000, 0);
		for (int i = l; i <= r; i++) {
			update(ret, { num[i] ^ global, 1 });
		}
		return ret;
	}
}block[502];

int num[250003];

const int BLOCK_SZ = 500;

int main() {
#ifdef LOCAL
	freopen("C:\\Home\\ContestCodes\\input.in", "r", stdin);
#endif
	int n, q;
	scanf("%d %d", &n, &q);
	//n = 250000, q = 50000;
	for (int i = 0; i < n; i++) {
		scanf("%d", &num[i]);
		//num[i] = rand() % 65536;
	}

	for (int i =0, k = 0; i < n; i+=BLOCK_SZ, k++) {
		block[k].dirty = block[k].global = block[k].id = 0;
		block[k].trie[0][0] = block[k].trie[0][1] = -1;
		block[k].cnt[0] = 0;
		for (int j = 0; j < BLOCK_SZ && i + j < n; j++) {
			block[k].insert(num[i + j]);
		}
	}

	for (int i = 0; i < q; i++) {
		int type, l, r, k;
		scanf("%d %d %d", &type, &l, &r);
		//type = rand() % 2 + 1;
		//l = rand() % n + 1;
		//r = rand() % n + 1;
		//if (l > r) swap(l, r);
		l--, r--;
		if (type == 2) {
			scanf("%d", &k);
			//k = rand() % 65536;
		}

		if (type == 1) {
			PII ans = { 100000, 0 };
			for (int i = 0, q = 0; i < n; i += BLOCK_SZ, q++) {
				int last = i + BLOCK_SZ - 1;
				last = MIN(last, n - 1);
				PII now;
				if (last < l || r < i) continue;
				else if (l <= i && last <= r) {
					now = block[q].whole_block_query();
				}
				else {
					now = block[q].inside_query(MAX(l, i) - i,
						MIN(r, last) - i);
				}
				update(ans, now);
			}
			printf("%d %d\n", ans.first, ans.second);
		}
		else {
			for (int i = 0, q = 0; i < n; i += BLOCK_SZ, q++) {
				int last = i + BLOCK_SZ - 1;
				last = MIN(last, n - 1);

				if (last < l || r < i) continue;
				else if (l <= i && last <= r) {
					block[q].global ^= k;
				}
				else {
					block[q].dirty = 1;
					for (int x = MAX(l, i); x <= MIN(r, last); x++) {
						int y = x - i;
						block[q].num[y] ^= k;
					}
				}
			}
		}
	}
	return 0;
}
