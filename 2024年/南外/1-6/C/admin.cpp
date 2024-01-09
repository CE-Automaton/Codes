#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#define meow(args...) (fprintf(stderr, args), fflush(stderr))
const int N=1e5+1;
struct Bitset {
	unsigned long long mask[50000/64+1];
	void set(int id) {mask[id>>6]|=1llu<<(id&63);}
};
struct Interval {
	int l, r;
	bool operator<(const Interval &o) const {return l<o.l;}
};
int a[N], cnt[N], id[N], len, maj[N], nmin[N], pc[65536];
Interval range[N];
Bitset st[6][64], cur;
int read() {
	int a=0;
	unsigned char c;
	while((c=getchar()-'0')>9);
	while(a=a*10+c, (c=getchar()-'0')<=9);
	return a;
}
void check_union(Bitset &S, const Bitset &T) {
	for(int i=0; i<len; ++i) S.mask[i]|=T.mask[i];
}
int count(const Bitset &S) {
	int ans=0;
	for(int i=0; i<len; ++i) ans+=pc[S.mask[i]&65535]+pc[S.mask[i]>>16&65535]+pc[S.mask[i]>>32&65535]+pc[S.mask[i]>>48];
	return ans;
}
int main() {
	int n, m, p, nid=0, nmaj=0, siz;
	for(int i=1; i<65536; ++i) pc[i]=pc[i&i-1]+1;
	assert(freopen("cicada.in", "r", stdin));
	assert(freopen("cicada.out", "w", stdout));
	n=read(), m=read(), p=read();
	for(int i=1; i<=n; ++i) ++cnt[a[i]=read()];
	for(int i=1; i<N; ++i) if(cnt[i]>1) id[i]=nid++;
	for(int i=1; i<=n; ++i) {
		nmin[i]=nmin[i-1];
		if(cnt[a[i]]>1) maj[nmaj++]=i; else ++nmin[i];
	}
	for(int i=0; i<nmaj; ++i) a[i]=id[a[maj[i]]];
	siz=nmaj/64+1;
	len=nid+63>>6;
	for(int i=0; i<nmaj; ++i) st[0][i/siz].set(a[i]);
	for(int i=1; i<6; ++i)
		for(int j=0; j<64; ++j) {
			st[i][j]=st[i-1][j];
			check_union(st[i][j], st[i-1][j+(1<<i-1)]);
		}
#define	LOOP (cur.set(a[l]), cur.set(a[l+1]), cur.set(a[l+2]), cur.set(a[l+3]), cur.set(a[l+4]), cur.set(a[l+5]), cur.set(a[l+6]), cur.set(a[l+7]))
	for(int i=0, ans; i<m; ++i) {
		int k=read(), base=0;
		memset(cur.mask, 0, len*sizeof(unsigned long long));
		for(int j=0; j<k; ++j) {
			int l=read(), r=read();
			if(i&&p) {
				l=(l^ans)%n+1;
				r=(r^ans)%n+1;
				if(l>r) std::swap(l, r);
			}
			range[j]=(Interval){l, r};
		}
		std::sort(range, range+k);
		for(int j=0, r=0; j<k; ++j) {
			if(r>=range[j].l) range[j].l=r+1;
			if(range[j].r>r) r=range[j].r;
		}
		for(int j=0; j<k; ++j) {
			int l=range[j].l, r=range[j].r;
			if(l>r) continue;
			base+=nmin[r]-nmin[l-1];
			l=std::lower_bound(maj, maj+nmaj, l)-maj;
			r=std::upper_bound(maj, maj+nmaj, r)-maj;
			if(l/siz==r/siz) {
				for(; l+8<=r; l+=8) LOOP;
				while(l<r) cur.set(a[l++]);
			} else {
				int bl=l/siz+1, br=r/siz, lr=bl*siz, rl=br*siz;
				for(; l+8<=lr; l+=8) LOOP;
				while(l<lr) cur.set(a[l++]);
				for(l=rl; l+8<=r; l+=8) LOOP;
				while(l<r) cur.set(a[l++]);
				if(bl!=br) {
					int lv=31-__builtin_clz(br-bl);
					check_union(cur, st[lv][bl]);
					check_union(cur, st[lv][br-(1<<lv)]);
				}
			}
		}
		printf("%d\n", ans=base+count(cur));
	}
#undef LOOP
	return 0;
}
