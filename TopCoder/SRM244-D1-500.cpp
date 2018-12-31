/*
My idea is very simple but requires a bit of code. I mirror our rectangle 5x times in all direction and draw
a line between original point A and for each occurance of point B (in mirror). Then I check if the segment 
intersects all the sides (or some of their mirrors).
The code is a bit painful and required library code (just for checking seg-seg intersection).
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

/////////

#define mp make_pair
#define pb push_back

const double eps = 1e-8;
const double pi = acos(-1.0);
const double inf = 1e20;
const int maxp = 1111;

//Compares a double to zero
int dblcmp(double d)
{
	if (fabs(d)<eps) return 0;
	return d > eps ? 1 : -1;
}

//square of a double
inline double sqr(double x)
{
	return x * x;
}

/*
point()						- Empty constructor
point(double x, double y)	- constructor
input()						- double input
output()					- .2lf output
operator ==					- compares x and y
operator <					- compares first by x, then by y
len()						- gives length from origin
len2()						- gives square of length from origin
distance(point p)			- gives distance from p
add(point p)				- returns new point after adding curresponging x and y
sub(point p)				- returns new point after subtracting curresponging x and y
mul(double b)				- returns new point after multiplieing x and y by b
div(double b)				- returns new point after divideing x and y by b
dot(point p)				- dot product
det(point p)				- cross product of 2d points
rad(point a, point b)		- Probably radius of circumcircle of the triangle
trunc(double r)				- return point that is truncated the distance from center to r
rotleft()					- returns 90 degree ccw rotated point
rotright()					- returns 90 degree cw rotated point
rotate(point p, double angle) - returns point after rotateing the point centering at p by angle radian ccw
*/
struct point
{
	double x, y;

	point() {}

	point(double _x, double _y)
	{
		x = _x;
		y = _y;
	}

	void input()
	{
		scanf("%lf%lf", &x, &y);
	}

	void output()
	{
		printf("%.2f %.2f\n", x, y);
	}

	bool operator==(point a)const
	{
		return dblcmp(a.x - x) == 0 && dblcmp(a.y - y) == 0;
	}

	bool operator<(point a)const
	{
		return dblcmp(a.x - x) == 0 ? dblcmp(y - a.y) < 0 : x < a.x;
	}

	point operator-(point a)const
	{
		return point(x - a.x, y - a.y);
	}

	double len()
	{
		return hypot(x, y);
	}

	double len2()
	{
		return x * x + y * y;
	}

	double distance(point p)
	{
		return hypot(x - p.x, y - p.y);
	}

	point add(point p)
	{
		return point(x + p.x, y + p.y);
	}

	point sub(point p)
	{
		return point(x - p.x, y - p.y);
	}

	point mul(double b)
	{
		return point(x * b, y * b);
	}

	point div(double b)
	{
		return point(x / b, y / b);
	}

	double dot(point p)
	{
		return x * p.x + y * p.y;
	}
	double det(point p)
	{
		return x * p.y - y * p.x;
	}
	double rad(point a, point b)
	{
		point p = *this;
		return fabs(atan2(fabs(a.sub(p).det(b.sub(p))), a.sub(p).dot(b.sub(p))));
	}
	point trunc(double r)
	{
		double l = len();
		if (!dblcmp(l))return *this;
		r /= l;
		return point(x*r, y*r);
	}
	point rotleft()
	{
		return point(-y, x);
	}
	point rotright()
	{
		return point(y, -x);
	}
	point rotate(point p, double angle)
	{
		point v = this->sub(p);
		double c = cos(angle), s = sin(angle);
		return point(p.x + v.x*c - v.y*s, p.y + v.x*s + v.y*c);
	}
};


/*
Stores two points

line()								- Empty constructor
line(point a, point b)				- line through a and b
operator ==							- checks if two points are same
line(point p, double angle)			- one end p, another end at angle degree
line(double a, double b, double c)	- line of equation ax + by + c = 0
input()								- inputs a and b
adjust()							- orders in such a way that a < b
length()							- distance of ab
angle()								- returns 0 <= angle < 180
relation()							- 0 if collinear
1 if ccw
2 if cw
pointonseg(point p)					- returns 1 if point is on segment
parallel(line v)					- returns 1 if they are parallel
segcrossseg(line v)					- returns 0 if does not intersect
returns 1 if non-standard intersection
returns 2 if intersects
segcrossseg_inside(line v)			- returns 1 if intersects strictly inside
returns 0 if not
linecrossseg(line v)				- v is line
linecrossline(line v)				- 0 if parallel
1 if coincides
2 if intersects
crosspoint(line v)					- returns intersection point
dispointtoline(point p)				- distance from point p to the line
dispointtoseg(point p)				- distance from p to the segment
lineprog(point p)					- returns projected point p on ab line
symmetrypoint(point p)				- returns reflection point of p over ab
*/
struct line
{
	point a, b;
	line() {}
	line(point _a, point _b)
	{
		a = _a;
		b = _b;
	}
	bool operator==(line v)
	{
		return (a == v.a) && (b == v.b);
	}

	line(point p, double angle)
	{
		a = p;
		if (dblcmp(angle - pi / 2) == 0)
		{
			b = a.add(point(0, 1));
		}
		else
		{
			b = a.add(point(1, tan(angle)));
		}
	}
	//ax+by+c=0
	line(double _a, double _b, double _c)
	{
		if (dblcmp(_a) == 0)
		{
			a = point(0, -_c / _b);
			b = point(1, -_c / _b);
		}
		else if (dblcmp(_b) == 0)
		{
			a = point(-_c / _a, 0);
			b = point(-_c / _a, 1);
		}
		else
		{
			a = point(0, -_c / _b);
			b = point(1, (-_c - _a) / _b);
		}
	}
	void input()
	{
		a.input();
		b.input();
	}
	void adjust()
	{
		if (b<a)swap(a, b);
	}
	double length()
	{
		return a.distance(b);
	}
	double angle()
	{
		double k = atan2(b.y - a.y, b.x - a.x);
		if (dblcmp(k)<0)k += pi;
		if (dblcmp(k - pi) == 0)k -= pi;
		return k;
	}
	int relation(point p)
	{
		int c = dblcmp(p.sub(a).det(b.sub(a)));
		if (c<0)return 1;
		if (c>0)return 2;
		return 3;
	}
	bool pointonseg(point p)
	{
		return dblcmp(p.sub(a).det(b.sub(a))) == 0 && dblcmp(p.sub(a).dot(p.sub(b))) <= 0;
	}
	bool parallel(line v)
	{
		return dblcmp(b.sub(a).det(v.b.sub(v.a))) == 0;
	}
	int segcrossseg(line v)
	{
		int d1 = dblcmp(b.sub(a).det(v.a.sub(a)));
		int d2 = dblcmp(b.sub(a).det(v.b.sub(a)));
		int d3 = dblcmp(v.b.sub(v.a).det(a.sub(v.a)));
		int d4 = dblcmp(v.b.sub(v.a).det(b.sub(v.a)));
		if ((d1^d2) == -2 && (d3^d4) == -2)return 2;
		return (d1 == 0 && dblcmp(v.a.sub(a).dot(v.a.sub(b))) <= 0 ||
			d2 == 0 && dblcmp(v.b.sub(a).dot(v.b.sub(b))) <= 0 ||
			d3 == 0 && dblcmp(a.sub(v.a).dot(a.sub(v.b))) <= 0 ||
			d4 == 0 && dblcmp(b.sub(v.a).dot(b.sub(v.b))) <= 0);
	}
	int segcrossseg_inside(line v)
	{
		if (v.pointonseg(a) || v.pointonseg(b) || pointonseg(v.a) || pointonseg(v.b)) return 0;
		int d1 = dblcmp(b.sub(a).det(v.a.sub(a)));
		int d2 = dblcmp(b.sub(a).det(v.b.sub(a)));
		int d3 = dblcmp(v.b.sub(v.a).det(a.sub(v.a)));
		int d4 = dblcmp(v.b.sub(v.a).det(b.sub(v.a)));
		if ((d1^d2) == -2 && (d3^d4) == -2)return 1;
		return (d1 == 0 && dblcmp(v.a.sub(a).dot(v.a.sub(b))) <= 0 ||
			d2 == 0 && dblcmp(v.b.sub(a).dot(v.b.sub(b))) <= 0 ||
			d3 == 0 && dblcmp(a.sub(v.a).dot(a.sub(v.b))) <= 0 ||
			d4 == 0 && dblcmp(b.sub(v.a).dot(b.sub(v.b))) <= 0);
	}
	int linecrossseg(line v)//*this seg v line
	{
		int d1 = dblcmp(b.sub(a).det(v.a.sub(a)));
		int d2 = dblcmp(b.sub(a).det(v.b.sub(a)));
		if ((d1^d2) == -2)return 2;
		return (d1 == 0 || d2 == 0);
	}
	int linecrossline(line v)
	{
		if ((*this).parallel(v))
		{
			return v.relation(a) == 3;
		}
		return 2;
	}
	point crosspoint(line v)
	{
		double a1 = v.b.sub(v.a).det(a.sub(v.a));
		double a2 = v.b.sub(v.a).det(b.sub(v.a));
		return point((a.x*a2 - b.x*a1) / (a2 - a1), (a.y*a2 - b.y*a1) / (a2 - a1));
	}
	double dispointtoline(point p)
	{
		return fabs(p.sub(a).det(b.sub(a))) / length();
	}
	double dispointtoseg(point p)
	{
		if (dblcmp(p.sub(b).dot(a.sub(b)))<0 || dblcmp(p.sub(a).dot(b.sub(a)))<0)
		{
			return MIN(p.distance(a), p.distance(b));
		}
		return dispointtoline(p);
	}
	point lineprog(point p)
	{
		return a.add(b.sub(a).mul(b.sub(a).dot(p.sub(a)) / b.sub(a).len2()));
	}
	point symmetrypoint(point p)
	{
		point q = lineprog(p);
		return point(2 * q.x - p.x, 2 * q.y - p.y);
	}
};
//////////

int checkH(int qx, int qy, int px, int py, int a, int b, int st) {
	line l(point(qx, qy), point(px, py));
	for (int i = -5; i < 5; i ++) {
		for (int j = st; j < 5; j+=2) {
			int ax = i * a, ay = j * b;
			int bx = (i + 1) * a, by = j * b;
			line l2(point(ax, ay), point(bx, by));
			if (l.segcrossseg(l2)) return 1;

		}
	}
	return 0;
}

int checkV(int qx, int qy, int px, int py, int a, int b, int st) {
	line l(point(qx, qy), point(px, py));
	for (int i = st; i < 5; i += 2) {
		for (int j = -5; j < 5; j++) {
			int ax = i * a, ay = j * b;
			int bx = i * a, by = (j + 1) * b;
			line l2(point(ax, ay), point(bx, by));
			if (l.segcrossseg(l2)) return 1;

		}
	}
	return 0;
}

int check(int qx, int qy, int px, int py, int a, int b) {
	if (!checkH(qx, qy, px, py, a, b, -5)) return 0;
	if (!checkH(qx, qy, px, py, a, b, -4)) return 0;
	if (!checkV(qx, qy, px, py, a, b, -5)) return 0;
	if (!checkV(qx, qy, px, py, a, b, -4)) return 0;
	return 1;
}

class Polyline {
public:
    double length(int a, int b, int x0, int y0, int x1, int y1) {
		double ret = 1e9;
		for (int i = -5; i < 5; i++) {
			for (int j = -5; j < 5; j++) {
				int px = x0, py = y0;

				int qx, qy;
				if (ABS(i) % 2) qx = (i * a) + a - x1;
				else qx = (i * a) + x1;
				if (ABS(j) % 2) qy = (j * b) + b - y1;
				else qy = (j * b) + y1;

				if (check(qx, qy, px, py, a, b)) {
					double now = S(qx - px) + S(qy - py);
					ret = MIN(ret, now);
				}


			}
		}
		return sqrt(ret);
    }

};

// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
	{
		Polyline theObject;
		eq(0, theObject.length(2, 2, 1, 1, 1, 1), 5.6568);
	}
	{
        Polyline theObject;
        eq(0, theObject.length(4, 3, 1, 1, 3, 2),7.810249675906654);
    }
    {
        Polyline theObject;
        eq(1, theObject.length(4, 3, 1, 1, 2, 2),8.602325267042627);
    }
    {
        Polyline theObject;
        eq(2, theObject.length(4, 3, 1, 1, 1, 2),9.433981132056603);
    }
    {
        Polyline theObject;
        eq(3, theObject.length(50, 70, 20, 40, 20, 40),172.04650534085255);
    }
    {
        Polyline theObject;
        eq(4, theObject.length(98, 200, 78, 32, 35, 174),299.9549966244937);
    }
}
// END CUT HERE
