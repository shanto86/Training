/*
The main idea is to loop over all subrectangle size
and finding the number of rhombus packed in it.
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

int gcd(int a, int b) {
	if (a == 0) return b;
	if (b == 0) return a;
	if (a % b == 0) return  b;
	return gcd(b, a % b);
}

int calc(int RR, int CC) {
	if (RR == 4 && CC == 8) 
		RR = 4;
	if (CC > RR) swap(RR, CC);
	int ret = 0;
	for (int i = 0; i <= CC / 2; i++) {

		int times, on_border;
		int R = RR * 2;
		int C = CC * 2;
		int c = i * 2;

		int cr = R / 2, cc = C / 2;
		int pr = -cr, pc = c - cc;
		pr = ABS(pr), pc = ABS(pc);
		int g = gcd(ABS(pr), ABS(pc));
		pr /= g, pc /= g;
		swap(pr, pc);
		int k = 1000000;
		if (pr) k = MIN(k, R / 2 / pr);
		if (pc) k = MIN(k, C / 2 / pc);
		if ((cr & 1) != (cc & 1)) continue;;
		if (!k || k == 1000000) continue;
		if (cr & 1) {
			if (!(k & 1)) k--;
			times = (k + 1) / 2;
		}
		else {
			if ((k & 1)) k--;
			times = k / 2;
		}
		on_border = (k * pc == C/2);

		if (i == 0) {
			ret += times * 2 - (RR == CC);
		}
		else if (i * 2 == CC) {
			ret += on_border;
		}
		else {
			ret += 2 * on_border;
		}
	}
	return ret;
}

class SettingTents {
public:
    int countSites(int N, int M) {
		int ret = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				//printf("%d %d %d\n", i, j, calc(i, j));
				ret += calc(i, j) * (N - i + 1) * (M - j + 1);
			}
		}
		return ret;
    }

};

// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
    {
        SettingTents theObject;
        eq(0, theObject.countSites(2, 2),6);
    }
    {
        SettingTents theObject;
        eq(1, theObject.countSites(1, 6),6);
    }
    {
        SettingTents theObject;
        eq(2, theObject.countSites(6, 8),527);
    }
}
// END CUT HERE
