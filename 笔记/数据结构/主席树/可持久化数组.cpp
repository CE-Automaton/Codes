#include <bits/stdc++.h>
using namespace std;
int n, m, a[1000006], tot, x, y, root[1000006], v, pr;
struct node { int l, r, s; } nd[25000006];
int built(int k, int l, int r) {
	if(l == r) {
		nd[++tot]={tot, tot, a[l]};
		return tot;
	}
	int mid = (l+r)/2, now = ++tot;
	nd[now].l=built(k*2, l, mid);
	nd[now].r=built(k*2+1, mid+1, r);
	nd[now].s=0;
	return now;
}
int ctrln(int z) {
	nd[++tot]=nd[z];
	return tot;
}
int change(int k, int l, int r) {
	int now = ctrln(k);
	if(l == r) {
		nd[now].s=y;
		return now;
	}
	int mid = (l+r)/2;
	if(x <= mid) nd[now].l=change(nd[k].l, l, mid);
	else nd[now].r=change(nd[k].r, mid+1, r);
	return now;
}
int ask(int k, int l, int r) {
	if(l == r) return nd[k].s;
	int mid = (l+r)/2;
	if(x <= mid) return ask(nd[k].l, l, mid);
	else return ask(nd[k].r, mid+1, r);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	root[0]=built(1, 1, n);
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d", &v, &pr);
		if(pr == 1) {
			scanf("%d%d", &x, &y);
			root[i]=change(root[v], 1, n);
		}
		else {
			scanf("%d", &x);
			printf("%d\n", ask(root[v], 1, n));
			root[i]=root[v];
		}
	}
	return 0;
} 
