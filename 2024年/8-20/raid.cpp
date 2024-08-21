#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 4e3+5, M = 8e5+5;
int X, k, n, q, a[N], b[N], c[N], t, d, fz[N], fm[N], dd[N], pp[N], tot, too;
LL ans[M];
struct qwq {
	int d, w;
};
vector <qwq> que[N];
struct qvq {
	int lz, lm, rz, rm;
	LL w;
	bool operator <(const qvq& A) const {
		return A.w > w;
	}
}zhan[N];
priority_queue <qvq> qq;

template <typename T> inline void debug(T x) { cerr<<x<<'\n'; }
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
int comp(int A, int B) {
	return 1LL*fz[A]*fm[B] < 1LL*fz[B]*fm[A];
}
int compp(qwq A, qwq B) {
	return A.d < B.d;
}

signed main() {
	read(X), read(k), read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i]), read(b[i]), read(c[i]);
	for(int i = 1; i <= q; ++i)
		read(t), read(d), que[t].push_back(qwq {d, i});
	for(int i = 1; i <= n; ++i) {
		if(que[i].size() == 0) continue;
		tot=0;
		LL sum = 0;
		for(int j = 1; j <= n; ++j)
			if(i != j) {
				if(a[j] > a[i]) {
					fz[++tot]=a[j]-a[i];
					fm[tot]=b[i]-b[j]+a[j]-a[i];
					dd[tot]=0;
					if(fm[tot] == 0) 
						sum+=c[j], --tot;
					else 
						if(fm[tot] > 0) {
							sum+=c[j];
							if(fz[tot] < fm[tot])
								dd[tot]=-c[j];
							else
								--tot;
						}
					else 
						if(fm[tot] < 0) 
							sum+=c[j], --tot;
				}
				else {
					fz[++tot]=a[j]-a[i];
					fm[tot]=b[i]-b[j]+a[j]-a[i];
					dd[tot]=0;
					if(fm[tot] == 0) 
						--tot;
					else
						if(fm[tot] > 0) 
							--tot;
					else
						if(fm[tot] < 0) {
							if(fz[tot] > fm[tot])
								dd[tot]=c[j];
							else 
								--tot;
						}
				}
			}
		fz[++tot]=1; fm[tot]=1;
		dd[tot]=0;
		for(int j = 1; j <= tot; ++j) {
			pp[j]=j;
			if(fz[j] < 0) fz[j]=-fz[j], fm[j]=-fm[j];
		}
		sort(que[i].begin(), que[i].end(), compp);
		sort(pp+1, pp+1+tot, comp);
		int lstz = 0, lstm = 1, op = 1;
		too=0;
		for(int j = 1; j <= tot; ++j) {
			if(j >= 2 && 1LL*fz[pp[j-1]]*fm[pp[j]] == 1LL*fz[pp[j]]*fm[pp[j-1]]/*判断分数相等不能用分子分母各自判断是否相同的办法！*/) {
				sum+=dd[pp[j]];
				lstz=fz[pp[j]], lstm=fm[pp[j]];
				continue;
			}
			zhan[++too]=qvq {lstz, lstm, fz[pp[j]], fm[pp[j]], sum};
			sum+=dd[pp[j]];
			lstz=fz[pp[j]], lstm=fm[pp[j]];
		}
		for(int j = 0; j < que[i].size(); ++j) {
			while(op <= too && 1LL*zhan[op].lz*X < 1LL*(que[i][j].d+k)*zhan[op].lm)
				qq.push(zhan[op]), ++op;
			while(!qq.empty() && 1LL*qq.top().rz*X <= 1LL*que[i][j].d*qq.top().rm/*注意相等的时候也要pop掉！！！*/)
				qq.pop();
			if(!qq.empty()) 
				ans[que[i][j].w]=qq.top().w;
		}
		while(!qq.empty()) qq.pop();
	}
	for(int i = 1; i <= q; ++i)
		write(ans[i], '\n');
	return 0;
}