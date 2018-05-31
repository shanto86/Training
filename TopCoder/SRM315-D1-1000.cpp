/*
Main idea is to notice, there are not many patterns the 3
rectangles can lie, based on some horizontal/vertical cut.
After the O(n^2) cuts, we find the maximum rectangle
inside the cut rectangles. That can be found using
the idea of maximum subrectangle problem.
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

vector<string> F;
vector<VI> vals;

inline int area(int r1, int r2, int c1, int c2) {
	int val = vals[r2][c2];
	if (r1) val -= vals[r1 - 1][c2];
	if (c1) val -= vals[r2][c1 - 1];
	if (r1 && c1) val += vals[r1 - 1][c1 - 1];
	return val;
}

int calc(int r1, int r2, int c1, int c2) {
	int ret = area(r1, r2, c1, c2);
	for (int i = r1; i <= r2; i++) {
		for (int j = i; j <= r2; j++) {
			int minarea = 0;
			for (int k = c1; k <= c2; k++) {
				int cur = area(i, j, c1, k);
				ret = MAX(ret, cur - minarea);
				minarea = MIN(minarea, cur);
			}
		}
	}
	return ret;
}

class ThreeMines {
public:
    int maximumProfit(vector <string> field) {
		F = field;
		int R = SZ(field);
		int C = SZ(field[0]);
		vals = vector<VI>(R, VI(C, 0));
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (IN(field[i][j], 'a', 'z')) vals[i][j] = field[i][j] - 'a';
				else vals[i][j] = -(field[i][j] - 'A');

				if (i) vals[i][j] += vals[i - 1][j];
				if (j) vals[i][j] += vals[i][j - 1];
				if (i && j) vals[i][j] -= vals[i - 1][j - 1];
			}
		}
		int ans = -1000000000;

		for (int i = 0; i < R; i++) {
			for (int j = i + 1; j < R - 1; j++) {
				int now = calc(0, i, 0, C - 1) + calc(i + 1, j, 0, C - 1) + calc(j + 1, R - 1, 0, C - 1);
				ans = MAX(ans, now);
			}
		}
		for (int i = 0; i < C; i++) {
			for (int j = i + 1; j < C - 1; j++) {
				int now = calc(0, R - 1, 0, i) + calc(0, R - 1, i + 1, j) + calc(0, R - 1, j + 1, C - 1);
				ans = MAX(ans, now);
			}
		}

		for (int i = 0; i < R - 1; i++) {
			for (int j = 0; j < C - 1; j++) {
				int now;
				now = calc(0, R - 1, 0, j) + calc(0, i, j + 1, C - 1) + calc(i + 1, R - 1, j + 1, C - 1);
				ans = MAX(ans, now);
				now = calc(0, R - 1, j + 1, C - 1) + calc(0, i, 0, j) + calc(i + 1, R - 1, 0, j);
				ans = MAX(ans, now);

				now = calc(0, i, 0, C - 1) + calc(i + 1, R - 1, 0, j) + calc(i + 1, R - 1, j + 1, C - 1);
				ans = MAX(ans, now);
				now = calc(i + 1, R - 1, 0, C - 1) + calc(0, i, 0, j) + calc(0, i, j + 1, C - 1);
				ans = MAX(ans, now);
			}
		}
		return ans;
    }

};

// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
    {
        string fieldARRAY[] = {
           "bbbb",
           "bBBB",
           "BBbb",
           "BBBB"};
        vector <string> field( fieldARRAY, fieldARRAY+ARRSIZE(fieldARRAY) );
        ThreeMines theObject;
        eq(0, theObject.maximumProfit(field),7);
    }
    {
        string fieldARRAY[] = {"cfCBDCbcdZb"};
        vector <string> field( fieldARRAY, fieldARRAY+ARRSIZE(fieldARRAY) );
        ThreeMines theObject;
        eq(1, theObject.maximumProfit(field),14);
    }
    {
        string fieldARRAY[] = {"d", "c", "B", "m", "Z", "h", "g", "B", "z", "G", "H", "b", "Y"}
           ;
        vector <string> field( fieldARRAY, fieldARRAY+ARRSIZE(fieldARRAY) );
        ThreeMines theObject;
        eq(2, theObject.maximumProfit(field),54);
    }
    {
        string fieldARRAY[] = {
           "hBhh", 
           "BBBB",
           "BBBB", 
           "hBhh", 
           "hBhh"};
        vector <string> field( fieldARRAY, fieldARRAY+ARRSIZE(fieldARRAY) );
        ThreeMines theObject;
        eq(3, theObject.maximumProfit(field),62);
    }
    {
        string fieldARRAY[] = {
           "BB", 
           "BB"};
        vector <string> field( fieldARRAY, fieldARRAY+ARRSIZE(fieldARRAY) );
        ThreeMines theObject;
        eq(4, theObject.maximumProfit(field),-3);
    }
    {
        string fieldARRAY[] = {
           "ZcabcaacacabcbbbcababacaccbZaa",
           "acaaccccacbccbaaccabaccaacbZbc",
           "bcbaacbcbbccbbcbabbbbaZcbcbccb",
           "cccacbabccbZbcbabaacbbZcbacbab",
           "cacbabbcabbabbcacbcbbcaacaabbc",
           "bacZcacaaccbabbcccccabcaacbaca",
           "cbcccacabcabacaccacaZbbcbcacbb",
           "cZbbbcaacbaacaabZcaccbcZccbbab",
           "Zcababaacbbbbccbcbbaccacacbbcc",
           "cZcccaaabbcbcbccccbcbaabbbccbb",
           "bbcaacacabccababacbccacccbbaba",
           "cccbbcaZabccacabbccccabbabbbab",
           "bbbacbccbbcaabaaabccbcaabcacaa",
           "cbbababbccccbcccbaacacccaabaac",
           "aaccaccaccbabbccaaaacbacccacca",
           "bbbcabcabZZcabcabbaacZbaaabaZb",
           "aaabbabcabaaacbcccccbbcabcccbc",
           "bbbaccbacacaccbbaccabacbbbaaac",
           "acaaacccbabbccbcbabbcbaaaccabb",
           "bcaaaaabcbabaaabccacccbaacbbbc",
           "bZcbcbcccaabccaabbccbababbbcca",
           "cbbbbcccabcabcbacaaaaabbbbbcac",
           "ccbbcbacacbbcacacbaabcbbacbaba",
           "cbbbaabaabbbbaccabbcbcaccaaaac",
           "abZcabaacbbcacbaaabccbabacacaa",
           "aabccacbabaacaccccbbbbcccccaca",
           "aabcbaaacbabcaccbaabbbabbabbca",
           "ababcabaccaaaacccacbcbcabacbcb",
           "bcaaaacabcabbbaccccccacabccacb",
           "cbbabbbccaaaaacbccaabcbbccbacc"};
        vector <string> field( fieldARRAY, fieldARRAY+ARRSIZE(fieldARRAY) );
        ThreeMines theObject;
        eq(5, theObject.maximumProfit(field),671);
    }
}
// END CUT HERE
