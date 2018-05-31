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

VI xp, yp, xv, yv;

double f(double t) {
	double minx, miny, maxx, maxy;
	for (int i = 0; i < SZ(xp); i++) {
		double x = xp[i] + xv[i] * t;
		double y = yp[i] + yv[i] * t;
		if (i == 0) {
			minx = maxx = x;
			miny = maxy = y;
		}
		minx = MIN(minx, x);
		maxx = MAX(maxx, x);
		miny = MIN(miny, y);
		maxy = MAX(maxy, y);
	}
	return MAX(maxx - minx, maxy - miny);
}

class CatchTheMice {
public:
    double largestCage(vector <int> xp, vector <int> yp, vector <int> xv, vector <int> yv) {
		::xp = xp;
		::yp = yp;
		::xv = xv;
		::yv = yv;
		double lo = 0;
		double hi = 1e9;
		for (int i = 0; i < 100000; i++) {
			double m1 = (2 * lo + hi) / 3;
			double m2 = (lo + 2 * hi) / 3;
			if (f(m1) < f(m2)) hi = m2;
			else lo = m1;
		}
        double res = f(lo);
        return res;
    }

};

// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
    {
        int xpARRAY[] = {0,10};
        vector <int> xp( xpARRAY, xpARRAY+ARRSIZE(xpARRAY) );
        int ypARRAY[] = {0,10};
        vector <int> yp( ypARRAY, ypARRAY+ARRSIZE(ypARRAY) );
        int xvARRAY[] = {10,-10};
        vector <int> xv( xvARRAY, xvARRAY+ARRSIZE(xvARRAY) );
        int yvARRAY[] = {0,0};
        vector <int> yv( yvARRAY, yvARRAY+ARRSIZE(yvARRAY) );
        CatchTheMice theObject;
        eq(0, theObject.largestCage(xp, yp, xv, yv),10.0);
    }
    {
        int xpARRAY[] = {0,10,0};
        vector <int> xp( xpARRAY, xpARRAY+ARRSIZE(xpARRAY) );
        int ypARRAY[] = {0,0,10};
        vector <int> yp( ypARRAY, ypARRAY+ARRSIZE(ypARRAY) );
        int xvARRAY[] = {1,-6,4};
        vector <int> xv( xvARRAY, xvARRAY+ARRSIZE(xvARRAY) );
        int yvARRAY[] = {4,5,-4};
        vector <int> yv( yvARRAY, yvARRAY+ARRSIZE(yvARRAY) );
        CatchTheMice theObject;
        eq(1, theObject.largestCage(xp, yp, xv, yv),3.0);
    }
    {
        int xpARRAY[] = {50,10,30,15};
        vector <int> xp( xpARRAY, xpARRAY+ARRSIZE(xpARRAY) );
        int ypARRAY[] = {-10,30,20,40};
        vector <int> yp( ypARRAY, ypARRAY+ARRSIZE(ypARRAY) );
        int xvARRAY[] = {-5,-10,-15,-5};
        vector <int> xv( xvARRAY, xvARRAY+ARRSIZE(xvARRAY) );
        int yvARRAY[] = {40,-10,-1,-50};
        vector <int> yv( yvARRAY, yvARRAY+ARRSIZE(yvARRAY) );
        CatchTheMice theObject;
        eq(2, theObject.largestCage(xp, yp, xv, yv),40.526315789473685);
    }
    {
        int xpARRAY[] = {0,10,10,0};
        vector <int> xp( xpARRAY, xpARRAY+ARRSIZE(xpARRAY) );
        int ypARRAY[] = {0,0,10,10};
        vector <int> yp( ypARRAY, ypARRAY+ARRSIZE(ypARRAY) );
        int xvARRAY[] = {1,0,-1,0};
        vector <int> xv( xvARRAY, xvARRAY+ARRSIZE(xvARRAY) );
        int yvARRAY[] = {0,1,0,-1};
        vector <int> yv( yvARRAY, yvARRAY+ARRSIZE(yvARRAY) );
        CatchTheMice theObject;
        eq(3, theObject.largestCage(xp, yp, xv, yv),10.0);
    }
    {
        int xpARRAY[] = {13,50,100,40,-100};
        vector <int> xp( xpARRAY, xpARRAY+ARRSIZE(xpARRAY) );
        int ypARRAY[] = {20,20,-150,-40,63};
        vector <int> yp( ypARRAY, ypARRAY+ARRSIZE(ypARRAY) );
        int xvARRAY[] = {4,50,41,-41,-79};
        vector <int> xv( xvARRAY, xvARRAY+ARRSIZE(xvARRAY) );
        int yvARRAY[] = {1,1,1,3,-1};
        vector <int> yv( yvARRAY, yvARRAY+ARRSIZE(yvARRAY) );
        CatchTheMice theObject;
        eq(4, theObject.largestCage(xp, yp, xv, yv),212.78688524590163);
    }
    {
        int xpARRAY[] = {0,10};
        vector <int> xp( xpARRAY, xpARRAY+ARRSIZE(xpARRAY) );
        int ypARRAY[] = {0,0};
        vector <int> yp( ypARRAY, ypARRAY+ARRSIZE(ypARRAY) );
        int xvARRAY[] = {5,5};
        vector <int> xv( xvARRAY, xvARRAY+ARRSIZE(xvARRAY) );
        int yvARRAY[] = {3,3};
        vector <int> yv( yvARRAY, yvARRAY+ARRSIZE(yvARRAY) );
        CatchTheMice theObject;
        eq(5, theObject.largestCage(xp, yp, xv, yv),10.0);
    }
    {
        int xpARRAY[] = {-49,-463,-212,-204,-557,-67,-374,-335,-590,-4};
        vector <int> xp( xpARRAY, xpARRAY+ARRSIZE(xpARRAY) );
        int ypARRAY[] = {352,491,280,355,129,78,404,597,553,445};
        vector <int> yp( ypARRAY, ypARRAY+ARRSIZE(ypARRAY) );
        int xvARRAY[] = {-82,57,-23,-32,89,-72,27,17,100,-94};
        vector <int> xv( xvARRAY, xvARRAY+ARRSIZE(xvARRAY) );
        int yvARRAY[] = {-9,-58,9,-14,56,75,-32,-98,-81,-43};
        vector <int> yv( yvARRAY, yvARRAY+ARRSIZE(yvARRAY) );
        CatchTheMice theObject;
        eq(6, theObject.largestCage(xp, yp, xv, yv),25.467532467532468);
    }
}
// END CUT HERE
