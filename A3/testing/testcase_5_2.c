
int main() {
	int a;
	int b;
	int c;
	int d;
	int e;
	int ret1;
	int f;
	a = 1;
	b = 2;
	c = 3;
	d = 4;
	e = 5;
	f = 6;

	if(( (a+3) == (b - (-2)))&&(( (c*6) >= (d/3) ) || (! (f>5) )))
		ret1 = f%4;
	printf("%d\n", ret1);
	return 0;
}