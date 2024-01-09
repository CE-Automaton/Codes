long double len(int x, int y) {
	long long xx = a[x].x-a[y].x, yy = a[x].y-a[y].y;
	return sqrtl((xx*xx+yy*yy));//不开long long会爆炸！！！！！！！
}
long double calc(int x, int y, int z) {
	long double b = len(x, y), a = len(x, z), c = len(y, z);
	return acos((long double) -/*加负号是为了求补角*/(b*b+c*c-a*a)/b/c/2.00);
}