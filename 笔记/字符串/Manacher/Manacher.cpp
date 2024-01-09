#include <bits/stdc++.h>
using namespace std;
int n, len[22000005], mid, mr, ans;
char s[11000005], t[22000005];
int main() {
	scanf("%s", s+1);
	n=strlen(s+1);
	for(int i = 1; i <= n; ++i) t[i*2]=s[i], t[i*2-1]='#';
	t[2*n+1]=t[0]='#', len[0]=len[1]=1, mid=1, mr=2;
	for(int i = 2; i <= 2*n+1; ++i) {
		if(i >= mr) len[i]=1;
		else len[i]=min(len[mid*2-i], mr-i);
		while(t[i+len[i]] == t[i-len[i]]) ++len[i];
		if(i+len[i] > mr) {
			mr=i+len[i];
			mid=i;
		}
	}
	for(int i = 1; i <= 2*n+1; ++i)
		ans=max(ans, (len[i]*2-1)/2);
	printf("%d\n", ans);
	return 0;
} 
