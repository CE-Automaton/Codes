#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const uLL base = 29;
uLL hs[8005], ht, bs[8005];
int n, m, haha = 1000000;
char s[8005], t[8005];
int cnt(string qwq) {
	int len = qwq.size(), ret = 0;
	for(int i = 0; i < len; ++i)
		hs[i+1]=hs[i]*base+qwq[i]-'a'+1;
	for(int i = 1; i <= len-m+1; ++i)
		if(hs[i+m-1]-hs[i-1]*bs[m] == ht) ++ret;
	return ret;
}
void dfs(int x, string qwq) {
	if(x == n+1) {
		if(qwq.size() == 0) return ;
		if(cnt(qwq) == 0)
			haha=min(haha, n-((int) qwq.size()));
		return ;
	}
	dfs(x+1, qwq+s[x]);
	dfs(x+1, qwq);
}
int main() {
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	scanf("%s%s", s+1, t+1);
	n=strlen(s+1), m = strlen(t+1);
	bs[0]=1;
	for(int i = 1; i <= n; ++i)
		bs[i]=bs[i-1]*base;
	for(int i = 1; i <= m; ++i)
		ht=ht*base+t[i]-'a'+1;
	if(n <= 10) {
		dfs(1, "");
		printf("%d\n", haha);
		return 0;
	}
	string az = "";
	for(int i = 1; i <= n; ++i)
		az+=s[i];
	if(n > 1000) {
		cout<<cnt(az);
		return 0;
	}
	haha = 0;
	while('O') {
		int o = cnt(az);
		if(o == 0) {
			printf("%d\n", haha);
			return 0;
		}
		string p, q;
		int h = 1000000;
		for(int i = 0; i < az.size(); ++i) {
			p="";
			for(int j = 0; j < az.size(); ++j)
				if(i != j) p+=az[j];
			int gs = cnt(p);
			if(gs < h)
				q=p, h=gs;
		}
		az=q;
		++haha;
	}
	return 0;
}
