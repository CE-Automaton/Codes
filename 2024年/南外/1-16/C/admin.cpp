#include <bits/stdc++.h>
using namespace std;
const int N=1e7+5;
char s[N];
int n,a[N],tot,ans[N];
inline bool work(int len,int k){
	if(k==0)return len==0;
	if(len==1)return 0;
	if(k==1){
		if(len&1)return 0;
		else for(int i=2;i<=len;i+=2)ans[++tot]=1;
		return 1;
	}else{
		if(len%3==0){
			for(int i=3;i<=len;i+=3)ans[++tot]=2;
		}else if(len%3==1){
			for(int i=3;i<=len-4;i+=3)ans[++tot]=2;
			ans[++tot]=1;ans[++tot]=1;
		}else{
			for(int i=3;i<=len-2;i+=3)ans[++tot]=2;
			ans[++tot]=1;
		}
		return 1;
	}
}
inline bool check(int k){
	memset(a+1,0,n<<2);
	for(int i=1;i<=n;++i){
		if(i>1&&s[i]=='1'&&s[i-1]=='0'){
			for(int j=1;j<=k;++j)a[i-j]=1;
		}
		if(s[i]=='1')a[i]=1;
	}
	tot=0;
	int pre=0;
	for(int i=1;i<=n;++i){
		if(a[i]&&!a[i-1]){
			if(!pre){
				if(!work(i-pre-1,k))return 0;
				pre=i;
			}else{
				if(!work(i-pre-2,k))return 0;
				pre=i;
			}
		}
		if(a[i]&&!a[i+1]){
			ans[++tot]=i-pre+1;
			pre=i;
		}
	}
	if(!work(n-k-pre,k))return 0;
	return 1;
}
int main(){
	freopen("exam.in","r",stdin);
	freopen("exam.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",s+1);
	int mn=4,pre=-1;
	for(int i=1;i<=n;++i){
		if(s[i]=='1'&&(i==1||s[i-1]=='0'))
			mn=min(mn,i-pre-2);
		if(s[i]=='1')pre=i;
	}
	if(pre==-1){
		puts("Yes");
		for(int i=1;i<=n;++i)putchar('T');
		return 0;
	}
	mn=min(mn,n-pre);
	for(int i=0;i<=mn;++i){
		if(check(i)){
			puts("Yes");
			int flag=0;
			for(int j=1;j<=tot;++j){
				for(int p=1;p<=ans[j];++p){
					++flag;putchar('F');
				}
				if(j<tot)putchar('T'),++flag;
			}
			while(flag<n)putchar('T'),++flag;
			return 0;
		}
	}
	puts("No");
	return 0;
}
