#include <bits/stdc++.h>
using namespace std;
const int N = 3e6+5;
int n, zhan[N], r[N], tot, cnt, fa[N], dep[N], ans;
char s[N];

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
    freopen("bracket.in", "r", stdin);
    freopen("bracket.out", "w", stdout);
	scanf("%s", s+1);
    n=strlen(s+1);
    int now = 0;
    for(int i = 1; i <= n; ++i) {
        if(s[i] == '(')
            ++now;
        else
            --now;
        if(now < 0) {
            puts("-1");
            return 0;
        }
    }
    for(int i = 1; i <= n; ++i) {
        dep[i]=1;
        if(s[i] == '(')
            zhan[++tot]=i;
        else
            r[i]=zhan[tot], --tot;
    }
    tot=0;
    for(int i = n; i >= 1; --i) 
        if(s[i] == ')') {
            while(tot && r[zhan[tot]] > i) --tot;
            if(tot) 
                fa[i]=zhan[tot];
            zhan[++tot]=i;
        }
    for(int i = 1; i <= n; ++i)
        if(fa[i])
            dep[fa[i]]=max(dep[fa[i]], dep[i]+1);
    for(int i = 1; i <= n; ++i)
        ans=max(dep[i], ans);
    write(n-ans*2, '\n');
	return 0;
}