#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 2e5+5;
int t, n, u, v, in[N], mn[N], mx[N];
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
int comp(int A, int B) {
	return mn[A] < mn[B];
}
void dfs(int x, int fa) {
	if(to[x].size() == 1)
		mn[x]=x;//mn为该子树内叶子节点最小值 
	else
		mn[x]=inf;
	for(int i = 0, y = 0; i < to[x].size(); ++i) {
		y=to[x][i];
		if(y == fa) continue;
		dfs(y, x);
		mn[x]=min(mn[x], mn[y]);
		mx[x]=(mn[y] > mn[mx[x]] ? y : mx[x]);
	}
}
void get_ans(int x, int fa, int pd/*判断当前是否有根节点*/, int ww/*判断是否能为根节点*/) {
	if(to[x].size() == 1) {
		write(x, ' ');
		return ;
	}
	sort(to[x].begin(), to[x].end(), comp);
	int az = 1;
	if(ww == 0)//不能为根,只能按后序遍历 
		az=1;
	else 
		if(pd == 0 && x < mn[mx[x]]/* && to[mx[x]].size() != 1*/)/*更优*/
			az=0;
	pd|=az;
	for(int i = 0, y = 0; i < to[x].size(); ++i) {
		y=to[x][i];
		if(y == fa || y == mx[x]) continue;
		get_ans(y, x, pd, 0/*因为x的其他子树没遍历完*/);
	}
	if(az)
		get_ans(mx[x], x, pd, 0/*因为x已经是根了*/), write(x, ' ');
	else
		write(x, ' '), get_ans(mx[x], x, pd, ww);
}

signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	read(t);
	while(t--) {
		read(n);
		for(int i = 2; i <= n; ++i)
			read(u), read(v), ++in[u], ++in[v], 
			to[u].push_back(v), to[v].push_back(u);
		int st = 0, tt = 0;
		for(int i = 1; i <= n; ++i)
			if(in[i] == 1) {
				st=i;
				break;
			}
		dfs(st, 0);
//		for(int i = 1; i <= n; ++i)
//			cout<<mn[i]<<"! "<<i<<" pd: "<<mx[i]<<" "<<mn[mx[i]]<<"\n";
		write(st, ' ');//这个最小的叶子节点一定先走 
		get_ans(to[st][0], st, 0, 1);
		putchar('\n');
		for(int i = 1; i <= n; ++i)
			mn[i]=mx[i]=in[i]=0, to[i].clear();
	}
	FastIO::flusher.~Flusher();
	return 0;
}
