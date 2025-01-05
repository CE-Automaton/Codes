#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 4e5+5;
int t, n, nb[2][N], kk[N], cnt, dd[N<<1];
struct qwq {
	int w, pd, d;
}b[N<<1];
struct qvq {
	int r, w;
	bool operator <(const qvq& A) const {
		return A.r < r;
	}
};
vector <qvq> ad[N<<1];
priority_queue <qvq> q;

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
int comp(qwq A, qwq B) {
	return A.w < B.w;
}

signed main() {
	File("balloon");
	read(t);
	while(t--) {
		read(n);
		for(int i = 1; i <= n; ++i)
			read(nb[0][i]), read(nb[1][i]), read(kk[i]), 
			b[(i<<1)-1]=qwq{nb[0][i], 0, i}, b[(i<<1)]=qwq{nb[1][i], 1, i};
		sort(b+1, b+1+n+n, comp);
		cnt=0;
		for(int i = 1; i <= n+n; ++i) {
			if(i == 1 || b[i].w != b[i-1].w)
				dd[++cnt]=b[i].w;
			nb[b[i].pd][b[i].d]=cnt;
		}
		for(int i = 1; i <= cnt; ++i)
			ad[i].clear()/*, debug(dd[i]), debug(' ')*/;
		// debug('\n');
		// for(int i = 1; i <= n; ++i)
		// 	debug(nb[0][i], nb[1][i], kk[i], "??????\n");
		while(!q.empty()) q.pop();
		for(int i = 1; i <= n; ++i)
			ad[nb[0][i]].push_back(qvq {nb[1][i], kk[i]});
		int pd = 1;
		for(int i = 1; i <= cnt && pd; ++i) {
			int ln = dd[i]-dd[i-1]-1;//给dd[i-1]+1~dd[i]-1放气球
			while(!q.empty() && ln) {
				qvq it = q.top(); q.pop();
				if(it.r < i) {
					// debug(it.r, i, it.w, "???\n");
					pd=0;
					break;
				}
				int op = min(ln, it.w);
				it.w-=op, ln-=op;
				if(it.w)
					q.push(it);
			}
			for(int j = 0; j < ad[i].size(); ++j)
				q.push(ad[i][j]);
			ln = 1;//给dd[i]位置放气球
			while(!q.empty() && ln) {
				qvq it = q.top(); q.pop();
				if(it.r < i) {
					// debug(it.r, cnt, it.w, "???\n");
					pd=0;
					break;
				}
				int op = min(ln, it.w);
				it.w-=op, ln-=op;
				if(it.w)
					q.push(it);
			}
		}
		if(!q.empty())
			pd=0;
		if(pd)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}