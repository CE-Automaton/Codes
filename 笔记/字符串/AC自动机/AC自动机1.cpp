#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, gs, ans;
char s[N], t[N];
queue <int> q;
struct trie {
	int vis[27], cnt, fil;
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
void add(int m) {
	int now = 0;
	for(int i = 1; i <= m; ++i) {
		int& to = AC[now].vis[s[i]-'a'+1];//往下层走 
		if(!to) to=++gs;//新建节点 
		now=to;
	}
	++AC[now].cnt;//标记结束点 
	return ;
}
void sol() {
	for(int i = 1; i <= 26; ++i) 
		if(AC[0].vis[i])
			AC[AC[0].vis[i]].fil=0, q.push(AC[0].vis[i]);//第一层的fail指向根 
	while(!q.empty()) {
		int u = q.front(); 
		q.pop();
		for(int i = 1; i <= 26; ++i)
			if(AC[u].vis[i])
				AC[AC[u].vis[i]].fil=AC[AC[u].fil].vis[i], 
				q.push(AC[u].vis[i]);//更新点的fail 
			else
				AC[u].vis[i]=AC[AC[u].fil].vis[i];//不存在, 则指向fail的vis[i], 因为fail已经处理过
	}
}

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		scanf("%s", s+1), add(strlen(s+1));
	sol();
	AC[0].fil=0;
	int now = 0;
	scanf("%s", t+1);
	n=strlen(t+1);
	for(int i = 1; i <= n; ++i) {
		now=AC[now].vis[t[i]-'a'+1];//向下走 
		int tt = now;
		while(tt && AC[tt].cnt != -1)//统计答案 
			ans+=AC[tt].cnt, AC[tt].cnt=-1, tt=AC[tt].fil;
	}
	write(ans, '\n');
	return 0;
}
