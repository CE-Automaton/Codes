#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e6+5;
int n, l[N], r[N], mx, gs, tot, zhan[N];
char s[N];

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
void check(int k) {
    tot=0;
    // debug(k, ":\n");
    for(int i = 1; i <= gs; ++i) {
        int qwq = l[i]-r[i-1]-2-k;
        // debug(qwq, "!?\n");
        if(qwq < 0) return ;
        else if(qwq) {
            if(!k || qwq == 1) return ;
            else {
                if(qwq&1) {
                    if(k <= 1) return ;
                    zhan[++tot]=2, qwq-=3;
                }
                while(qwq) zhan[++tot]=1, qwq-=2;
            }
        }
        zhan[++tot]=r[i]-l[i]+1+k;
    }
    int qwq = n-r[gs]-k;
    if(qwq < 0) return ;
    else if(qwq) {
        if(!k || qwq == 1) return ;
        else {
            if(qwq&1) {
                if(k <= 1) return ;
                zhan[++tot]=2, qwq-=3;
            }
            while(qwq) zhan[++tot]=1, qwq-=2;
        }
    }
    puts("Yes");
    for(int j = 1; j <= tot; ++j) {
        for(int i = 1; i <= zhan[j]; ++i)
            putchar('F');
        if(j != tot)
            putchar('T');
    }
    for(int i = 1; i <= k; ++i)
        putchar('T');
    exit(0);
}

signed main() {
    // File("exam");
    read(n);
    scanf("%s", s+1);
    r[0]=-1;
    mx=n;
    for(int i = 1; i <= n; ++i) 
        if(s[i] == '1') {
            ++gs, l[gs]=r[gs]=i;
            while(r[gs]+1 <= n && s[r[gs]+1] == '1')
                ++r[gs];
            mx=min(mx, l[gs]-r[gs-1]-2);
            i=r[gs];
        }
    if(!gs) {
        puts("Yes");
        for(int i = 1; i <= n; ++i)
            putchar('T');
        return 0;
    }
    mx=min(mx, n-r[gs]);
    mx=min(mx, 4);
    debug(mx, "!?\n");
    for(int k = 0; k <= mx; ++k)
        check(k);
    puts("No");
	return 0;
}