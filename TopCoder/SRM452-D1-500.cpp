/*
Very interesting problem. No particular approach.
Main idea is to think for- after putting an I
where can we put next I? They have to of different
parity, then where the next I? Only one valid place
and so on.
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
	if (a % b == 0) return b;
	return gcd(b, a % b);
}

LL MOD = 1000000007;

class IOIString {
public:
    int countIOIs(vector <string> mask) {
		string s = "";
		for (string& t : mask) s += t;

		int len = s.size();
		VI pos;
		int what = 0;
		for (int i = 0; i < len; i++) {
			if (s[i] == 'I') {
				pos.push_back(i);
			}
			what += s[i] == '?';
		}

		LL ans = 0;

		int diff = -1;
		if (SZ(pos) > 1) diff = pos[1] - pos[0];
		for (int i = 2; i < SZ(pos); i++) {
			diff = gcd(diff, pos[i] - pos[i - 1]);
		}
		int first = -1, last = -1;
		if (SZ(pos)) first = pos[0], last = pos[SZ(pos) - 1];

		for (int i = 0; i < len; i++) {
			if (s[i] == 'O') continue;
			if ((SZ(pos) == 0) || (SZ(pos) == 1 && pos[0] == i)) ans++;
			if (first != -1 && first < i) break;
			for (int j = 1; i + j < len; j+=2) {

				int cnt = (s[i] == 'I');
				for (int k = i + j; k < len; k += j) {
					if (s[k] == 'O') break;
					cnt += s[k] == 'I';
					if (cnt == SZ(pos)) ans++;
				}
			}
		}

		if (SZ(pos) == 0) ans += 1;

		LL now = 1;
		for (int i = 1; i <= what; i++) now = (now * 2) % MOD;
		ans = now - ans;
        return ans;
    }

};

// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
    {
        string maskARRAY[] = {"IO?"};
        vector <string> mask( maskARRAY, maskARRAY+ARRSIZE(maskARRAY) );
        IOIString theObject;
        eq(0, theObject.countIOIs(mask),1);
    }
    {
        string maskARRAY[] = {"????"};
        vector <string> mask( maskARRAY, maskARRAY+ARRSIZE(maskARRAY) );
        IOIString theObject;
        eq(1, theObject.countIOIs(mask),4);
    }
    {
        string maskARRAY[] = {"?II"};
        vector <string> mask( maskARRAY, maskARRAY+ARRSIZE(maskARRAY) );
        IOIString theObject;
        eq(2, theObject.countIOIs(mask),0);
    }
    {
        string maskARRAY[] = {"I??O??I"};
        vector <string> mask( maskARRAY, maskARRAY+ARRSIZE(maskARRAY) );
        IOIString theObject;
        eq(3, theObject.countIOIs(mask),16);
    }
    {
        string maskARRAY[] = {"???I???????O???","???????????O??IO????????I???"};
        vector <string> mask( maskARRAY, maskARRAY+ARRSIZE(maskARRAY) );
        IOIString theObject;
        eq(4, theObject.countIOIs(mask),438952513);
    }
}
// END CUT HERE
