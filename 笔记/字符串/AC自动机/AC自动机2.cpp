#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, gs, ans[155], dd[155];
char s[155][75], t[N];
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
void add(int m, int d) {
	int now = 0;
	for(int i = 1; i <= m; ++i) {
		int& to = AC[now].vis[s[d][i]-'a'+1]; 
		if(!to) {
			to=++gs;
			for(int j = 1; j <= 26; ++j)
				AC[to].vis[j]=0;
			AC[to].cnt=AC[to].fil=0;
		}
		now=to;
	}
	AC[now].cnt=d;
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
int comp(int A, int B) {
	if(ans[A] == ans[B])
		return A < B;
	return ans[A] > ans[B];
}

signed main() {
	while(1) {
		read(n);
		if(n == 0) break;
		for(int i = 1; i <= 26; ++i) 
			AC[0].vis[i]=0;
		AC[0].cnt=AC[0].fil=0;
		gs=0;
		for(int i = 1; i <= n; ++i)
			scanf("%s", s[i]+1), add(strlen(s[i]+1), i), dd[i]=i, ans[i]=0;
		sol();
		AC[0].fil=0;
		int now = 0;
		scanf("%s", t+1);
		int ln=strlen(t+1);
		for(int i = 1; i <= ln; ++i) {
			now=AC[now].vis[t[i]-'a'+1];
			int tt = now;
			while(tt)
				++ans[AC[tt].cnt], tt=AC[tt].fil;
		}
		sort(dd+1, dd+1+n, comp);
		write(ans[dd[1]], '\n');
		for(int i = 1; i <= n; ++i) 
			if(ans[dd[1]] == ans[dd[i]]) 
				printf("%s\n", s[dd[i]]+1);
			else
				break;
	}
	return 0;
}
