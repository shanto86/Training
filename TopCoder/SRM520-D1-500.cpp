// Straight forward dp. Just to optimize, first generate for each of the description pattern,
// what score can be made in how many ways.
// Next, just come from bottom and calculate for each score how many ways to make that maintaining the scoreboard order.
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

VI mainDp[8];
int total;
const int MOD = 1000000007;

VI CalcDp(VI& points, int mask) {
	VI ret(total + 1, 0);
	ret[0] = 1;
	for (int m = 0; m < 3; m++) {
		if (mask & (1 << m));
		else continue;

		VI newRet(total + 1, 0);
		for (int i = 1; i <= total; i++) {
			ret[i] = (ret[i] + ret[i - 1]);
			if (ret[i] >= MOD) ret[i] -= MOD;
		}

		for (int i = 1; i <= total; i++) {
			int now = ret[i - 1];
			if (i - points[m] > 0) now -= ret[i - points[m] - 1];
			if (now < 0) now += MOD;
			newRet[i] = now;
		}
		newRet.swap(ret);
	}
	return ret;
}

void Calc(VI& ans, VI& by) {
	LL prev = 0;
	for (int i = 0; i <= total; i++) {
		int new_prev = (prev + ans[i]);
		if (new_prev >= MOD) new_prev -= MOD;
		ans[i] = (prev * by[i]) % MOD;
		prev = new_prev;
	}
}

class SRMIntermissionPhase {
public:
    int countWays(vector <int> points, vector <string> description) {
		total = 0;
		for (int p : points) total += p;
		for (int i = 0; i < 8; i++) mainDp[i] = CalcDp(points, i);
		VI D;
		for (string d : description) {
			int mask = 0;
			for (int m = 0; m < 3; m++) {
				mask |= (d.at(m) == 'Y') << m;
			}
			D.push_back(mask);
		}

		int team = SZ(description);
		VI ans = mainDp[D[team - 1]];
		for (int i = team - 2; i >= 0; i--) {
			Calc(ans, mainDp[D[i]]);
		}
		int ret = 0;
		for (int i = 0; i <= total; i++) {
			ret += ans[i];
			if (ret >= MOD) ret -= MOD;
		}
		return ret;
    }

};

// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
    {
        int pointsARRAY[] = {25000, 50000, 100000};
        vector <int> points( pointsARRAY, pointsARRAY+ARRSIZE(pointsARRAY) );
        string descriptionARRAY[] = {"YNN",
            "NNN"};
        vector <string> description( descriptionARRAY, descriptionARRAY+ARRSIZE(descriptionARRAY) );
        SRMIntermissionPhase theObject;
        eq(0, theObject.countWays(points, description),25000);
    }
    {
        int pointsARRAY[] = {30000, 60000, 90000};
        vector <int> points( pointsARRAY, pointsARRAY+ARRSIZE(pointsARRAY) );
        string descriptionARRAY[] = {"NYN",
            "NYN"};
        vector <string> description( descriptionARRAY, descriptionARRAY+ARRSIZE(descriptionARRAY) );
        SRMIntermissionPhase theObject;
        eq(1, theObject.countWays(points, description),799969993);
    }
    {
        int pointsARRAY[] = {25000, 45000, 110000};
        vector <int> points( pointsARRAY, pointsARRAY+ARRSIZE(pointsARRAY) );
        string descriptionARRAY[] = {"NNN",
            "YYY"};
        vector <string> description( descriptionARRAY, descriptionARRAY+ARRSIZE(descriptionARRAY) );
        SRMIntermissionPhase theObject;
        eq(2, theObject.countWays(points, description),0);
    }
    {
        int pointsARRAY[] = {25600, 51200, 102400};
        vector <int> points( pointsARRAY, pointsARRAY+ARRSIZE(pointsARRAY) );
        string descriptionARRAY[] = {"NYY",
            "YNY",
            "YYY",
            "YNN",
            "YYN",
            "NNY",
            "NYN",
            "NNN"};
        vector <string> description( descriptionARRAY, descriptionARRAY+ARRSIZE(descriptionARRAY) );
        SRMIntermissionPhase theObject;
        eq(3, theObject.countWays(points, description),867560805);
    }
}
// END CUT HERE
