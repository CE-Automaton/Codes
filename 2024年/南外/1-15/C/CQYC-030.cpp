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
const int N = 200 ;
const int M = 4782990 ;
int n,m ;
int a[N][N] ;
char s[N][N],t[N][N] ;
int f[M],g[M],pw[N] ;
signed main()
{
//cerr<<(double)(&s_gnd-&S_GND)/1024.0/1024.0 ;
	freopen("daredevil.in","r",stdin) ;
	freopen("daredevil.out","w",stdout) ;
    read(n,m) ;
    FOR(i,1,n,1) scanf("%s",s[i]+1) ;
    if(n < m)
    {
        FOR(i,1,n,1) FOR(j,1,m,1) t[j][i] = s[i][j] ;
        swap(n,m) ; FOR(i,1,n,1) FOR(j,1,m,1) s[i][j] = t[i][j] ;
    }
    FOR(i,1,n,1) FOR(j,1,m,1) a[i][j] = s[i][j]-'0' ;
    // FOR(i,0,pw[m+1]-1,1) f[i] = M ;
    me(f,0x3f) ;
    pw[0] = 1,f[0] = 0 ; FOR(i,1,16,1) pw[i] = pw[i-1]*3 ;
    FOR(i,1,n,1) 
    {
        FOR(j,1,m,1)
        {
            FOR(S,0,pw[m+1]-1,1) g[S] = M ;
            FOR(S,0,pw[m+1]-1,1) if(f[S] < M)
            {
                int x = S/pw[j]%3,y = S%3 ;
                if(a[i][j] != 1)
                {
                    if(!x && !y) g[S+pw[j]] = min(g[S+pw[j]],f[S]),g[S+1] = min(g[S+1],f[S]) ;
                    else g[S] = min(g[S],f[S]) ;
                    g[S-x*pw[j]+pw[j]*2-y+2] = min(g[S-x*pw[j]+pw[j]*2-y+2],f[S]+1) ;
                }
                if(a[i][j] != 0 && x != 1 && y != 1) g[S-x*pw[j]-y] = min(g[S-x*pw[j]-y],f[S]) ;
            }
            FOR(S,0,pw[m+1]-1,1) f[S] = g[S] ; 
        }
        FOR(S,0,pw[m+1]-1,3) f[S] = min(f[S],f[S+2]),f[S+1] = f[S+2] = M ;
    }
    int ans = M ;
    FOR(S,0,pw[m+1]-1,3)
    {
        int chk = 0 ; 
        FOR(j,1,m,1) if(S/pw[j]%3 == 1) {chk = 1 ; break ;}
        if(chk) continue ; ans = min(ans,f[S]) ;
    }
    print(ans),enter ;
    return 0 ;
}
