#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
#define inf 1000000007
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, k, d[N], zhan[N], tot, vis[N], huan[N], cnt, ans, gs[N], mdep[N], pd[N], rt;
vector <int> to[N];

namespace FastIO {
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=obuf;
	char* flush(){fwrite(obuf,1,oT-oS,stdout);return oT=obuf;}
	struct Flusher{~Flusher(){flush();}}flusher;
	inline char gc(){return iS==iT && (iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT)?EOF:*iS++;}
	inline void pc(char c){if(oT==oS+SIZE) flush();*oT++=c;}
	#define getchar gc
	#define putchar pc
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
}
using FastIO::gc;
using FastIO::pc;
using FastIO::read;
using FastIO::write;
int dfs(int x, int dep) {
	mdep[x]=dep;
	int ret = 0;
	vis[x]=1;
	for(int y : to[x]) 
		if(y != 1 && y != rt)
			ret+=dfs(y, dep+1), mdep[x]=max(mdep[x], mdep[y]);
	int pd = 0;
	if(mdep[x]-dep >= k-1) 
		++ret, mdep[x]=dep-1, pd = 1;
	return ret+(pd == 0 && x == rt);
}

signed main() {
	File("lost");
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		read(d[i]);
	if(k == 1) {
		for(int i = 1; i <= n; ++i)
			ans+=(d[i] != 1);
		write(ans, '\n');
		FastIO::flusher.~Flusher();
		return 0;
	}
	ans=(d[1] != 1);
	for(int i = 2; i <= n; ++i)
		to[d[i]].push_back(i);
	rt=1;
	for(int y : to[1])
		ans+=dfs(y, 1);
	for(int i = 2; i <= n; ++i) 
		if(!vis[i]) {
			// debug(i, "...\n");
			tot=0;
			zhan[++tot]=i, vis[i]=1;
			int now = d[i];
			while(!vis[now]) {
				zhan[++tot]=now, vis[now]=tot;
				now=d[now];
			}
			cnt=0;
			for(int j = vis[now]; j <= tot; ++j)
				huan[++cnt]=zhan[j];
			for(int j = 1; j <= cnt; ++j) 
				huan[cnt+j]=huan[j], pd[j]=pd[j+cnt]=0, gs[j]=gs[cnt+j]=0;
			if(n > 2000) {
				int fr = 0;
				for(int j = 1; j <= cnt; ++j) {
					mdep[huan[j]]=1;
					for(int y : to[huan[j]])
						if(y != huan[j+1])
							dfs(y, 2), mdep[huan[j]]=max(mdep[huan[j]], mdep[y]);
					if(mdep[huan[j]]-1 >= k-1)
						mdep[huan[j]]=0, pd[j]=1, fr=j, ++ans;
					else
						--mdep[huan[j]];
				}
				if(fr) {
					for(int j = fr-1; j >= 1; --j) {
						if(pd[j]) continue;
						if(mdep[j] >= k-1)
							mdep[j]=0, ++ans;
						if(j == 1) 
							mdep[huan[cnt]]=max(mdep[huan[cnt]], mdep[huan[j]]+1);
						else 
							mdep[huan[j-1]]=max(mdep[huan[j-1]], mdep[huan[j]]+1);
					}
					for(int j = cnt; j > fr; --j) {
						if(pd[j]) continue;
						if(mdep[j] >= k-1)
							mdep[j]=0, ++ans;
						if(j == 1) 
							mdep[huan[cnt]]=max(mdep[huan[cnt]], mdep[huan[j]]+1);
						else 
							mdep[huan[j-1]]=max(mdep[huan[j-1]], mdep[huan[j]]+1);
					}
				}
				else {
					int mx = 1;
					for(int j = 2; j <= cnt; ++j)
						if(mdep[huan[j]] > mdep[huan[mx]])
							mx=j;
					if(mdep[huan[mx]]+cnt-1 < k-1) continue;
					int nd = k-1-mdep[huan[mx]];
					fr = (mx-nd <= 0 ? cnt-mx+nd : mx-nd);
					for(int j = fr-1; j >= 1; --j) {
						if(mdep[j] >= k-1)
							mdep[j]=0, ++ans;
						if(j == 1) 
							mdep[huan[cnt]]=max(mdep[huan[cnt]], mdep[huan[j]]+1);
						else 
							mdep[huan[j-1]]=max(mdep[huan[j-1]], mdep[huan[j]]+1);
					}
					for(int j = cnt; j > fr; --j) {
						if(mdep[j] >= k-1)
							mdep[j]=0, ++ans;
						if(j == 1) 
							mdep[huan[cnt]]=max(mdep[huan[cnt]], mdep[huan[j]]+1);
						else 
							mdep[huan[j-1]]=max(mdep[huan[j-1]], mdep[huan[j]]+1);
					}
				}
			}
			else {
				int mn = inf;
				for(int j = 1; j <= cnt; ++j) {
					rt=huan[j];
					mn=min(mn, dfs(huan[j], 1));
				}
				ans+=mn;
			}
		}
	FastIO::flusher.~Flusher();
	write(ans, '\n');
	return 0;
}