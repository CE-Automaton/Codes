#include <bits/stdc++.h>
#define rg register
#define pc putchar
#define gc getchar
#define pf printf
#define space pc(' ')
#define enter pc('\n')
#define me(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define FOR(i,k,t,p) for(rg int i(k) ; i <= t ; i += p)
#define ROF(i,k,t,p) for(rg int i(k) ; i >= t ; i -= p)
using namespace std ;
bool s_gnd ;
inline void read(){}
template<typename T,typename ...T_>
inline void read(T &x,T_&...p)
{
    x = 0 ;rg int f(0) ; rg char c(gc()) ;
    while(!isdigit(c)) f |= (c=='-'),c = gc() ;
    while(isdigit(c)) x = (x<<1)+(x<<3)+(c^48),c = gc() ;
    x = (f?-x:x) ;
    read(p...);
}
int stk[30],tp ;
inline void print(){}
template<typename T,typename ...T_>
inline void print(T x,T_...p)
{
    if(x < 0) pc('-'),x = -x ;
    do stk[++tp] = x%10,x /= 10 ; while(x) ;
    while(tp) pc(stk[tp--]^48) ; space ;
    print(p...) ;
}
bool S_GND ;
const int N = 2e5+5 ;
char s[2][N],pp[N<<1] ;
mt19937 rd(time(0)) ;
signed main()
{
//cerr<<(double)(&s_gnd-&S_GND)/1024.0/1024.0 ;
//	freopen(".in","r",stdin) ;
	freopen("family.in","w",stdout) ;
    int n = 200000,q = 100 ; print(n,q),enter ;
    FOR(i,0,1,1) FOR(j,1,n,1) s[i][j] = (rd()%1000)?'.':'X',pp[i*n+j] = s[i][j] ;
    FOR(i,0,1,1)
    {
        FOR(j,1,n,1) cout<<s[i][j] ; enter ;
    }
    while(q--)
    {
        int x = rd()%(2*n)+1,y = rd()%(2*n)+1 ;
        while(pp[x] == 'X') x = rd()%(2*n)+1 ;
        while(pp[y] == 'X') y = rd()%(2*n)+1 ;
        print(x,y),enter ;
    }
    return 0 ;
}
