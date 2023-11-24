#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5+5;
int n, m, q, u, v, cnt/*大节点个数*/, jp1[25][N], dfn[N], tot, siz[N], az[N], rt[N], sum[N], dep[N], 
jp2[25][N], len[25][N], dep2[N];
vector <int> to[N], tto[N];
struct node {//大节点 
	int rt/*根节点*/, fa/*根节点连接的小节点的x*/, fart/*这个大节点连接的大节点*/;
}d[N];
struct tree {//主席树 
	int gs;
	struct nnode {
		int ls, rs, cs;
	}tr[N*20];
	void updt(int& k, int l, int r, int to) {
		tr[++gs]=tr[k], k=gs;
		if(l == r) {
			++tr[k].cs;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid) updt(tr[k].ls, l, mid, to);
		else updt(tr[k].rs, mid+1, r, to);
		tr[k].cs=tr[tr[k].ls].cs+tr[tr[k].rs].cs;
	}
	int ask_k(int k1, int k2, int l, int r, int k) {
		if(l == r)
			return l;
		int mid = ((l+r)>>1), kk = tr[tr[k1].ls].cs-tr[tr[k2].ls].cs;
		if(k <= kk) return ask_k(tr[k1].ls, tr[k2].ls, l, mid, k);
		else return ask_k(tr[k1].rs, tr[k2].rs, mid+1, r, k-kk);
	}
}A;

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
void dfs(int x, int fa) {
	siz[x]=1, dfn[x]=++tot, az[tot]=x, dep[x]=dep[fa]+1;
	jp1[0][x]=fa;
	for(int i = 1; i <= 20; ++i)
		jp1[i][x]=jp1[i-1][jp1[i-1][x]];
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), siz[x]+=siz[y];
}
int ask_lp(int l, int r, int k) {
	return A.ask_k(rt[r], rt[l-1], 1, n, k);
}
void dfs2(int x, int fa) {
	dep2[x]=dep2[fa]+1;
	len[0][x]=dep[d[x].fa]-dep[d[fa].rt]+1;//从这个大节点的根节点跳到上一个大节点的根节点 
	jp2[0][x]=fa;
	for(int i = 1; i <= 20; ++i)
		jp2[i][x]=jp2[i-1][jp2[i-1][x]], len[i][x]=len[i-1][x]+len[i-1][jp2[i-1][x]];
	for(int y : tto[x])
		if(y != fa)
			dfs2(y, x);
}
int jump(int x, int y) {
	int ret = 0;
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 20; i >= 0; --i)
		if(dep[jp1[i][x]] >= dep[y]) 
			ret+=dep[x]-dep[jp1[i][x]], x=jp1[i][x];
	for(int i = 20; i >= 0; --i)
		if(jp1[i][x] != jp1[i][y]) 
			ret+=dep[x]-dep[jp1[i][x]]+dep[y]-dep[jp1[i][y]], x=jp1[i][x], y=jp1[i][y];
	if(x != y)
		ret+=dep[x]-dep[jp1[0][x]]+dep[y]-dep[jp1[0][y]], x=jp1[0][x], y=jp1[0][y];
	return ret;
}

signed main() {
	read(n), read(m), read(q);
	for(int i = 1; i <= n-1; ++i) 
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	d[++cnt]=(node) {1, 0, 0};
	dfs(1, 0); 
	for(int i = 1; i <= n; ++i) 
		rt[i]=rt[i-1], A.updt(rt[i], 1, n, az[i]);
	sum[1]=siz[1];
	
	for(int i = 1; i <= m; ++i) {
		read(u), read(v);
		int l = 1, r = cnt, ans = 0;
		while(l <= r) {//找到连接的大节点 
			int mid = ((l+r)>>1);
			if(sum[mid] >= v)
				ans=mid, r=mid-1;
			else
				l=mid+1;
		}
		d[++cnt]=(node) {u, ask_lp(dfn[d[ans].rt], dfn[d[ans].rt]+siz[d[ans].rt]-1, v-sum[ans-1]), ans};
		tto[ans].push_back(cnt);
		sum[cnt]=sum[cnt-1]+siz[u];
	}
	dfs2(1, 0);
//	for(int i = 1; i <= cnt; ++i)
//		cout<<"<"<<i<<"> rt:"<<d[i].rt<<" fa:"<<d[i].fa<<" BIG_fa:"<<d[i].fart<<"\n";
	
	for(int i = 1; i <= q; ++i) {
		read(u), read(v);
		int l = 1, r = cnt, ub = 0, vb = 0;
		while(l <= r) {//找到u属于的大节点 
			int mid = ((l+r)>>1);
			if(sum[mid] >= u)
				ub=mid, r=mid-1;
			else
				l=mid+1;
		}
		u=ask_lp(dfn[d[ub].rt], dfn[d[ub].rt]+siz[d[ub].rt]-1, u-sum[ub-1]);
		l = 1, r = cnt;
		while(l <= r) {//找到v属于的大节点 
			int mid = ((l+r)>>1);
			if(sum[mid] >= v)
				vb=mid, r=mid-1;
			else
				l=mid+1;
		}
		v=ask_lp(dfn[d[vb].rt], dfn[d[vb].rt]+siz[d[vb].rt]-1, v-sum[vb-1]);
//		cout<<ub<<"-"<<u<<" "<<vb<<"-"<<v<<"\n";
		int ans = 0;
		if(ub == vb) {
			ans=jump(u, v);
			write(ans, '\n');
		}
		else {
			if(dep2[ub] < dep2[vb]) swap(ub, vb), swap(u, v);
			ans+=dep[u]-dep[d[ub].rt];//u先跳到大点的根节点
			for(int i = 20; i >= 0; --i)
				if(dep2[jp2[i][ub]] > dep2[vb]) //先不跳到同一深度,万一等会儿直接ub=vb了 
					ans+=len[i][ub], ub=jp2[i][ub];
//			cout<<ub<<" "<<vb<<"\n";
			if(vb == jp2[0][ub]) {
				++ans, u=d[ub].fa;
//				cout<<u<<" "<<v<<" "<<ans<<"\n";
				ans+=jump(u, v);
			}
			else {//v一定会跳到根节点,可以直接跳到同一深度,正常跳大节点,跳到最后在lca所在大节点找lca即可 
				ans+=dep[v]-dep[d[vb].rt];
				if(dep2[ub] != dep2[vb])
					ans+=len[0][ub], ub=jp2[0][ub];
				for(int i = 20; i >= 0; --i)
					if(jp2[i][ub] != jp2[i][vb]) 
						ans+=len[i][ub]+len[i][vb], ub=jp2[i][ub], vb=jp2[i][vb];
				++ans, u=d[ub].fa;
				++ans, v=d[vb].fa;
//				cout<<ans<<" "<<u<<" "<<v<<"!?\n";
				ans+=jump(u, v);
			} 
			write(ans, '\n');
		}
	}
	return 0;
}
