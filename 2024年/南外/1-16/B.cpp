#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, m, xx, a[3], b[3], bs[3][3]={{1,1,0},{1,2,1},{2,2,1}};
int upd(int x) {
    return (x >= mod ? x-mod : x);
}
struct matr {
    int a[3][3];
    void clear() {
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                a[i][j]=0;
    }
    matr operator *(const matr& A) const {
        matr ret; ret.clear();
        for(int i = 0; i < 3; ++i)
            for(int k = 0; k < 3; ++k)
                for(int j = 0; j < 3; ++j)
                    ret.a[i][j]=upd(ret.a[i][j]+1LL*a[i][k]*A.a[k][j]%mod);
        return ret;
    }
}pw[31], op;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}

signed main() {
    File("count");
	read(n), read(m);
    a[0]=0, a[1]=1, a[2]=0;
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            pw[0].a[i][j]=bs[i][j];
    for(int i = 1; i <= 29; ++i)
        pw[i]=pw[i-1]*pw[i-1];
    int lst = 1, gs = 0;
    for(int i = 1; i <= m; ++i) {
        read(xx);
        gs = xx-lst+1;
        if(gs)
            for(int j = 0; j <= 29; ++j)
                if((gs>>j)&1) {
                    for(int k = 0; k < 3; ++k)
                        b[k]=a[k], a[k]=0;
                    for(int k = 0; k < 3; ++k)
                        for(int o = 0; o < 3; ++o)
                            a[o]=upd(a[o]+1LL*b[k]*pw[j].a[k][o]%mod);
                }
        a[1]=upd(a[1]-a[0]+mod);//!!!!!
        lst=xx+1;
    }
    gs=n-lst+1;
    for(int j = 0; j <= 29; ++j)
        if((gs>>j)&1) {
            for(int k = 0; k < 3; ++k)
                b[k]=a[k], a[k]=0;
            for(int k = 0; k < 3; ++k)
                for(int o = 0; o < 3; ++o)
                    a[o]=upd(a[o]+1LL*b[k]*pw[j].a[k][o]%mod);
        }
    write(a[0], '\n');
	return 0;
}