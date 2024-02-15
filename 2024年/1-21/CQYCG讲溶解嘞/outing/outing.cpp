#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, gs, tot, zhan[105];
LL w[N], ans, sum;
struct trie {
	int vis[2], cnt, pd;
}tr[N*61];

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
void add(LL x) {
	int now = 0;
	for(int i = 0; i <= 59; ++i) {
		int& to = tr[now].vis[((x>>i)&1LL)];
		if(!to) to=++gs;
		now=to;
	}
	++tr[now].cnt;
}
void get(int x, int dep) {
	if(tr[x].vis[0])
		get(tr[x].vis[0], dep+1), tr[x].cnt+=tr[tr[x].vis[0]].cnt-2*tr[tr[x].vis[0]].pd;
	if(tr[x].vis[1])
		get(tr[x].vis[1], dep+1), tr[x].cnt+=tr[tr[x].vis[1]].cnt-2*tr[tr[x].vis[1]].pd;
	if(tr[x].cnt >= 2)
		tr[x].pd=1, ans^=(LL) (1LL<<dep)-1LL/* , debug(dep, "!!?\n") */;
	else
		tr[x].pd=0;
}
void dlt(LL x) {
	tot=0;
	int now = 0;
	for(int i = 0; i <= 59; ++i) {
		zhan[++tot]=now;
		now=tr[now].vis[(x>>i)&1LL];
	}
	for(int i = tot; i >= 1; --i) {
		int op = zhan[i];
		tr[op].cnt=(tr[op].vis[0] ? tr[tr[op].vis[0]].cnt-2*tr[tr[op].vis[0]].pd : 0)+
		(tr[op].vis[1] ? tr[tr[op].vis[1]].cnt-2*tr[tr[op].vis[1]].pd : 0);
		if(tr[op].cnt >= 2)
			tr[op].pd=1, sum^=(LL) (1LL<<i)-1LL/* , debug(op, i, "!??\n") */;
		else
			tr[op].pd=0;
	}
	--tr[now].cnt;
	for(int i = tot; i >= 1; --i) {
		int op = zhan[i];
		tr[op].cnt=(tr[op].vis[0] ? tr[tr[op].vis[0]].cnt-2*tr[tr[op].vis[0]].pd : 0)+
		(tr[op].vis[1] ? tr[tr[op].vis[1]].cnt-2*tr[tr[op].vis[1]].pd : 0);
		if(tr[op].cnt >= 2)
			tr[op].pd=1, sum^=(LL) (1LL<<i)-1LL/* , debug(op, i, "!?\n") */;
		else
			tr[op].pd=0;
	}
	++tr[now].cnt;
	for(int i = tot; i >= 1; --i) {
		int op = zhan[i];
		tr[op].cnt=(tr[op].vis[0] ? tr[tr[op].vis[0]].cnt-2*tr[tr[op].vis[0]].pd : 0)+
		(tr[op].vis[1] ? tr[tr[op].vis[1]].cnt-2*tr[tr[op].vis[1]].pd : 0);
		if(tr[op].cnt >= 2)
			tr[op].pd=1;
		else
			tr[op].pd=0;
	}
}

signed main() {
	File("outing");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(w[i]), add(w[i]), ans^=w[i];
	get(0, 1);
	for(int i = 1; i <= n; ++i) 
		sum=ans, dlt(w[i]), write(sum^w[i], ' ');
	return 0;
}