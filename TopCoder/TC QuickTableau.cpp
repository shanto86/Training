/*
There is not many valid young table. So generate each of them and
find how many swaps required by finding number of cycles.
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

VI T, Z;
int used[18];
int res;
int where[18], vis[18];

void check() {
	for (int i = 0; i < 16; i++) {
		where[Z[i]] = i;
		vis[i] = 0;
	}
	int cycle = 0;
	for (int i = 0; i < 16; i++) {
		if (vis[i]) continue;
		while (true) {
			int j = where[T[i]];
			if (vis[j]) break;
			vis[j] = 1;
			i = j;
		}
		cycle++;
	}
	res = MIN(res, 16 - cycle);
}

void bktk(int at) {
	if (at == 16) {
		check();
		return;
	}

	int r = at / 4, c = at % 4;
	for (int i = 0; i < 16; i++) {
		if (used[i]) continue;
		int nr = r - 1, nc = c;
		if (nr >= 0 && Z[nr * 4 + nc] > i) continue;
		nr = r, nc = c - 1;
		if (nc >= 0 && Z[nr * 4 + nc] > i) continue;
		used[i] = 1;
		Z[at] = i;
		bktk(at + 1);
		used[i] = 0;
	}
}

class QuickTableau {
public:
    int numSwaps(vector <int> table) {
		T = table;
		for (int i = 0; i < 16; i++) T[i]--;
		res = 1000000;
		Z.resize(16);
		bktk(0);
		return res;
    }

};

// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        int tableARRAY[] = {
            1,  2,  3,  4,
            5,  6,  7,  8,
            9, 10, 11, 12,
           13, 14, 15, 16
           };
        vector <int> table( tableARRAY, tableARRAY+ARRSIZE(tableARRAY) );
        QuickTableau theObject;
        eq(0, theObject.numSwaps(table),0);
    }
    {
        int tableARRAY[] = {
           16, 15, 14, 13,
           12, 11, 10,  9,
            8,  7,  6,  5,
            4,  3,  2,  1
           };
        vector <int> table( tableARRAY, tableARRAY+ARRSIZE(tableARRAY) );
        QuickTableau theObject;
        eq(1, theObject.numSwaps(table),6);
    }
    {
        int tableARRAY[] = {
            2,  1,  3,  4,
            5,  6,  7,  8,
            9, 10, 11, 12,
           13, 14, 15, 16
           };
        vector <int> table( tableARRAY, tableARRAY+ARRSIZE(tableARRAY) );
        QuickTableau theObject;
        eq(2, theObject.numSwaps(table),1);
    }
    {
        int tableARRAY[] = {
            4,  3,  2,  1,
            5,  6,  7,  8,
            9, 10, 11, 12,
           13, 14, 15, 16
           };
        vector <int> table( tableARRAY, tableARRAY+ARRSIZE(tableARRAY) );
        QuickTableau theObject;
        eq(3, theObject.numSwaps(table),2);
    }
	return 0;
}
// END CUT HERE
