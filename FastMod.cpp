int mod=998244353;
struct FastMod
{
	using ull=unsigned long long;
	using L=__int128;
	ull b,m;
	FastMod(ull b):b(b),m(ull((L(1)<<64)/b)){}
	ull reduce(ull a)// return a mod b
	{
		ull q=(ull)((L(m)*a)>>64),r=a-q*b;
		return r>=b?r-b:r;
	}
}F(mod);
