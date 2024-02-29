#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5, M = 1e6+5;
int n, m, t, vis[M]/*判断操作是否有被使用*/, ys[M], kk, u, tot, zhan[N], aa[N], lst, lll;
unordered_map<int,int> as[M];
char s[15];
queue <int> q;
deque <int> az[N];
vector <int> yos[M], to[N]/*每个数作为哪些操作1的未知值*/;
struct tree {
	int tr[N]/*当前值*/, sum[N<<2], op[N]/*是否属于S*/;
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		if(l == r) {
			tr[l]=2, op[l]=0;
			sum[k]=1;
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		sum[k]=sum[ls]+sum[rs];
	}
	void updt(int k, int l, int r, int to, int ww) {//普通赋值
		if(l == r) {
			tr[l]=ww, op[l]=0, sum[k]=(tr[l]&&!op[l]);
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls, l, mid, to, ww);
		else
			updt(rs, mid+1, r, to, ww);
		sum[k]=sum[ls]+sum[rs];
	}
	void updtt(int k, int l, int r, int to, int ww) {//强制赋值(GET)
		if(l == r) {
			tr[l]=ww, op[l]=1, sum[k]=(tr[l]&&!op[l]);
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updtt(ls, l, mid, to, ww);
		else
			updtt(rs, mid+1, r, to, ww);
		sum[k]=sum[ls]+sum[rs];
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq && l == r) {
			if(tr[l] && !op[l])
				return l;
			return M;
		}
		int mid = ((l+r)>>1), ret = M;
		if(lq <= mid && sum[ls] != 0)
			ret=ask(ls, l, mid, lq, rq);
		if(ret == M && mid < rq && sum[rs] != 0)
			ret=ask(rs, mid+1, r, lq, rq);
		return ret;
	}
}A;

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
void dfs1(int x, int r) {//不早于r的涉及x的操作1均为1
	// debug(az[x].size(), az[x].empty(), "????????\n");
	q.push(x);
	aa[x]=1, zhan[++tot]=x;
	while(!q.empty()) {
		x=q.front(); q.pop();
		while(!az[x].empty()) {
			int it = az[x].back();
			if(it >= r) {
				az[x].pop_back();
				if(!vis[it]) {
					for(int y : yos[it]) {
						if(A.tr[y] != 1)
							A.updt(1, 1, n, y, 1);
						if(!aa[y])
							q.push(y), aa[y]=1, zhan[++tot]=y;
					}
					vis[it]=1;
					// debug(ys[it], "???\n");
					// if(ys[it] == 0)
					// 	debug("!!!\n");
					// if(ys[it] == 1)
					// 	debug("!?!?\n");
				}
			}
			else
				break;
		}
	}
	while(tot) 
		aa[zhan[tot]]=0, --tot;
}
void dfs(int x, int r) {//涉及x的操作1均为0
	q.push(x);
	aa[x]=1, zhan[++tot]=x;
	while(!q.empty()) {
		x=q.front(); q.pop();
		// debug(x, az[x].size(), "!: ");
		while(!az[x].empty()) {
			int it = az[x].front();
			// debug(it), debug(' ');
			if(it <= r) {
				az[x].pop_front();
				if(!vis[it]) {
					for(int y : yos[it]) {
						if(az[y].back() <= r && A.tr[y] == 2) {
							// if(y == 1485)
							// 	debug("!?!?!?\n");
							A.updt(1, 1, n, y, 0);
						}
						else
							A.updt(1, 1, n, y, 2);
						if(!aa[y])
							q.push(y), aa[y]=1, zhan[++tot]=y;
					}
					vis[it]=1;
				}
			}
			else 
				break;
		}
		// debug('\n');
	}
	while(tot) {
		// to[zhan[tot]].clear();
		aa[zhan[tot]]=0, --tot;
	}
}
void opop(int &x) {
	x=(x-1+t*lst)%n+1;
}

signed main() {
	File("array");
	read(n), read(m), read(t);
	A.built(1, 1, n);
	for(int i = 1; i <= m; ++i) {
		scanf("%s", s+1);
		read(kk);
		// printf("%d:\n", i);
		if(s[1] == 'M') {
			int pd = 0, pd2 = 0;
			// printf("MERGE %d\n", kk);
			// int pp = kk;
			while(kk--)
				read(u), opop(u)/*, printf("%d ", u)*/, 
				pd|=(A.tr[u] == 1), pd2+=(A.tr[u] == 2), 
				az[u].push_back(i), yos[i].push_back(u);
			// if(pp)
			// 	puts("");
			if(pd) {
				vis[i]=1;
				for(int y : yos[i]) {
					az[y].pop_back();
					if(A.tr[y] != 1)
						A.updt(1, 1, n, y, 1);
				}
			}
			else
				if(pd2) {
					// ys[i]=pd2;
					for(int y : yos[i]) 
						if(A.tr[y] == 0)
							A.updt(1, 1, n, y, 2);
						// else
						// 	to[y].push_back(i), as[i][y]=1;
				}
				else {
					vis[i]=1;//全0，无效操作
					for(int y : yos[i]) 
						az[y].pop_back();
				}
		}
		if(s[1] == 'G') {
			opop(kk);
			read(u);
			// printf("GET %d %d\n", kk, u);
			A.updtt(1, 1, n, kk, u);
			if(u) {
				if(!az[kk].empty())
					dfs1(kk, az[kk].back());
			}
			else {
				if(!az[kk].empty())
					dfs(kk, az[kk].back());
			}
		}
		if(s[1] == 'Q') {
			++lll;
			opop(kk);
			// if(lll == 139) {
			// 	debug(kk, i, A.tr[270], A.tr[271], A.op[270], A.op[271], '\n');
			// 	exit(0);
			// }
			// printf("QUERY %d\n", kk);
			if(A.sum[1] == 0) {
				lst=0;
				puts("YES");
				continue;
			}
			putchar('N'), putchar('O'), putchar(' ');
			int ans = A.ask(1, 1, n, kk, n);
			if(ans == M)
				ans=A.ask(1, 1, n, 1, kk);
			write(lst=ans, '\n');
		}
		// for(int i = 1; i <= n; ++i)
		// 	write(A.tr[i], ' ');
		// puts("");
		// for(int i = 1; i <= n; ++i)
		// 	write(A.op[i], ' ');
		// puts("");
		// puts("");
	}
	return 0;
}