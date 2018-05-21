/*
Tutorial: http://codeforces.com/blog/entry/57324
My Solution is a little bit different. I used regular dp. The idea is,
first partition the 1..10^9 range into segments such that each segment is 
totally in or totally out of all (li, ri). So there are at most 600 segments.
Now for each segment, we calculate the count as f(i). If you think, you will
notice, f(i) is a polynomial. Now representing polynomial in efficient way
might be tricky, because you need to perform sum[i = 1 to n] f(i).
The trick is, it will be easy to perform summation if you represent f(i)
as sum of falling factorial.
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

typedef vector<LL> VI;
LL inv[500];

const LL MOD = 998244353;
struct Seg {
	VI V;
	LL sum = 0;
};

void transform(VI& V, int a, int b) {
	V.push_back(0);
	for (int i = SZ(V) - 1; i >= 1; i--) {
		V[i] = (V[i - 1] * inv[i]) % MOD;
	}
	V[0] = 0;
}

LL eval(VI& V, int a, int b) {
	LL n = b - a + 2, sum = 0, p = 1;
	for (int i = 0; i < SZ(V); i++) {
		sum = (sum + p * V[i]) % MOD;
		p = (p * (n - i - 1)) % MOD;
	}
	return sum;
}

LL bigmod(LL a, LL b) {
	if (b == 0) return 1;
	LL x = bigmod(a, b / 2);
	x = (x * x) % MOD;
	if (b & 1) x = (x * a) % MOD;
	return x;
}

class IncreasingSequences {
public:
    int count(vector <int> L, vector <int> R) {
		inv[0] = 1;
		for (int i = 1; i < 500; i++) {
			inv[i] = bigmod(i, MOD - 2);
		}
		set<int> S;
		S.insert(0);
		S.insert(1);
		L.push_back(1000000001);
		R.push_back(1000000001);
		for (int l : L) S.insert(l);
		for (int r : R) S.insert(r + 1);
		VI V; for (int s : S) V.push_back(s);
		VP Z;
		for (int i = 1; i < SZ(V); i++) {
			Z.push_back(PII(V[i - 1], V[i] - 1));
		}

		vector<Seg> dp(SZ(Z));
		for (int i = 0; i < SZ(Z); i++) {
			dp[i].V = { i == 0 };
		}
		for (int i = 0; i < SZ(L); i++) {
			int l = L[i], r = R[i];
			LL runsum = 0;
			for (int j = 0; j < SZ(Z); j++) {
				transform(dp[j].V, Z[j].first, Z[j].second);
				LL now = eval(dp[j].V, Z[j].first, Z[j].second);
				dp[j].V[0] = (dp[j].V[0] + runsum) % MOD;
				runsum = (runsum + now) % MOD;
				int in = (l <= Z[j].first && Z[j].second <= r);
				if (!in) {
					dp[j].V = { 0 };
				}
			}
		}
		return eval(dp[SZ(Z) - 1].V, Z[SZ(Z) - 1].first, Z[SZ(Z) - 1].second);
    }
};

// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
	{
		int LARRAY[] = { 10, 30 };
		vector <int> L(LARRAY, LARRAY + ARRSIZE(LARRAY));
		int RARRAY[] = { 20, 40 };
		vector <int> R(RARRAY, RARRAY + ARRSIZE(RARRAY));
		IncreasingSequences theObject;
		eq(1, theObject.count(L, R), 121);
	}
	{
        int LARRAY[] = {1, 3, 1, 4};
        vector <int> L( LARRAY, LARRAY+ARRSIZE(LARRAY) );
        int RARRAY[] = {6, 5, 4, 6};
        vector <int> R( RARRAY, RARRAY+ARRSIZE(RARRAY) );
        IncreasingSequences theObject;
        eq(0, theObject.count(L, R),4);
    }
    {
        int LARRAY[] = {30, 10};
        vector <int> L( LARRAY, LARRAY+ARRSIZE(LARRAY) );
        int RARRAY[] = {40, 20};
        vector <int> R( RARRAY, RARRAY+ARRSIZE(RARRAY) );
        IncreasingSequences theObject;
        eq(2, theObject.count(L, R),0);
    }
    {
        int LARRAY[] = {4, 46, 46, 35, 20, 77, 20};
        vector <int> L( LARRAY, LARRAY+ARRSIZE(LARRAY) );
        int RARRAY[] = {41, 65, 84, 90, 49, 86, 88};
        vector <int> R( RARRAY, RARRAY+ARRSIZE(RARRAY) );
        IncreasingSequences theObject;
        eq(3, theObject.count(L, R),2470);
    }
    {
        int LARRAY[] = {1};
        vector <int> L( LARRAY, LARRAY+ARRSIZE(LARRAY) );
        int RARRAY[] = {1000000000};
        vector <int> R( RARRAY, RARRAY+ARRSIZE(RARRAY) );
        IncreasingSequences theObject;
        eq(4, theObject.count(L, R),1755647);
    }
}
// END CUT HERE
