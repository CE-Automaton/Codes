#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const uLL base = 7;
uLL hs[100005], hsf[100005], bs[100005];
int n, sx[35], ha[35], l, pd[35], cnt, fn[100005], my[100005];
char x[100005];
char bh(char y) {
	if(y == 'T') return 'A'; if(y == 'G') return 'C';
	if(y == 'C') return 'G'; if(y == 'A') return 'T';
}
int ef(int A, int B) {
	int ans = 0, ll = 1, rr = min(A, B)-l+1;
	while(ll <= rr) {
		int mid = (ll+rr)/2;
		uLL a = hs[A-mid+1]-hs[A+1]*bs[mid], b = hs[B-mid+1]-hs[B+1]*bs[mid];
		if(a == b) ll=mid+1, ans=mid;
		else rr = mid-1;
	}
	return ans;
} 
int tspd(int l1, int r1, int l2, int r2) {//0表示左优,1表示右优
	int ans = 0, ll = 1, rr = min(r1-l1+1, r2-l1+1);
	while(ll <= rr) {
		int mid = (ll+rr)/2, a1 = r1-mid+1, a2 = l2+mid-1;
		uLL a = hs[a1]-hs[r1+1]*bs[mid], b = hsf[a2]-hsf[l2-1]*bs[mid];
		//左边的不仅要变换,还要反过来,而右边的啥也不干 
		if(a == b) ll=mid+1, ans=mid;
		else rr = mid-1;
	}
	if(ans == min(r1-l1+1, r2-l1+1))
		return 0;
	if(sx[x[r1-ans]-'A'+1] < ha[x[l2+ans]-'A'+1]) return 0;
	return 1;
}
int comp(int A, int B) {//1表示A优,0表示B优 
	int xt = ef(A, B);
	if(xt == A-l+1) 
		return tspd(l, B-xt, A+1, B);
	if(xt == B-l+1) 
		return tspd(l, A-xt, B+1, A)^1;
	if(sx[x[A-xt]-'A'+1] < sx[x[B-xt]-'A'+1])
		return 1;
	return 0;
}
void sot(int ll, int rr) {
	if(ll == rr) return ;
	int mid = (rr+ll)/2;
	sot(ll, mid), sot(mid+1, rr);
	for(int i = ll; i <= rr; ++i) my[i]=fn[i];
	int xx = ll, yy = mid+1;
	for(int i = ll; i <= rr; ++i) {
		if(xx > mid) fn[i]=my[yy++];
		else if(yy > rr) fn[i]=my[xx++];
		else if(comp(my[xx], my[yy])) fn[i]=my[xx++];
		else fn[i]=my[yy++];
	}
}
int main() {
	freopen("gene.in", "r", stdin);
	freopen("gene.out", "w", stdout);
	scanf("%s", x+1);
	n=strlen(x+1);
	ha[1]=bs[0]=sx['T'-'A'+1]=1; ha['C'-'A'+1]=sx['G'-'A'+1]=2;
	ha['G'-'A'+1]=sx['C'-'A'+1]=3; ha['T'-'A'+1]=sx[1]=4;
	for(int i = 1; i <= n; ++i)
		bs[i]=bs[i-1]*base, hsf[i]=hsf[i-1]*base+ha[x[i]-'A'+1]/*未进行变换的*/;
	for(int i = n; i >= 1; --i)
		hs[i]=hs[i+1]*base+sx[x[i]-'A'+1]/*变换后的*/, ++pd[x[i]-'A'+1];
	if(pd['T'-'A'+1] != 0) {//有'T'一定把'T'换到前面,原本最前面的'A'不能动 
		for(l = 1; l <= n; ++l) 
			if(x[l] != 'A') break;
		for(int i = l; i <= n; ++i)
			if(x[i] == 'T' && (i == n || x[i+1] != 'T'))
				fn[++cnt]=i;
		sot(1, cnt);
		for(int i = l; i <= fn[1]; ++i)
			x[i]=bh(x[i]);
		for(int i = 1; i*2 <= fn[1]-l+1; ++i)
			swap(x[l+i-1], x[fn[1]-i+1]);
	}
	else {
		if(pd['G'-'A'+1] != 0) {//没有'T'的话,一定是最前面的'A'、'C'不能动
			for(l = 1; l <= n; ++l) 
				if(x[l] != 'A' && x[l] != 'C') break;
			for(int i = l; i <= n; ++i)
				if(x[i] == 'G' && (i == n || x[i+1] != 'G'))
					fn[++cnt]=i;
			sot(1, cnt);
			for(int i = l; i <= fn[1]; ++i)
				x[i]=bh(x[i]);
			for(int i = 1; i*2 <= fn[1]-l+1; ++i)
				swap(x[l+i-1], x[fn[1]-i+1]);
		}
		else 
			x[n]=bh(x[n]);//'A'、'C'都会变成字典序更大的,一定不优,但好像一定要变换 
	}
	printf("%s\n", x+1);
	return 0;
} 
