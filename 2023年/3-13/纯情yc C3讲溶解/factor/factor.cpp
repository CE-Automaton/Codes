#include <bits/stdc++.h>
#define int long long
#define uLL unsigned long long
#define mod 1000000007
using namespace std;
const uLL base = 1000000007;
int n, m, a[10005], cnt, az, l[1000006], r[1000006], to[1000006], opop[1000006];
vector <int> qwq[1000006];
unordered_map<uLL, int> haha;

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}

void solve(int n, int m) {
    for(int i = 1; i <= 1000000; ++i)
        l[i]=i-1, r[i]=i+1, to[i]=0, qwq[i].clear();
    r[0]=1;
    for(int j = 1; j <= n; ++j) {
        int ppp = a[j];
        for(int i = 2; i*i <= ppp; ++i)
            while(ppp%i == 0)
                qwq[j].push_back(i), ppp/=i;
        if(ppp != 1)
            qwq[j].push_back(ppp);
    }
    cnt=az=n;
    for(int i = 1; i <= m; ++i) {
        int lst = az;
        for(int j = r[0], o = 1; o <= lst; ++o, j=r[j]) {
            qwq[cnt+1].push_back(qwq[j][to[j]]);
            ++to[j];
            if(qwq[j].size() == to[j]) {
                r[l[j]]=r[j];
                l[r[j]]=l[j];
                --az;
            }
        }
        ++cnt;
        ++az;
        sort(qwq[cnt].begin(), qwq[cnt].end());
    }
    write(az), putchar('\n');
    for(int j = r[0], o = 1; o <= az; ++o, j=r[j]) {
        int now = 1;
        for(int i = to[j]; i < qwq[j].size(); ++i)
            now=1LL*now*qwq[j][i]%mod;
        write(now), putchar(' ');
    }
}

signed main() {
    freopen("factor.in", "r", stdin);
    freopen("factor.out", "w", stdout);
    read(n), read(m);
    for(int i = 1; i <= n; ++i)
        read(a[i]);
    if(n == 1 || m >= 1000000000 || n*m >= 1000000) {
        for(int i = 1; i <= 1000000; ++i)
            l[i]=i-1, r[i]=i+1;
        r[0]=1;
        for(int j = 1; j <= n; ++j) {
            int ppp = a[j];
            for(int i = 2; i*i <= ppp; ++i)
                while(ppp%i == 0)
                    qwq[j].push_back(i), ppp/=i;
            if(ppp != 1)
                qwq[j].push_back(ppp);
        }
        cnt=az=n;
        for(int i = 1; i <= m; ++i) {
            int lst = az;
            for(int j = r[0], o = 1; o <= lst; ++o, j=r[j]) {
                qwq[cnt+1].push_back(qwq[j][to[j]]);
                ++to[j];
                if(qwq[j].size() == to[j]) {
                    r[l[j]]=r[j];
                    l[r[j]]=l[j];
                    --az;
                }
            }
            ++cnt;
            ++az;
            sort(qwq[cnt].begin(), qwq[cnt].end());
            for(int j = r[0], o = 1; o <= az; ++o, j=r[j]) {
                int now = 1;
                for(int i = to[j]; i < qwq[j].size(); ++i)
                    now=1LL*now*qwq[j][i]%mod;
                opop[o]=now;
            }
            sort(opop+1, opop+1+az);
            uLL ha = 0;
            for(int j = 1; j <= az; ++j)
                ha=ha*base+opop[j];
            if(haha.find(ha) != haha.end()) {
                int st = haha[ha], fn = i-1;
                m=st+(m-st)%(fn-st+1);
                solve(n, m);
                exit(0);
            }
            haha[ha]=i;
        }
        write(az), putchar('\n');
        for(int j = r[0], o = 1; o <= az; ++o, j=r[j]) {
            int now = 1;
            for(int i = to[j]; i < qwq[j].size(); ++i)
                now=1LL*now*qwq[j][i]%mod;
            write(now), putchar(' ');
        }
        return 0;
    }
    solve(n, m);
	return 0;
}