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
#include <unordered_map>
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

map<int, int> M;
vector<string> S;
int R, C;

int id[300], nid;
int Id(char ch) {
	if (id[ch] == -1) return id[ch] = nid++;
	return id[ch];
}

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
LL ans;
int xid;

void dfs(int r, int c, int mask, int depth) {
	if (depth == 11) {
		M[mask]++;
		int xmask = mask ^ ((1 << 21) - 1) ^ (1 <<xid);
		auto iM = M.find(xmask);
		if (iM == M.end()) return;
		ans += iM->second;
		return;
	}
	for (int d = 0; d < 4; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];
		if (nr < 0 || nc < 0 || nr >= R || nc >= C) continue;
		if (S[nr][nc] == '.') continue;
		if (mask & (1 << Id(S[nr][nc]))) continue;
		dfs(nr, nc, mask | (1 << Id(S[nr][nc])), depth + 1);
	}
}

class AlphabetPaths {
public:
    long long count(vector <string> letterMaze) {
		ans = 0;
		nid = 0;
		S = letterMaze;
		R = SZ(S);
		C = SZ(S[0]);
		MEM(id, -1);

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (S[i][j] == '.') continue;
				M.clear();
				xid = Id(S[i][j]);
				dfs(i, j, 1 << Id(S[i][j]), 1);
			}
		}
		return ans*2;
	}

};

// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        string letterMazeARRAY[] = {"ABCDEFZHIXKLMNOPQRST",
            "...................V"};
        vector <string> letterMaze( letterMazeARRAY, letterMazeARRAY+ARRSIZE(letterMazeARRAY) );
        AlphabetPaths theObject;
        eq(0, theObject.count(letterMaze),2LL);
    }
    {
        string letterMazeARRAY[] = {".................VT.",
            "....................",
            "ABCDEFZHIXKLMNOPQRS.",
            "..................S.",
            ".................VT."};
        vector <string> letterMaze( letterMazeARRAY, letterMazeARRAY+ARRSIZE(letterMazeARRAY) );
        AlphabetPaths theObject;
        eq(1, theObject.count(letterMaze),0LL);
    }
    {
        string letterMazeARRAY[] = {"TBCDE.PQRSA", 
            "FZHIXKLMNOV"};
        vector <string> letterMaze( letterMazeARRAY, letterMazeARRAY+ARRSIZE(letterMazeARRAY) );
        AlphabetPaths theObject;
        eq(2, theObject.count(letterMaze),50LL);
    }
    {
        string letterMazeARRAY[] = {"ABCDEF.",
            "V....Z.",
            "T....H.",
            "S....I.",
            "R....X.",
            "KLMNOPQ"};
        vector <string> letterMaze( letterMazeARRAY, letterMazeARRAY+ARRSIZE(letterMazeARRAY) );
        AlphabetPaths theObject;
        eq(3, theObject.count(letterMaze),4LL);
    }
	{
		string letterMazeARRAY[] =
		{ "ABCABCABCABCABCABCAB", "DEFDEFDEFDEFDEFDEFDE", "ZHIZHIZHIZHIZHIZHIZH", "XKLXKLXKLXKLXKLXKLXK", "MNOMNOMNOMNOMNOMNOMN", "PQRPQRPQRPQRPQRPQRPQ", "STVSTVSTVSTVSTVSTVST", "ABCABCABCABCABCABCAB", "DEFDEFDEFDEFDEFDEFDE", "ZHIZHIZHIZHIZHIZHIZH", "XKLXKLXKLXKLXKLXKLXK", "MNOMNOMNOMNOMNOMNOMN", "PQRPQRPQRPQRPQRPQRPQ", "STVSTVSTVSTVSTVSTVST", "ABCABCABCABCABCABCAB", "DEFDEFDEFDEFDEFDEFDE", "ZHIZHIZHIZHIZHIZHIZH", "XKLXKLXKLXKLXKLXKLXK", "MNOMNOMNOMNOMNOMNOMN", "PQRPQRPQRPQRPQRPQRPQ" };

		vector <string> letterMaze(letterMazeARRAY, letterMazeARRAY + ARRSIZE(letterMazeARRAY));
		AlphabetPaths theObject;
		eq(4, theObject.count(letterMaze), 5338808LL);
	}
	return 0;
}
// END CUT HERE
