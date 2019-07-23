#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <ctime>
#include <vector>
#include <fstream>
#include <list>
#include <iomanip>
#include <numeric>
using namespace std;
#define ll long long
#define ull unsigned long long
#define REP(i, lim) for(int i=0;i<lim;++i)
#define REPP(i, lim) for(int i=1;i<=lim;++i)
#define FOR(i,l,r)  for(int i=l;i<r;++i)
#define clr(s) memset(s, 0, sizeof(s))
#define lowclr(s) memset(s, -1, sizeof(s))
const int inf = 0x3f3f3f3f;
const int MAXN = 2000055;

double len[MAXN], dis[MAXN], spd[MAXN];

inline double mymax(double a, double b) {
    return (a>b) ? a:b;
}

int main()
{
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
//    std::ios::sync_with_stdio(false); cin.tie(0);

    int n;
    while(~scanf("%d", &n)) {
        double tot = 0;
        REP(i, n + 1) scanf("%lf", len+i);
        REP(i, n + 1) scanf("%lf", dis+i);
        REP(i, n + 1) scanf("%lf", spd+i);

        double ans = dis[0]/spd[0];

        REPP(i, n) {
            tot += len[i];
            ans = mymax(ans, (tot + dis[i]) / spd[i]);
        }

        printf("%.10lf\n", ans)
    }

    return 0;
}
