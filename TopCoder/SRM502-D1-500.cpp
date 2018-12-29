// First we can greedily order the tasks by exchange argument.
// Then run dp over the tasks.
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

int dp[100005];

class TheProgrammingContestDivOne {
public:
    int find(int T, vector <int> maxPoints, vector <int> pointsPerMinute, vector <int> requiredTime) {
		VI order;
		for (int i = 0; i < SZ(maxPoints); i++) order.push_back(i);
		auto cmp = [&](int a, int b) {
			LL pointAB = (1LL * requiredTime[b]) * pointsPerMinute[a];
			LL pointBA = (1LL * requiredTime[a]) * pointsPerMinute[b];
			return pointAB > pointBA;
		};
		sort(ALL(order), cmp);

		CLR(dp);
		for (int i : order) {
			for (int j = T - requiredTime[i]; j >= 0; j--) {
				int newPoint = MAX(0, maxPoints[i] - (1LL * pointsPerMinute[i]) * (j + requiredTime[i]));
				dp[j + requiredTime[i]] = MAX(dp[j + requiredTime[i]], dp[j] + newPoint);
			}
		}
		int res = 0;
		for (int i = 0; i <= T; i++) res = MAX(res, dp[i]);
		return res;
    }

};

// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
    {
        int maxPointsARRAY[] = {502};
        vector <int> maxPoints( maxPointsARRAY, maxPointsARRAY+ARRSIZE(maxPointsARRAY) );
        int pointsPerMinuteARRAY[] = {2};
        vector <int> pointsPerMinute( pointsPerMinuteARRAY, pointsPerMinuteARRAY+ARRSIZE(pointsPerMinuteARRAY) );
        int requiredTimeARRAY[] = {47};
        vector <int> requiredTime( requiredTimeARRAY, requiredTimeARRAY+ARRSIZE(requiredTimeARRAY) );
        TheProgrammingContestDivOne theObject;
        eq(0, theObject.find(74, maxPoints, pointsPerMinute, requiredTime),408);
    }
    {
        int maxPointsARRAY[] = {100000, 100000};
        vector <int> maxPoints( maxPointsARRAY, maxPointsARRAY+ARRSIZE(maxPointsARRAY) );
        int pointsPerMinuteARRAY[] = {1, 100000};
        vector <int> pointsPerMinute( pointsPerMinuteARRAY, pointsPerMinuteARRAY+ARRSIZE(pointsPerMinuteARRAY) );
        int requiredTimeARRAY[] = {50000, 30000};
        vector <int> requiredTime( requiredTimeARRAY, requiredTimeARRAY+ARRSIZE(requiredTimeARRAY) );
        TheProgrammingContestDivOne theObject;
        eq(1, theObject.find(40000, maxPoints, pointsPerMinute, requiredTime),0);
    }
    {
        int maxPointsARRAY[] = {250, 500, 1000};
        vector <int> maxPoints( maxPointsARRAY, maxPointsARRAY+ARRSIZE(maxPointsARRAY) );
        int pointsPerMinuteARRAY[] = {2, 4, 8};
        vector <int> pointsPerMinute( pointsPerMinuteARRAY, pointsPerMinuteARRAY+ARRSIZE(pointsPerMinuteARRAY) );
        int requiredTimeARRAY[] = {25, 25, 25};
        vector <int> requiredTime( requiredTimeARRAY, requiredTimeARRAY+ARRSIZE(requiredTimeARRAY) );
        TheProgrammingContestDivOne theObject;
        eq(2, theObject.find(75, maxPoints, pointsPerMinute, requiredTime),1200);
    }
    {
        int maxPointsARRAY[] = {100, 100, 100000};
        vector <int> maxPoints( maxPointsARRAY, maxPointsARRAY+ARRSIZE(maxPointsARRAY) );
        int pointsPerMinuteARRAY[] = {1, 1, 100};
        vector <int> pointsPerMinute( pointsPerMinuteARRAY, pointsPerMinuteARRAY+ARRSIZE(pointsPerMinuteARRAY) );
        int requiredTimeARRAY[] = {15, 15, 30};
        vector <int> requiredTime( requiredTimeARRAY, requiredTimeARRAY+ARRSIZE(requiredTimeARRAY) );
        TheProgrammingContestDivOne theObject;
        eq(3, theObject.find(30, maxPoints, pointsPerMinute, requiredTime),97000);
    }
}
// END CUT HERE
