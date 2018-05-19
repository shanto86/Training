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
#define SQ(X) ( (X) * (X) )
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

// BEGIN CUT HERE
vector<string> split( const string& s, const string& delim =" " ) {
    vector<string> res;
    string t;
    for ( int i = 0 ; i != s.size() ; i++ ) {
        if ( delim.find( s[i] ) != string::npos ) {
            if ( !t.empty() ) {
                res.push_back( t );
                t = "";
            }
        } else {
            t += s[i];
        }
    }
    if ( !t.empty() ) {
        res.push_back(t);
    }
    return res;
}

vector<int> splitInt( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<int> res;
    for ( int i = 0 ; i != tok.size(); i++ )
        res.push_back( atoi( tok[i].c_str() ) );
    return res;
}

#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))

template<typename T> void print( T a ) {
    cerr << a;
}
static void print( long long a ) {
    cerr << a << "L";
}
static void print( string a ) {
    cerr << '"' << a << '"';
}
template<typename T> void print( vector<T> a ) {
    cerr << "{";
    for ( int i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}
template<typename T> void eq( int n, T have, T need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
template<typename T> void eq( int n, vector<T> have, vector<T> need ) {
    if( have.size() != need.size() ) {
        cerr << "Case " << n << " failed: returned " << have.size() << " elements; expected " << need.size() << " elements.";
        print( have );
        print( need );
        return;
    }
    for( int i= 0; i < have.size(); i++ ) {
        if( have[i] != need[i] ) {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
// END CUT HERE

//typedef int LL;
typedef long long int LL;
//typedef __int64 LL;

LL fib[40];
set<LL> masks;
map<int, int> M;

void check(LL x, LL y) {
	if (x <= 0 || x > 100000000) return;
	if (y <= 0 || y > 100000000) return;
	//if (x > y) return;

	LL mask = 0;
	if (M.find(x) != M.end()) mask |= (1LL << M[x]);
	masks.insert(mask);
	if (x < y && M.find(y) != M.end()) mask |= (1LL << M[y]);
	masks.insert(mask);
	while (true) {
		LL z = x + y;
		if (z > 100000000) break;
		if (M.find(z) != M.end()) mask |= (1LL << M[z]);
		masks.insert(mask);
		x = y;
		y = z;
	}
}

void check(LL a, LL b, LL p, LL q) {
	if (p == 0 && q == 1) {
		check(a, b);
		return;
	}
	if (p == 0) {
		// 2: fib[0], fib[1]
		// 3: fib[1], fib[2]
		// q: fib[q - 2], fib[q - 1]
		// b = fib[q - 2] * a + fib[q- 1]*x
		LL x = (b - fib[q - 2] * a) / fib[q - 1];
		if (b != fib[q - 2] * a + fib[q - 1] * x) return;
		check(a, x);
		return;
	}
	if (p == 1) {
		// 2: fib[0], fib[1]
		// 3: fib[1], fib[2]
		// q: fib[q - 2], fib[q - 1]
		// b = fib[q - 2] * x + fib[q- 1]*a
		LL x = (b - fib[q - 1] * a) / fib[q - 2];
		if (b != fib[q - 1] * a + fib[q - 2] * x) return;
		check(x, a);
		return;
	}
	// fib[p - 2] * x + fib[p - 1] * y - a = 0
	// fib[q - 2] * x + fib[q - 1] * y - b = 0
	LL d = fib[p - 2] * fib[q - 1] - fib[p - 1] * fib[q - 2];
	LL x = (fib[p - 1] * -b - fib[q - 1] * -a) / d;
	LL y = fib[q - 2] * -a - fib[p - 2] * -b;
	if (a != fib[p - 2] * x + fib[p - 1] * y) return;
	if (b != fib[q - 2] * x + fib[q - 1] * y) return;
	check(x, y);
}

class SubFibonacci {
public:
    int maxElements(vector <int> S) {
		fib[0] = 1;
		fib[1] = 1;
		for (int i = 2; i <= 39; i++) fib[i] = fib[i - 1] + fib[i - 2];
		sort(ALL(S));
		M.clear();
		for (int i = 0; i < SZ(S); i++) {
			M[S[i]] = i;
		}
		masks.clear();
		for (int i = 0; i < SZ(S); i++) {
			masks.insert(1LL << i);
			for (int j = i + 1; j < SZ(S); j++) {
				for (int p = 0; p < 40; p++) {
					for (int q = p + 1; q < 40; q++) {
						check(S[i], S[j], p, q);
					}
				}
			}
		}

		int ans = 1;
		masks.erase(0);
		for (LL i : masks) {
			LL x = i, jj = 0, last = -1;
			//printf("%lld: ", i);
			while (x) {
				if (x & 1) {
					last = jj;
					//printf("%d ", S[jj]);
				}
				x >>= 1;
				jj++;
			}
			//printf("\n");

			for (LL j : masks) {
				LL x = j, jj = 0, first = -1;
				while (x) {
					if (x & 1) {
						first = jj;
						break;
					}
					x >>= 1;
					jj++;
				}

				if (last >= first) continue;

				x = i | j;
				int now = 0;
				while (x) {
					now += x & 1;
					x >>= 1;
				}
				if (now == 11) printf(">>>%lld %lld\n", i, j);
				ans = MAX(now, ans);
			}
		}
		return ans;
    }

};

// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
	{
		int SARRAY[] = { 104, 77, 181, 258, 439, 704, 1139, 1843, 2982, 4825, 451, 730, 1181, 1911, 3092, 5003 };
		vector <int> S(SARRAY, SARRAY + ARRSIZE(SARRAY));
		SubFibonacci theObject;
		eq(0, theObject.maxElements(S), 10);
	}
	{
        int SARRAY[] = {8, 1, 20, 3, 10};
        vector <int> S( SARRAY, SARRAY+ARRSIZE(SARRAY) );
        SubFibonacci theObject;
        eq(0, theObject.maxElements(S),5);
    }
    {
        int SARRAY[] = {19, 47, 50, 58, 77, 99};
        vector <int> S( SARRAY, SARRAY+ARRSIZE(SARRAY) );
        SubFibonacci theObject;
        eq(1, theObject.maxElements(S),4);
    }
    {
        int SARRAY[] = {512};
        vector <int> S( SARRAY, SARRAY+ARRSIZE(SARRAY) );
        SubFibonacci theObject;
        eq(2, theObject.maxElements(S),1);
    }
    {
        int SARRAY[] = {3, 5, 7, 10, 13, 15, 20, 90};
        vector <int> S( SARRAY, SARRAY+ARRSIZE(SARRAY) );
        SubFibonacci theObject;
        eq(3, theObject.maxElements(S),7);
    }
    {
        int SARRAY[] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
        vector <int> S( SARRAY, SARRAY+ARRSIZE(SARRAY) );
        SubFibonacci theObject;
        eq(4, theObject.maxElements(S),10);
    }
}
// END CUT HERE
