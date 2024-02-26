#include<bits/stdc++.h>
using namespace std;

const int maxn=3005;
int n,m,c;
char s[maxn],ans[2][maxn*maxn];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<2*n;i++){
		scanf("%s",s);
		if(i==0)c=s[0]=='B';
	}
	if((n*m)&1){
		int now=0;
		for(int i=0;i<n*m;i++)for(int j=i+1;j<n*m;j++){
			ans[0][now]=ans[1][now]=char(((j-i)&1)+'0');
			now++;
		}
	}
	else{
		int now=0;
		for(int i=0;i<n*m;i++)for(int j=i+1;j<n*m;j++){
			if(i==0)ans[c][now]='1';
			else ans[c][now]=char(((j-i)&1)+'0');
			if(j==n*m-1)ans[1^c][now]='0';
			else ans[1^c][now]=char(((j-i)&1)+'0');
			now++;
		}
	}
	printf("%s\n%s\n",ans[0],ans[1]);
	return 0;
}
