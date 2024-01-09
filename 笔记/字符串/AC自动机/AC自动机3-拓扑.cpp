#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, gs, ans[N], to[N], in[N];
char s[N], t[N];
queue <int> q;
struct trie {
	int vis[27], fil, cnt, ss;
}AC[N];

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
void add(int m, int d) {
	int now = 0;
	for(int i = 1; i <= m; ++i) {
		int& to = AC[now].vis[s[i]-'a'+1];
		if(!to) 
			to=++gs;
		now=to;
	}
	if(!AC[now].cnt)
		AC[now].cnt=d, to[d]=d;
	else
		to[d]=AC[now].cnt;
	return ;
}
void sol() {
	for(int i = 1; i <= 26; ++i) 
		if(AC[0].vis[i])
			AC[AC[0].vis[i]].fil=0, q.push(AC[0].vis[i]);
	while(!q.empty()) {
		int u = q.front(); 
		q.pop();
		for(int i = 1; i <= 26; ++i)
			if(AC[u].vis[i])
				AC[AC[u].vis[i]].fil=AC[AC[u].fil].vis[i], 
				q.push(AC[u].vis[i]);
			else
				AC[u].vis[i]=AC[AC[u].fil].vis[i];
	}
}

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		scanf("%s", s+1), add(strlen(s+1), i), ans[i]=0;
	sol();
	AC[0].fil=0;
	int now = 0;
	scanf("%s", t+1);
	int ln=strlen(t+1);
	for(int i = 1; i <= ln; ++i) {
		now=AC[now].vis[t[i]-'a'+1];
		++AC[now].ss;
	}
	for(int i = 0; i <= gs; ++i)
		if(AC[i].fil)
			++in[AC[i].fil];
	for(int i = 1; i <= gs; ++i)
		if(in[i] == 0)
			q.push(i);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		ans[AC[u].cnt]+=AC[u].ss;
		if(AC[u].fil) {
			--in[AC[u].fil], AC[AC[u].fil].ss+=AC[u].ss;
			if(in[AC[u].fil] == 0)
				q.push(AC[u].fil);
		}
	}
	for(int i = 1; i <= n; ++i) 
		write(ans[to[i]], '\n');
	return 0;
}
