/*
We need to count the number of subtrees.
It's a straightforward DP. I kept two dp per node and populated them in dfs style.
DP[0][at][i] = Number of i size subtree in the tree rooted at i.
DP[1][at][i] = Number of i size subtree in the tree rooted at i including i.
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

//typedef int LL;
typedef long long int LL;
//typedef __int64 LL;



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
void eq( int n, LL haves, LL need ) {
    if ( haves == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( haves );
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

VI V[100];
LL dp[100][2][100];

void DP(int at, int par) {
	dp[at][1][1] = 1;
	dp[at][1][0] = 1;
	for (int i : V[at]) {
		if (i == par) continue;
		DP(i, at);
		for (int j = 1; j < 60; j++) {
			dp[at][0][j] += dp[i][0][j];
		}

		for (int j = 59; j >= 1; j--) {
			LL cur = 0;
			for (int k = 1; k <= j; k++) {
				cur += dp[at][1][k] * dp[i][1][j - k];
			}
			dp[at][1][j] = cur;
		}
	}
	for (int i = 1; i < 60; i++) dp[at][0][i] += dp[at][1][i];
	dp[at][0][0] = 1;
}
class CentaurCompanyDiv2 {
public:
    long long count(vector <int> a, vector <int> b) {
		int n = SZ(a);
		for (int i = 0; i < 100; i++) {
			V[i].clear();
		}
		for (int i = 0; i < n; i++) {
			V[a[i]].push_back(b[i]);
			V[b[i]].push_back(a[i]);
		}
		CLR(dp);
		DP(1, 0);
		LL ans = 0;
		for (int i = 0; i < 100; i++) ans += dp[1][0][i];
		return ans;
    }

};

// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
    {
        int aARRAY[] = {1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        CentaurCompanyDiv2 theObject;
        eq(0, theObject.count(a, b),4L);
    }
    {
        int aARRAY[] = {2,2};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,3};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        CentaurCompanyDiv2 theObject;
        eq(1, theObject.count(a, b),7L);
    }
    {
        int aARRAY[] = {1,2,3,4,5,6,7,8,9};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {2,3,4,5,6,7,8,9,10};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        CentaurCompanyDiv2 theObject;
        eq(2, theObject.count(a, b),56L);
    }
    {
        int aARRAY[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        CentaurCompanyDiv2 theObject;
        eq(3, theObject.count(a, b),1125899906842675L);
    }
    {
        int aARRAY[] = {10, 7, 2, 5, 6, 2, 4, 9, 7};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {8, 10, 10, 4, 1, 6, 2, 2, 3};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        CentaurCompanyDiv2 theObject;
        eq(4, theObject.count(a, b),144L);
    }
}
// END CUT HERE
