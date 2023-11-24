#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, a[5], b[5], tot, jia[15], tto, che[15];

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

signed main() {
	freopen("triple.in", "r", stdin);
	freopen("triple.out", "w", stdout);
	read(t);
	while(t--) {
		for(int i = 1; i <= 3; ++i)
			read(a[i]); 
		for(int i = 1; i <= 3; ++i)
			read(b[i]);
		signed ans = 3, pp = 0;
		if(b[1] != a[1])
			++pp;
		if(b[2] != a[2])
			++pp;
		if(b[3] != a[3])
			++pp;
		if(pp == 3)
			for(int x = 1; x <= 3; ++x)
				if(x != 2 || (x == 2 && a[1] != 0 && b[1]%a[1] == 0))
					for(int y = 1; y <= 3; ++y)
						if(y != 2 || (y == 2 && a[2] != 0 && b[2]%a[2] == 0))
							for(int z = 1; z <= 3; ++z) 
								if(z != 2 || (z == 2 && a[3] != 0 && b[3]%a[3] == 0)) {
									tot=tto=0;
									if(x == 1)
										jia[++tot]=b[1]-a[1];
									if(y == 1)
										jia[++tot]=b[2]-a[2];
									if(z == 1)
										jia[++tot]=b[3]-a[3];
									
									if(x == 2)
										che[++tto]=b[1]/a[1];
									if(y == 2)
										che[++tto]=b[2]/a[2];
									if(z == 2)
										che[++tto]=b[3]/a[3];
										
									if(tto >= 2 && che[1] == che[2]) 
										ans=min(ans, 2);//肯定能2次弄完
									if(tot >= 2 && jia[1] == jia[2])
										ans=min(ans, 2);//肯定能2次弄完
									if(tto == 3 && che[1] == che[2] && che[2] == che[3]) 
										ans=min(ans, 1);
									if(tto == 3 && (che[1] == che[2] || che[1] == che[3] || che[2] == che[3] || 
									che[1]*che[2] == che[3] || che[1]*che[3] == che[2] || che[2]*che[3] == che[1]))
										ans=min(ans, 2);
									if(tot == 3 && jia[1] == jia[2] && jia[2] == jia[3]) 
										ans=min(ans, 1);
									if(tot == 3 && (jia[1] == jia[2] || jia[1] == jia[3] || jia[2] == jia[3] || 
									jia[1]+jia[2] == jia[3] || jia[1]+jia[3] == jia[2] || jia[2]+jia[3] == jia[1]))
										ans=min(ans, 2);
									signed gs = (x == 3)+(y == 3)+(z == 3);
									if(gs == 1) {
										signed to = (x == 3 ? 1 : (y == 3 ? 2 : 3));
										if(tot && tto) {
											if(a[to]*che[1]+jia[1] == b[to] || (a[to]+jia[1])*che[1] == b[to])
												ans=min(ans, 2);
										}
										else //呃呃呃好像没啥意义 
											continue;
									}
									else {
										if(gs == 2) {
											signed aa = 0, bb = 0;
											if(x == 3) {
												if(aa) bb=1;
												else aa=1;
											}
											if(y == 3) {
												if(aa) bb=2;
												else aa=2;
											}
											if(z == 3) 
												bb=3;
											if(a[aa] == a[bb])
												continue;//无解
											if((b[aa]-b[bb])%(a[aa]-a[bb]) != 0)
												continue;//无解
											int A = (b[aa]-b[bb])/(a[aa]-a[bb]), B = b[aa]-a[aa]*A;
											if(tot) {
												if(jia[1] == B)
													ans=min(ans, 2-(A == 1));//jia[1]不可能为0 
												else
													if(jia[1]*A == B/*先加后乘时先加的那个数*/)
														ans=min(ans, 2-(A == 1));//B=0的时候不能减!!!因为jia[1]不可能为0,不能不加一个jia[1] 
													else
														ans=min(ans, 3-(A == 1)-(B == 0));
											}
											if(tto) {
												if(che[1] == A)
													ans=min(ans, 2-(A == 1)-(B == 0));
												else
													ans=min(ans, 3-(A == 1)-(B == 0));
											}
										}
										else {
											if(a[1] == a[2] || a[1] == a[3] || a[2] == a[3])
												continue;//无解
											if((b[1]-b[2])%(a[1]-a[2]) != 0 || (b[1]-b[3])%(a[1]-a[3]) != 0 || (b[3]-b[2])%(a[3]-a[2]) != 0) 
												continue;//无解
											int A1 = (b[1]-b[2])/(a[1]-a[2]), B1 = b[1]-a[1]*A1, 
											A2 = (b[1]-b[3])/(a[1]-a[3]), B2 = b[1]-a[1]*A2, 
											A3 = (b[3]-b[2])/(a[3]-a[2]), B3 = b[2]-a[2]*A3;
											if(A1 == A2 && A2 == A3 && B1 == B2 && B2 == B3) 
												ans=min(ans, 2-(A1 == 1)-(B1 == 0));
										}
									} 
								}
		if(pp == 2) {
			ans=min(ans, 2);
			signed aa = 0, bb = 0;
			if(b[1] != a[1]) {
				if(aa) bb=1;
				else aa=1;
			}
			if(b[2] != a[2]) {
				if(aa) bb=2;
				else aa=2;
			}
			if(b[3] != a[3]) 
				bb=3;
			for(int x = 1; x <= 3; ++x)
				if(x != 2 || (x == 2 && a[aa] != 0 && b[aa]%a[aa] == 0))
					for(int y = 1; y <= 3; ++y)
						if(y != 2 || (y == 2 && a[bb] != 0 && b[bb]%a[bb] == 0)) {
							tot=tto=0;
							if(x == 1)
								jia[++tot]=b[aa]-a[aa];
							if(y == 1)
								jia[++tot]=b[bb]-a[bb];
							
							if(x == 2)
								che[++tto]=b[aa]/a[aa];
							if(y == 2)
								che[++tto]=b[bb]/a[bb];
								
							if(tto == 2 && che[1] == che[2]) 
								ans=min(ans, 1);//肯定能1次弄完
							if(tot == 2 && jia[1] == jia[2])
								ans=min(ans, 1);//肯定能1次弄完
							signed gs = (x == 3)+(y == 3);
							if(gs == 1) {//无意义QwQ,但就是写了 
								signed to = (x == 3 ? aa : bb);
								if(tot && ((a[to] != 0 && (b[to]-jia[1])%a[to] == 0) || (a[to]+jia[1] != 0 && b[to]%(a[to]+jia[1]) == 0))) 
									ans=min(ans, 2);
								if(tto)
									ans=min(ans, 2);
							}
							else {
								if(a[aa] == a[bb])
									continue;//无解
								if((b[aa]-b[bb])%(a[aa]-a[bb]) != 0)
									continue;//无解
								int A = (b[aa]-b[bb])/(a[aa]-a[bb]), B = b[aa]-a[aa]*A;
								ans=min(ans, 2-(A == 1)-(B == 0));
							} 
						}
		}
		if(pp == 1)
			ans=min(ans, 1);
		if(pp == 0)
			ans=0;
		write(ans, '\n');
	}
	return 0;
}
/*
首先每个值单独加上一个数的话答案为3,那最终的答案一定不超过3

加、乘混合情况: 
三个数同时先加后乘或先乘后加比直接加优,先乘后加再乘肯定不优,先加后乘再加也不优 
先加后乘:ax+ab=x',ay+ab=y',az+ab=z';先乘后加ax+b=x',ay+b=y',az+b=z'
那先加后乘就等价于先乘后加了(a都可以解出来,值相同),相当于是b能被a整除的特殊情况 

单加单乘可以判断是否能1或2步得到答案 

一个数单乘或单加可以和两个数的加、乘混合一起讨论,判断最终答案能否为2 
一个数加、乘混合与另外两个数分别为单加单乘也有可能为2 
*/
