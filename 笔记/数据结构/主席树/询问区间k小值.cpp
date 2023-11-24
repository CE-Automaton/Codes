#include <bits/stdc++.h>
using namespace std;
int n, m, a[200005], cnt, tot, root[200005], lq, rq, kkk;
struct node {
	int l, r, s;
}nd[5000005];
struct haha {
	int s, id;
}b[200005];
int comp(haha A, haha B) {
	return A.s < B.s;
}
int built(int l, int r) {
	int now = ++tot; nd[now].s=0;
	if(l == r) return now;
	int mid = (l+r)/2;
	nd[now].l=built(l, mid), nd[now].r=built(mid+1, r);
	return now;
}
int ctrln(int z) {
	nd[++tot]=nd[z];
	return tot;
}
int add(int k, int x, int l, int r) {
	int now = ctrln(k);
	++nd[now].s;
	if(l == r)
		return now;
	int mid = (l+r)/2;
	if(x <= mid) nd[now].l=add(nd[k].l, x, l, mid);
	else nd[now].r=add(nd[k].r, x, mid+1, r);
	return now;
}
int ask(int k, int j, int x, int l, int r) {
	if(l == r) return b[l].s;
	int mid = (l+r)/2, hh = nd[nd[j].l].s-nd[nd[k].l].s;
	if(hh < x) return ask(nd[k].r, nd[j].r, x-hh, mid+1, r);
	else return ask(nd[k].l, nd[j].l, x, l, mid);
}
int main() {
	scanf("%d%d", &n, &m);
	root[0]=built(1, n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]), b[i]={a[i],i};
	sort(b+1, b+1+n, comp);
	for(int i = 1; i <= n; ++i)
		a[b[i].id]=i;
	for(int i = 1; i <= n; ++i) 
		root[i]=add(root[i-1], a[i], 1, n);
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &lq, &rq, &kkk);
		printf("%d\n", ask(root[lq-1], root[rq], kkk, 1, n));
	}
	return 0;
} 
