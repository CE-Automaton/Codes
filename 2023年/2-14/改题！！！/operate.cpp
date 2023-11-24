#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
int t, a, b, c, p[100005], cnt, ans;
map<pair<int, int>, int> qwq;
int solve(int x, int y) {
	if(x == 1) return 0;
	else if(y == 1) return (x > 0 ? x-1 : 1-x);
	else {
		if(qwq.find(make_pair(x, y)) != qwq.end()) return qwq[make_pair(x, y)];
		int &ret=qwq[make_pair(x, y)]; ret=(x > 0 ? x-1 : 1-x); 
		for(int i = 1; i <= cnt; ++i)
			if(y%p[i] == 0) {
				int j = x/p[i];
				ret=min(ret, solve(j, y/p[i])+1+x-j*p[i]);
				++j;
				ret=min(ret, solve(j, y/p[i])+1+j*p[i]-x);
			}
		return ret;
	}
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &a, &b);
		if(a < b) swap(a, b);
		int d = c = a-b;
		if(c == 1) {
			printf("%d\n", b-1);
			continue;
		}
		if(c == 0) {
			cnt=0;
			for(int i = 2; i*i <= b; ++i) 
				if(b%i == 0) {
					p[++cnt]=i;
					while(b%i == 0) b/=i;
				}
			if(b != 1) p[++cnt]=b;
			printf("%d\n", cnt);
			continue;
		}
		else {
			cnt=0;
			for(int i = 2; i*i <= d; ++i) 
				if(d%i == 0) {
					p[++cnt]=i;
					while(d%i == 0) d/=i;
				}
			if(d != 1) p[++cnt]=d;
		}
//		cout<<d<<":\n";
//		for(int i = 1; i <= cnt; ++i) 
//			cout<<p[i]<<" ";cout<<"\n";
		ans=solve(b, c);
		printf("%d\n", ans);
		qwq.clear();
	}
	return 0;
}
