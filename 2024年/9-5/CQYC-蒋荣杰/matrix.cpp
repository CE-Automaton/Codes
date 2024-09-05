#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e3+5;
int t, n, mod, a[N][N], b[N][N], c[N][N], sum, smu, sma[N], smb[N], ans, pwa[N], pwb[N], smm[2][N], smmm[2][N], mms[3], mmms[3], 
op[35][2]={{0,0}, {2,2}, {2,1}, {1,2}, {4,1}, {1,4}, {8,1}, {1,8}, {32,1}, {1,32}, {128,1}, {1,128}, {2048,1}, {1,2048}, {8192,1}, {1,8192}, 
{131072,1}, {1,131072}, {524288,1}, {1,524288}, {8388608,1}, {1,8388608}, {536870912,1}, {1,536870912}};
bitset<N> aa[N], bb[N], ss;

namespace FastIO {
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=obuf;
	char* flush(){fwrite(obuf,1,oT-oS,stdout);return oT=obuf;}
	struct Flusher{~Flusher(){flush();}}flusher;
	inline char gc(){return iS==iT && (iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT)?EOF:*iS++;}
	inline void pc(char c){if(oT==oS+SIZE) flush();*oT++=c;}
	#define getchar gc
	#define putchar pc
	// #define pc putchar 
	// template <typename T> inline void debug(T x) { cerr<<x; }
	// template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
}
using FastIO::gc;
using FastIO::pc;
using FastIO::read;
using FastIO::write;
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	File("matrix");
	read(t);
	while(t--) {
		ans = 1;
		read(mod), read(n);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				read(a[i][j]);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				read(b[i][j]);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				read(c[i][j]);
		if(mod == 1) {
			pc('Y'), pc('e'), pc('s'), pc('\n');
			continue;
		}
		if(mod == 2) {
			for(int i = 1; i <= n; ++i) {
				aa[i].reset();
				bb[i].reset();
				for(int j = 1; j <= n; ++j)
					aa[i][j]=a[i][j];
				for(int j = 1; j <= n; ++j)
					bb[j][i]=b[i][j];
			}
			for(int i = 1; i <= n && ans; ++i)
				for(int j = 1; j <= n && ans; ++j) {
					ss=(aa[i]&bb[j]);
					if(c[i][j] != ss.count()%2)
						ans=0;
				}
			if(ans)
				pc('Y'), pc('e'), pc('s'), pc('\n');
			else
				pc('N'), pc('o'), pc('\n');
			continue;
		}
		sum=smu=0;
		pwa[0]=mod-1;
		pwb[0]=mod-2;
		for(int i = 1; i <= n; ++i)
			sma[i]=smb[i]=0, 
			pwa[i]=upd(pwa[i-1]+pwa[i-1]),
			pwb[i]=pwa[i];
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j) {
				sma[j]=upd(sma[j]+1LL*pwa[i]*a[i][j]%mod);
				smb[i]=upd(smb[i]+1LL*pwb[j]*b[i][j]%mod);
				sum=upd(sum+1LL*pwa[i]*c[i][j]%mod*pwb[j]%mod);
			}
		for(int i = 1; i <= n; ++i)
			smu=upd(smu+1LL*sma[i]*smb[i]%mod);
		if(sum != smu) ans=0;

		sum=smu=0;
		for(int i = 0; i <= n; ++i)
			sma[i]=smb[i]=0, swap(pwa[i], pwb[i]);//省时
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j) {
				sma[j]=upd(sma[j]+1LL*pwa[i]*a[i][j]%mod);
				smb[i]=upd(smb[i]+1LL*pwb[j]*b[i][j]%mod);
				sum=upd(sum+1LL*pwa[i]*c[i][j]%mod*pwb[j]%mod);
			}
		for(int i = 1; i <= n; ++i)
			smu=upd(smu+1LL*sma[i]*smb[i]%mod);
		if(sum != smu) ans=0;

		for(int o = 2; o <= 23 && ans; o+=2) {
			mms[0]=mms[1]=mmms[0]=mmms[1]=mms[2]=mmms[2]=0;
			pwa[0]=op[o][0];
			for(int i = 1; i <= n; ++i)
				smm[0][i]=smmm[0][i]=smm[1][i]=smmm[1][i]=0, 
				pwa[i]=1LL*pwa[i-1]*pwa[0]%mod;
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j) {
					smm[0][j]=upd(smm[0][j]+a[i][j]);
					smm[1][j]=upd(smm[1][j]+1LL*pwa[i]*a[i][j]%mod);
					smmm[0][i]=upd(smmm[0][i]+b[i][j]);
					smmm[1][i]=upd(smmm[1][i]+1LL*pwa[j]*b[i][j]%mod);
					mms[0]=upd(mms[0]+1LL*pwa[i]*c[i][j]%mod);
					mms[1]=upd(mms[1]+1LL*pwa[j]*c[i][j]%mod);
					mms[2]=upd(mms[2]+1LL*pwa[i]*pwa[j]%mod*c[i][j]%mod);
				}
			for(int i = 1; i <= n; ++i)
				mmms[0]=upd(mmms[0]+1LL*smm[1][i]*smmm[0][i]%mod), //横着的
				mmms[1]=upd(mmms[1]+1LL*smm[0][i]*smmm[1][i]%mod), //竖着的
				mmms[2]=upd(mmms[2]+1LL*smm[1][i]*smmm[1][i]%mod); //斜着的
			if(mms[0] != mmms[0] || mms[1] != mmms[1] || mms[2] != mmms[2]) ans=0;
		}
		if(ans)
			pc('Y'), pc('e'), pc('s'), pc('\n');
		else
			pc('N'), pc('o'), pc('\n');
	}
	// write(clock(), '\n');
	FastIO::flusher.~Flusher();
	return 0;
}