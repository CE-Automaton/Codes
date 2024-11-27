#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 705;
int n, m, p, B, a[N][N], dp[2][N*N], sum[N][N], ans;
struct qwq {
	int xx, yy;
};
vector <qwq> to[N*N];
struct qvq {
	int xx, yy, ww;
}b[N*N];
queue <qvq> q;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
int comp(qvq A, qvq B) {
	return A.ww < B.ww;
}
void add(int xx, int yy, int ww) {
	if(sum[xx][yy] <= ww)
		return ;
	sum[xx][yy]=ww;
	if((xx^1) && (yy^1) && sum[xx-1][yy-1] > ww+1) {
		sum[xx-1][yy-1]=ww+1;
		q.push(qvq {xx-1, yy-1, ww+1});
	}
	if((xx^1) && (yy^m) && sum[xx-1][yy+1] > ww+1) {
		sum[xx-1][yy+1]=ww+1;
		q.push(qvq {xx-1, yy+1, ww+1});
	}
	if((xx^n) && (yy^1) && sum[xx+1][yy-1] > ww+1) {
		sum[xx+1][yy-1]=ww+1;
		q.push(qvq {xx+1, yy-1, ww+1});
	}
	if((xx^n) && (yy^m) && sum[xx+1][yy+1] > ww+1) {
		sum[xx+1][yy+1]=ww+1;
		q.push(qvq {xx+1, yy+1, ww+1});
	}
}

signed main() {
	File("barry");
	read(n), read(m), read(p);
	B=(int) sqrt(n*m*9);
	// debug(B, "?\n");
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			read(a[i][j]), to[a[i][j]].push_back(qwq {i, j});
	to[0].push_back(qwq {1, 1});
	dp[0][0]=0;
	int now = 0;
	for(int i = 1; i <= p; ++i) {
		now^=1;
		if(to[i-1].size() <= B || to[i].size() <= B) {
			for(int j = 0; j < to[i].size(); ++j)
				dp[now][j]=inf;
			for(int j = 0; j < to[i-1].size(); ++j)
				for(int k = 0; k < to[i].size(); ++k)
					dp[now][k]=min(dp[now][k], dp[now^1][j]+abs(to[i][k].xx-to[i-1][j].xx)+abs(to[i][k].yy-to[i-1][j].yy));
		}
		else {
			for(int o = 1; o <= n; ++o)
				for(int k = 1; k <= m; ++k)
					sum[o][k]=inf;
			int tot = 0, ll = 1;
			for(int j = 0; j < to[i-1].size(); ++j)
				b[++tot]=qvq {to[i-1][j].xx, to[i-1][j].yy, dp[now^1][j]};
			sort(b+1, b+1+tot, comp);
			add(b[1].xx, b[1].yy, b[1].ww);
			while(ll+1 <= tot && b[ll+1].ww == b[1].ww)
				++ll, add(b[ll].xx, b[ll].yy, b[ll].ww);
			while(!q.empty()) {
				qvq it = q.front(); q.pop();
				while(ll+1 <= tot && it.ww == b[ll+1].ww)
					++ll, add(b[ll].xx, b[ll].yy, b[ll].ww);
				if((it.xx^1) && (it.yy^1) && sum[it.xx-1][it.yy-1] > it.ww+1) {
					sum[it.xx-1][it.yy-1]=it.ww+1;
					q.push(qvq {it.xx-1, it.yy-1, it.ww+1});
				}
				if((it.xx^1) && (it.yy^m) && sum[it.xx-1][it.yy+1] > it.ww+1) {
					sum[it.xx-1][it.yy+1]=it.ww+1;
					q.push(qvq {it.xx-1, it.yy+1, it.ww+1});
				}
				if((it.xx^n) && (it.yy^1) && sum[it.xx+1][it.yy-1] > it.ww+1) {
					sum[it.xx+1][it.yy-1]=it.ww+1;
					q.push(qvq {it.xx+1, it.yy-1, it.ww+1});
				}
				if((it.xx^n) && (it.yy^m) && sum[it.xx+1][it.yy+1] > it.ww+1) {
					sum[it.xx+1][it.yy+1]=it.ww+1;
					q.push(qvq {it.xx+1, it.yy+1, it.ww+1});
				}
			}
			for(int k = 0; k < to[i].size(); ++k)
				dp[now][k]=sum[to[i][k].xx][to[i][k].yy];
		}
	}
	ans=inf;
	for(int i = 0; i < to[p].size(); ++i)
		ans=min(ans, dp[now][i]);
	write(ans, '\n');
	FastIO::flusher.~Flusher();
	return 0;
}