#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int t, n, len[106]={0,1,5,6,5,5,6,5,6,5,5,6,2,5,5,6,5,5,6,3,5,5,5,6,2,5,3,5,5,
6,5,5,6,5,5,6,1,2,5,6,5,5,6,5,3,5,5,6,5,5,6,5,5,6,5,6,5,5,6,2,3,5,5,6,5,
5,5,6,5,5,6,1,2,5,6,5,5,6,3,5,5,6,5,5,2,3,5,6,5,5,5,6,5,5,6,5,5,6,5,5,6,5,6,5,5,6};
char a[N], s[106][7]={"","a","aabbc","aabbcc","aabcb","aabcc","aabccb","aacbb",
"aacbbc","aacbc","aaccb","aaccbb","ab","abacc","abbac","abbacc","abbca",
"abbcc","abbcca","abc","abcba","abcca","abccb","abccba","ac","acabb",
"acb","acbba","acbbc","acbbca","acbca","accab","accabb","accba","accbb",
"accbba","b","ba","baabc","baabcc","baacb","baacc","baaccb","babcc",
"bac","bacab","bacca","baccab","baccb","bbaac","bbaacc","bbaca","bbacc",
"bbacca","bbcaa","bbcaac","bbcac","bbcca","bbccaa","bc","bca","bcaab",
"bcaac","bcaacb","bcacb","bcbaa","bccaa","bccaab","bccab","bccba","bccbaa",
"c","ca","caabb","caabbc","caabc","caacb","caacbb","cab","cabac","cabba",
"cabbac","cabbc","cacbb","cb","cba","cbaab","cbaabc","cbaac","cbabc",
"cbbaa","cbbaac","cbbac","cbbca","cbbcaa","cbcaa","ccaab","ccaabb","ccaba",
"ccabb","ccabba","ccbaa","ccbaab","ccbab","ccbba","ccbbaa"};//有效的循环节

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
	read(t);
	while(t--) {
		read(n);
		scanf("%s", a+1);
		long long ans = 0;
		for(int i = 1; i <= 105; ++i) {
			int now = 0, tot = 0;
			for(int j = 1; j <= n; ++j) {
				if(s[i][now] == a[j]) ++now;
				if(now == len[i]) now=0, ++tot;
			}
			ans=max(ans, 1LL*tot*tot*len[i]);
		}
		write(ans, '\n');
	}
	return 0;
}
